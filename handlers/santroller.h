#ifndef _SANTROLLER_H_
#define _SANTROLLER_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define SANTROLLER_VID 0x1209
#define SANTROLLER_PID 0x2882

#define SANTROLLER_REPORT_ID 0x01

#pragma pack(push, 1)

typedef struct
{
    uint8_t reportId;               // Report ID = 0x01 (1)
                                    // Collection: CA:Gamepad
    uint8_t green : 1;              // Usage 0x00090001: Button 1 Primary/trigger, Value = 0 to 1, Physical = Value
    uint8_t red : 1;                // Usage 0x00090002: Button 2 Secondary, Value = 0 to 1, Physical = Value
    uint8_t yellow : 1;             // Usage 0x00090005: Button 5, Value = 0 to 1, Physical = Value
    uint8_t blue : 1;               // Usage 0x00090004: Button 4, Value = 0 to 1, Physical = Value
    uint8_t orange : 1;             // Usage 0x00090007: Button 7, Value = 0 to 1, Physical = Value
    uint8_t BTN_GamepadButton8 : 1; // Usage 0x00090008: Button 8, Value = 0 to 1, Physical = Value
    uint8_t select : 1;             // Usage 0x0009000B: Button 11, Value = 0 to 1, Physical = Value
    uint8_t start : 1;              // Usage 0x0009000C: Button 12, Value = 0 to 1, Physical = Value

    uint8_t guide : 1;               // Usage 0x0009000D: Button 13, Value = 0 to 1, Physical = Value
    uint8_t BTN_GamepadButton3 : 1;  // Usage 0x00090003: Button 3 Tertiary, Value = 0 to 1, Physical = Value
    uint8_t BTN_GamepadButton6 : 1;  // Usage 0x00090006: Button 6, Value = 0 to 1, Physical = Value
    uint8_t BTN_GamepadButton9 : 1;  // Usage 0x00090009: Button 9, Value = 0 to 1, Physical = Value
    uint8_t BTN_GamepadButton10 : 1; // Usage 0x0009000A: Button 10, Value = 0 to 1, Physical = Value
    uint8_t : 1;                     // Pad
    uint8_t : 1;                     // Pad
    uint8_t : 1;                     // Pad

    uint8_t GD_GamepadHatSwitch : 4; // Usage 0x00010039: Hat Switch, Value = 0 to 7, Physical = Value x 45 in degrees
    uint8_t : 4;                     // Pad

    uint8_t whammy;       // Usage 0x00010030: X, Value = 0 to 255, Physical = Value
    uint8_t GD_GamepadY;  // Usage 0x00010031: Y, Value = 0 to 255, Physical = Value
    uint8_t starpower_axis; // Usage 0x00010033: Rx, Value = 0 to 255, Physical = Value

} SANTROLLER_report_t;

#pragma pack(pop)

bool is_SANTROLLER(uint8_t dev_addr);

void processSANTROLLER(uint8_t const *report, uint16_t len);

#endif
