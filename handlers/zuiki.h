#ifndef _ZUIKI_H_
#define _ZUIKI_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define ZUIKI_VID 0x33dd
#define ZUIKI_PID 0x0014

#define ZUIKI_REPORT_ID 0x01
#define ZUIKI_OUTPUT_REPORT_ID 0x05

#pragma pack(push, 1)

typedef struct
{
  uint8_t reportId;                        // Report ID = 0x01 (1)
                                           // Collection: CA:Joystick CP:Pointer
  int8_t GD_JoystickPointerX;              // Usage 0x00010030: X, Value =  to 127
  int8_t GD_JoystickPointerY;              // Usage 0x00010031: Y, Value =  to 127
  uint8_t green : 1;                       // Usage 0x00090001: Button 1 Primary/trigger, Value = 0 to 1, Physical = Value
  uint8_t red : 1;                         // Usage 0x00090002: Button 2 Secondary, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton3 : 1;  // Usage 0x00090003: Button 3 Tertiary, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton4 : 1;  // Usage 0x00090004: Button 4, Value = 0 to 1, Physical = Value
  uint8_t down : 1;                        // Usage 0x00090005: Button 5, Value = 0 to 1, Physical = Value
  uint8_t left : 1;                        // Usage 0x00090006: Button 6, Value = 0 to 1, Physical = Value
  uint8_t menu_left : 1;                   // Usage 0x00090007: Button 7, Value = 0 to 1, Physical = Value
  uint8_t menu_right : 1;                  // Usage 0x00090008: Button 8, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton9 : 1;  // Usage 0x00090009: Button 9, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton10 : 1; // Usage 0x0009000A: Button 10, Value = 0 to 1, Physical = Value
  uint8_t up : 1;                          // Usage 0x0009000B: Button 11, Value = 0 to 1, Physical = Value
  uint8_t right : 1;                       // Usage 0x0009000C: Button 12, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton13 : 1; // Usage 0x0009000D: Button 13, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton14 : 1; // Usage 0x0009000E: Button 14, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton15 : 1; // Usage 0x0009000F: Button 15, Value = 0 to 1, Physical = Value
  uint8_t BTN_JoystickPointerButton16 : 1; // Usage 0x00090010: Button 16, Value = 0 to 1, Physical = Value
} zuiki_report_t;

typedef struct
{
  uint8_t reportId;  // Report ID = 0x05 (5)
                     // Collection: CA:Joystick CP:Pointer
  uint8_t lights[4]; // Usage 0x00080043: Slow Blink On Time, Value = 0 to -1
} outputReport05_t;

#pragma pack(pop)

bool is_ZUIKI(uint8_t dev_addr);

void processZUIKI(uint8_t const *report, uint16_t len);
void setZuikiLights(uint8_t dev_addr, uint8_t instance);

#endif