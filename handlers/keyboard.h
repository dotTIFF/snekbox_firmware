#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "tusb.h"

#include "debug.h"

#include "common_types.h"

#define MAX_KEYBOARD_REPORT_SIZE 64

void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report, uint16_t len);

#endif