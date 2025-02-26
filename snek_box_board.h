#ifndef _BOARDS_SNEK_BOX_H
#define _BOARDS_SNEK_BOX_H

//------------- BOARD INFO -------------//

// For board detection
#define SNEKBOX_BOARD

//------------- PIN / HARDWARE -------------//

// NOTE: Console pins are defined in the PIO module
// I would include them here, but I can't use globals inside the pio or preprocessors...

#define SNEK_UART_SLOT_DEBUG uart0
#define PIN_SNEKBOX_UART_TX 0
#define PIN_SNEKBOX_UART_RX 1

#define PIN_SNEKBOX_5V_EN 8

#define PIN_SNEKBOX_LED 28
#define PIN_SNEKBOX_WS2812 29

#define PIN_SNEKBOX_DIP1 26
#define PIN_SNEKBOX_DIP2 27

#define PIN_SNEKBOX_BTN1 9
#define PIN_SNEKBOX_BTN2 10
#define PIN_SNEKBOX_BTN3 4
#define PIN_SNEKBOX_BTN4 11

#define SNEK_HELPER_I2C_INSTANCE i2c1
#define PIN_SNEK_I2C_SDA_PIN 2
#define PIN_SNEK_I2C_SCL_PIN 3

// PIO_USB_PINOUT_DMDP is one less than the DP for DM
#define SNEKBOX_USB_PIO_PINOUT (PIO_USB_PINOUT_DMDP)
#define PIN_SNEKBOX_USB_DP 13

//------------- CRYSTAL -------------//

// On some samples, the xosc can take longer to stabilize than is usual
#ifndef PICO_XOSC_STARTUP_DELAY_MULTIPLIER
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
#endif

//------------- FLASH -------------//

// slower generic access
// #define PICO_BOOT_STAGE2_CHOOSE_GENERIC_03H 1

// faster winbond commands.
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1

// lower is better.
#ifndef PICO_FLASH_SPI_CLKDIV
#define PICO_FLASH_SPI_CLKDIV 2
#endif

// pico_cmake_set_default PICO_FLASH_SIZE_BYTES = (8 * 1024 * 1024)
#ifndef PICO_FLASH_SIZE_BYTES
#define PICO_FLASH_SIZE_BYTES (8 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
#define PICO_RP2040_B0_SUPPORTED 0
#endif

#endif
