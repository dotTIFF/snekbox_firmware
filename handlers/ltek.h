#ifndef _LTEK_H_
#define _LTEK_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define LTEK_VID1 0x6667
#define LTEK_PID1 0xc006

#define LTEK_VID2 0x03EB
#define LTEK_PID2 0x8041

#define LTEK_REPORT_ID 0x01

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
} ltek_report_t;

#pragma pack(pop)

bool is_LTEK(uint8_t dev_addr);

void processLTEK(uint8_t const *report, uint16_t len);

#endif
