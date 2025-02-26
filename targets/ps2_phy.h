#ifndef _PS2_PHY_
#define _PS2_PHY_

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/multicore.h"

#include "ps2_controller.h"
#include "__targets.h"

#include "psxSPI.pio.h"

#define PS2_START_WORD_CONTROLLER 0x01
#define PS2_START_WORD_MEMCARD 0x81

void psx_setup();
void psx_task();

void SEND(uint8_t byte);
uint8_t RECV_CMD();

#endif