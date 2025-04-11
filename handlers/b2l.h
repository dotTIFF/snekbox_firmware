#ifndef _B2L_H_
#define _B2L_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define B2L_VID 0x1973
#define B2L_PID 0x1021

#define B2L_REPORT_ID 0x01

#pragma pack(push, 1)

typedef struct
{
    // Report ID = 0x01 (1)
    uint8_t reportId : 8;

    uint8_t p1_up : 1;
    uint8_t p1_down : 1;
    uint8_t p1_left : 1;
    uint8_t p1_right : 1;
    uint8_t p1_pad : 4; // always zero

    uint8_t p2_up : 1;
    uint8_t p2_down : 1;
    uint8_t p2_left : 1;
    uint8_t p2_right : 1;
    uint8_t p2_pad : 4; // always zero

} B2L_report_t;

#pragma pack(pop)

bool is_B2L(uint8_t dev_addr);

void processB2L(uint8_t const *report, uint16_t len);

#endif