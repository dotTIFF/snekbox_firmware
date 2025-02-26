#ifndef _DEFORCE_H_
#define _DEFORCE_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define DFORCE_VID 0x0079
#define DFORCE_PID 0x0011

#define DFORCE_REPORT_ID 0x01

#pragma pack(push, 1)

// decoded using hidrdd
// god this hid report was nasty,
// why does a dance pad need four joysticks!?!?!
// and select was the MSB of one?!!?!?!?
typedef struct
{
    // 01
    uint8_t report_id;

    // 7F 7F 7F
    uint8_t GD_JoystickX;
    uint8_t GD_JoystickX_1;
    uint8_t GD_JoystickX_2;

    // 7F
    uint8_t GD_JoystickX_3 : 7;
    uint8_t back : 1;

    // 0F
    uint8_t GD_JoystickUndefined : 4;
    uint8_t up : 1;
    uint8_t down : 1;
    uint8_t left : 1;
    uint8_t right : 1;

    // 00 00
    uint8_t center : 1;
    uint8_t down_right : 1;
    uint8_t up_left : 1;
    uint8_t up_right : 1;
    uint8_t down_left : 1;
    uint8_t select : 1;

} DFORCE_report_t;

#pragma pack(pop)

bool is_DFORCE(uint8_t dev_addr);

void processDFORCE(uint8_t const *report, uint16_t len);

#endif
