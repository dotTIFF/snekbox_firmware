#ifndef _GAMO_H_
#define _GAMO_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

// NOTE: sending a CONFIG_SET_PROTOCOL to this device kills the gamepad output.
// I have modified `hid_host.c` in tinyusb to skip this entirely for all devices.

#define PHOENIXWAN_VID 0x1ccf
#define PHOENIXWAN_PID 0x8048

#pragma pack(push, 1)

// decoded using hidrdd
// use the GAMEPAD mode.
typedef struct
{
    // No REPORT ID byte
    int8_t turntable;
    int8_t GD_JoystickPointerY;

    uint8_t B1 : 1;
    uint8_t B2 : 1;
    uint8_t B3 : 1;
    uint8_t B4 : 1;
    uint8_t B5 : 1;
    uint8_t B6 : 1;
    uint8_t B7 : 1;
    uint8_t BTN_JoystickPointerButton7 : 1;

    uint8_t E1 : 1;
    uint8_t E2 : 1;
    uint8_t E3 : 1;
    uint8_t E4 : 1;
    uint8_t BTN_JoystickPointerButton12 : 1;
    uint8_t BTN_JoystickPointerButton13 : 1;
    uint8_t BTN_JoystickPointerButton14 : 1;
    uint8_t BTN_JoystickPointerButton15 : 1;

    uint8_t pad_3 : 8;

} PHOENIXWAN_report_t;

#pragma pack(pop)

bool is_PHOENIXWAN(uint8_t dev_addr);

void processPHOENIXWAN(uint8_t const *report, uint16_t len);

#endif