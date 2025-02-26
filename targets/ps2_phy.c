#include "ps2_phy.h"
#include "debug.h"

uint smCmdReader;
uint smDatWriter;

uint offsetCmdReader;
uint offsetDatWriter;

PIO psx_pio = pio1;

bool ignore_whole_command = false;

void __not_in_flash_func(SEND)(uint8_t byte)
{
	// calling this during a non CS event is invalid
	if (gpio_get(PIN_SEL) == 1)
	{
		return;
	}

	// block against the fifo level *unless* the CS line from the
	// master is pulled, then exit out.
	while (pio_sm_is_tx_fifo_full(psx_pio, smDatWriter))
	{
		if (gpio_get(PIN_SEL) == 1)
		{
			return;
		}
	}

	write_byte_blocking(psx_pio, smDatWriter, byte);
}

uint8_t __not_in_flash_func(RECV_CMD)()
{
	// calling this during a non CS event is invalid
	if (gpio_get(PIN_SEL) == 1)
	{
		return 0;
	}

	// block against the fifo level *unless* the CS line from the
	// master is pulled, then exit out.
	while (pio_sm_get_rx_fifo_level(psx_pio, smCmdReader) == 0)
	{
		if (gpio_get(PIN_SEL) == 1)
		{
			return 0;
		}
	}

	return read_byte_blocking(psx_pio, smCmdReader);
}

void __time_critical_func(restart_pio_sm)()
{
	pio_set_sm_mask_enabled(psx_pio, 1 << smCmdReader | 1 << smDatWriter, false);
	pio_restart_sm_mask(psx_pio, 1 << smCmdReader | 1 << smDatWriter);

	// restart smCmdReader PC
	pio_sm_exec(psx_pio, smCmdReader, pio_encode_jmp(offsetCmdReader));
	// restart smDatWriter PC
	pio_sm_exec(psx_pio, smDatWriter, pio_encode_jmp(offsetDatWriter));

	pio_sm_clear_fifos(psx_pio, smCmdReader);
	// drain instead of clear, so that we empty the OSR
	pio_sm_drain_tx_fifo(psx_pio, smDatWriter);

	pio_enable_sm_mask_in_sync(psx_pio, 1 << smCmdReader | 1 << smDatWriter);
}

void __time_critical_func(selCallback)(uint gpio, uint32_t event)
{
	if (gpio != PIN_SEL && event & GPIO_IRQ_EDGE_RISE)
		return;

	ignore_whole_command = false;

	restart_pio_sm();
}

void psx_task()
{
	if (ignore_whole_command)
	{
		return;
	}

	if (pio_sm_get_rx_fifo_level(psx_pio, smCmdReader) > 0)
	{
		uint32_t status = save_and_disable_interrupts();
		
		uint8_t incoming = RECV_CMD();

		if (incoming == PS2_START_WORD_CONTROLLER)
		{
			process_joy_req();
		}
		else
		{
			// the PS1 will send us information we *don't* want from the memory card bus
			// since we share some lines.
			// for some reason it will pull the CS low, so let's just
			// ignore the whole word until the IRQ resets and allows
			// us to process things from the start of the next talks.
			ignore_whole_command = true;

			if (incoming != PS2_START_WORD_MEMCARD)
			{
				// DebugPrintf("Unknown byte %02x", incoming);
			}
		}
		
		restore_interrupts(status);
	}
}

void init_pio()
{
	// false is input.
	gpio_set_dir(PIN_DAT, false);
	gpio_set_dir(PIN_CMD, false);
	gpio_set_dir(PIN_SEL, false);
	gpio_set_dir(PIN_CLK, false);
	gpio_set_dir(PIN_ACK_GCN_DAT, false);

	gpio_disable_pulls(PIN_DAT);
	gpio_disable_pulls(PIN_CMD);
	gpio_disable_pulls(PIN_SEL);
	gpio_disable_pulls(PIN_CLK);
	gpio_disable_pulls(PIN_ACK_GCN_DAT);

	// used for initing the irq.
	gpio_init(PIN_SEL);
	gpio_set_dir(PIN_SEL, GPIO_IN);

	smCmdReader = pio_claim_unused_sm(psx_pio, true);
	smDatWriter = pio_claim_unused_sm(psx_pio, true);

	offsetCmdReader = pio_add_program(psx_pio, &cmd_reader_program);
	offsetDatWriter = pio_add_program(psx_pio, &dat_writer_program);

	cmd_reader_program_init(psx_pio, smCmdReader, offsetCmdReader);
	dat_writer_program_init(psx_pio, smDatWriter, offsetDatWriter);

	gpio_set_slew_rate(PIN_DAT, GPIO_SLEW_RATE_FAST);
	gpio_set_drive_strength(PIN_DAT, GPIO_DRIVE_STRENGTH_12MA);
}

void psx_setup()
{
	initPS2ControllerState();

	init_pio();

	DebugPrintf("PIO Init Finished");

	restart_pio_sm();

	sleep_ms(500);

	gpio_set_irq_enabled_with_callback(PIN_SEL, GPIO_IRQ_EDGE_RISE, true, selCallback);
	gpio_set_irq_enabled(PIN_SEL, GPIO_IRQ_EDGE_RISE, true);

	// multicore_reset_core1();
	// multicore_launch_core1(simulation_thread);

	DebugPrintf("Simulator started!");
}
