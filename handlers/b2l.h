#ifndef _B2L_H_
#define _B2L_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define B2L_VID 0x1973
#define B2L_PID 0x1021

#define MAX_KEYBOARD_REPORT_SIZE 64

void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report, uint16_t len);

bool is_B2L(uint8_t dev_addr);

#endif
