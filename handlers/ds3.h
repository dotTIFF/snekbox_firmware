#ifndef _DS3_H_
#define _DS3_H_

#include <stdint.h>
#include <stdbool.h>

#include "common_types.h"

#pragma pack(push, 1)

// taken from torvalds/linux/blob/master/drivers/hid/hid-sony.c
typedef struct
{
    uint8_t time_enabled; /* the total time the led is active (0xff means forever) */
    uint8_t duty_length;  /* how long a cycle is in deciseconds (0 means "really fast") */
    uint8_t enabled;
    uint8_t duty_off; /* % of duty_length the led is off (0xff means 100%) */
    uint8_t duty_on;  /* % of duty_length the led is on (0xff mean 100%) */
} sixaxis_led;

typedef struct
{
    uint8_t padding;
    uint8_t right_duration;   /* Right motor duration (0xff means forever) */
    uint8_t right_motor_on;   /* Right (small) motor on/off, only supports values of 0 or 1 (off/on) */
    uint8_t left_duration;    /* Left motor duration (0xff means forever) */
    uint8_t left_motor_force; /* left (large) motor, supports force values from 0 to 255 */
} sixaxis_rumble;

typedef struct
{
    // uint8_t report_id;
    sixaxis_rumble rumble;
    uint8_t padding[4];
    uint8_t leds_bitmap;   /* bitmap of enabled LEDs: LED_1 = 0x02, LED_2 = 0x04, ... */
    sixaxis_led led[4];    /* LEDx at (4 - x) */
    sixaxis_led _reserved; /* LED5, not actually soldered */
} sixaxis_output_report;

typedef struct
{
    uint8_t report_id;
    uint8_t pad0;

    struct
    {
        uint8_t select : 1;
        uint8_t l3 : 1;
        uint8_t r3 : 1;
        uint8_t start : 1;
        uint8_t dpad_up : 1;
        uint8_t dpad_right : 1;
        uint8_t dpad_down : 1;
        uint8_t dpad_left : 1;
    };

    struct
    {
        uint8_t l2 : 1;
        uint8_t r2 : 1;
        uint8_t l1 : 1;
        uint8_t r1 : 1;
        uint8_t triangle : 1;
        uint8_t circle : 1;
        uint8_t cross : 1;
        uint8_t square : 1;
    };

    struct
    {
        uint8_t ps_button : 1;
        uint8_t paddd : 7;
    };

    uint8_t pad1;
    uint8_t lx;
    uint8_t ly;
    uint8_t rx;
    uint8_t ry;

    uint8_t pad2[4];

    uint8_t analog_up;
    uint8_t analog_right;
    uint8_t analog_down;
    uint8_t analog_left;
    uint8_t analog_l2;
    uint8_t analog_r2;
    uint8_t analog_l1;
    uint8_t analog_r1;
    uint8_t analog_triangle;
    uint8_t analog_circle;
    uint8_t analog_cross;
    uint8_t analog_square;

} ds3_report_t;

#pragma pack(pop)

extern bool is_ds3_init;

bool is_DS3(uint8_t dev_addr);

void init_ds3(uint8_t dev_addr, uint8_t instance);

void processDS3(uint8_t const *report, uint16_t len);

void setDS3Rumble(uint8_t dev_addr, uint8_t instance, uint8_t rumbleLeft, uint8_t rumbleRight);

#endif