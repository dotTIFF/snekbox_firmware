#ifndef _DUAL_PS2_H_
#define _DUAL_PS2_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"
#include "input_report.h"

#define DUAL_PS2_VID 0x0810
#define DUAL_PS2_PID 0x0001

#define DUAL_PS2_REPORT_ID 0x01

#pragma pack(push, 1)

typedef struct
{
    // 0x01 for p1 0x02 for p2.
    uint8_t reportId;

    uint8_t ry;
    uint8_t rx;
    uint8_t lx;
    uint8_t ly;

    hid_hat_t dpad_hat : 4;
    uint8_t triangle : 1;
    uint8_t circle : 1;
    uint8_t cross : 1;
    uint8_t square : 1;

    uint8_t l2 : 1;
    uint8_t r2 : 1;
    uint8_t l1 : 1;
    uint8_t r1 : 1;
    uint8_t select : 1;
    uint8_t start : 1;
    uint8_t l3 : 1;
    uint8_t r3 : 1;

} dual_ps2_report_t;

#pragma pack(pop)

bool is_DUAL_PS2(uint8_t dev_addr);

void processDUAL_PS2(uint8_t const *report, uint16_t len);

#endif
