#ifndef _DS5_H_
#define _DS5_H_

#include <stdint.h>

#include "tusb.h"
#include "common_types.h"

#define DS5_VID 0x054c
#define DS5_PID 0x0ce6

#define DS5_REPORT_ID 0x01

#pragma pack(push, 1)

typedef struct
{
    uint8_t reportId;              // Report ID = 0x01 (1)
                                   // Collection: CA:Gamepad
    uint8_t lx;                    // Usage 0x00010030: X, Value = 0 to 255
    uint8_t ly;                    // Usage 0x00010031: Y, Value = 0 to 255
    uint8_t rx;                    // Usage 0x00010032: Z, Value = 0 to 255
    uint8_t ry;                    // Usage 0x00010035: Rz, Value = 0 to 255
    uint8_t l2_trigger;            // Usage 0x00010033: Rx, Value = 0 to 255
    uint8_t r2_trigger;            // Usage 0x00010034: Ry, Value = 0 to 255
    uint8_t VEN_Gamepad0020;       // Usage 0xFF000020: , Value = 0 to 255
    uint8_t dpad : 4;              // Usage 0x00010039: Hat Switch, Value = 0 to 7, Physical = Value x 45 in degrees
    uint8_t square : 1;            // Usage 0x00090001: Button 1 Primary/trigger, Value = 0 to 1, Physical = Value x 315
    uint8_t cross : 1;             // Usage 0x00090002: Button 2 Secondary, Value = 0 to 1, Physical = Value x 315
    uint8_t circle : 1;            // Usage 0x00090003: Button 3 Tertiary, Value = 0 to 1, Physical = Value x 315
    uint8_t triangle : 1;          // Usage 0x00090004: Button 4, Value = 0 to 1, Physical = Value x 315
    uint8_t l1 : 1;                // Usage 0x00090005: Button 5, Value = 0 to 1, Physical = Value x 315
    uint8_t r1 : 1;                // Usage 0x00090006: Button 6, Value = 0 to 1, Physical = Value x 315
    uint8_t l2 : 1;                // Usage 0x00090007: Button 7, Value = 0 to 1, Physical = Value x 315
    uint8_t r2 : 1;                // Usage 0x00090008: Button 8, Value = 0 to 1, Physical = Value x 315
    uint8_t create : 1;            // Usage 0x00090009: Button 9, Value = 0 to 1, Physical = Value x 315
    uint8_t options : 1;           // Usage 0x0009000A: Button 10, Value = 0 to 1, Physical = Value x 315
    uint8_t l3 : 1;                // Usage 0x0009000B: Button 11, Value = 0 to 1, Physical = Value x 315
    uint8_t r3 : 1;                // Usage 0x0009000C: Button 12, Value = 0 to 1, Physical = Value x 315
    uint8_t ps : 1;                // Usage 0x0009000D: Button 13, Value = 0 to 1, Physical = Value x 315
    uint8_t touchpad : 1;          // Usage 0x0009000E: Button 14, Value = 0 to 1, Physical = Value x 315
    uint8_t mute : 1;              // Usage 0x0009000F: Button 15, Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad0021 : 1;   // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00211 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00212 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00213 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00214 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00215 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00216 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00217 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00218 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad00219 : 1;  // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad002110 : 1; // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad002111 : 1; // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad002112 : 1; // Usage 0xFF000021: , Value = 0 to 1, Physical = Value x 315
    uint8_t VEN_Gamepad0022[52];   // Usage 0xFF000022: , Value = 0 to 255, Physical = Value x 21 / 17
} DS5_report_t;

#pragma pack(pop)

bool is_DS5(uint8_t dev_addr);
void processDS5(uint8_t const *report, uint16_t len);

#endif
