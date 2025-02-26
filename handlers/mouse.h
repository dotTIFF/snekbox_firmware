#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "debug.h"
#include "common_types.h"

#include "tusb.h"

void process_mouse_report(uint8_t dev_addr, hid_mouse_report_t const *report);

#endif