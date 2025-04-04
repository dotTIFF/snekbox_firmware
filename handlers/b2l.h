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
    uint8_t reportId;

    uint8_t left : 1;
    uint8_t right : 1;
    uint8_t up : 1;
    uint8_t down : 1;
    uint8_t pad1 : 4;

    uint8_t pad2 : 8;
} b2l_report_t;

#pragma pack(pop)

bool is_B2L(uint8_t dev_addr);

#endif
