#ifndef _SOFTMAT_H_
#define _SOFTMAT_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define SOFTMAT_VID 0x0b43
#define SOFTMAT_PID 0x0001

#pragma pack(push, 1)

typedef struct
{
    // No REPORT ID byte
    uint8_t triangle : 1;
    uint8_t circle : 1;
    uint8_t cross : 1;
    uint8_t square : 1;
    uint8_t BTN_JoystickPointerButton4 : 1;
    uint8_t BTN_JoystickPointerButton5 : 1;
    uint8_t BTN_JoystickPointerButton6 : 1;
    uint8_t BTN_JoystickPointerButton7 : 1;
    
    uint8_t select : 1;
    uint8_t start : 1;
    uint8_t BTN_JoystickPointerButton10 : 1;
    uint8_t BTN_JoystickPointerButton11 : 1;
    uint8_t up : 1;
    uint8_t right : 1;
    uint8_t down : 1;
    uint8_t left : 1;

    uint8_t GD_JoystickPointerX;
    uint8_t GD_JoystickPointerY;

    uint8_t GD_JoystickRz;
    uint8_t GD_JoystickZ;
    uint8_t VEN_Joystick0005;

} softmat_report_t;

#pragma pack(pop)

bool is_SOFTMAT(uint8_t dev_addr);

void processSOFTMAT(uint8_t const *report, uint16_t len);

#endif
