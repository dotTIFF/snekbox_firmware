#ifndef _SWITCH_PRO_H_
#define _SWITCH_PRO_H_

#include <stdbool.h>
#include <stdint.h>

#include "common_types.h"

#define JC_OUTPUT_RUMBLE_ONLY 0x10
#define JC_MIN_SUBCOMMAND_SIZE 10

#pragma pack(push, 1)

// https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/blob/master/bluetooth_hid_notes.md#standard-input-report---buttons
typedef struct
{
    uint8_t reportId;
    uint8_t counter;

    // joycon 0x03, 0x00 pro, 0x01 usb powered.
    uint8_t connectionInfo : 4;
    uint8_t batt : 4;

    uint8_t y : 1;
    uint8_t x : 1;
    uint8_t b : 1;
    uint8_t a : 1;
    uint8_t sr : 1;
    uint8_t sl : 1;
    uint8_t r : 1;
    uint8_t zr : 1;

    uint8_t minus : 1;
    uint8_t plus : 1;
    uint8_t r3 : 1;
    uint8_t l3 : 1;
    uint8_t home : 1;
    uint8_t capture : 1;
    uint8_t : 1;
    uint8_t charging_grip : 1;

    uint8_t down : 1;
    uint8_t up : 1;
    uint8_t right : 1;
    uint8_t left : 1;
    uint8_t sr2 : 1;
    uint8_t sl2 : 1;
    uint8_t l : 1;
    uint8_t zl : 1;

    uint16_t lx : 12;
    uint16_t ly : 12;
    uint16_t rx : 12;
    uint16_t ry : 12;

} switch_pro_report_t;

// https://github.com/torvalds/linux/blob/ee9a43b7cfe2d8a3520335fea7d8ce71b8cabd9d/drivers/hid/hid-nintendo.c#L506
typedef struct
{
    uint8_t output_id;  /* must be 0x01 for subcommand, 0x10 for rumble only */
    uint8_t packet_num; /* incremented every send */
    uint8_t rumble_data[8];
    uint8_t subcmd_id;
    uint8_t data[32]; /* length depends on the subcommand */
} joycon_subcmd_request_t;

#pragma pack(pop)

bool is_SWITCH_PRO(uint8_t dev_addr);

void processSWITCH_PRO(uint8_t const *report, uint16_t len);

extern bool is_switch_pro_init1, is_switch_pro_fully_init;

void init_switch_pro(uint8_t dev_addr, uint8_t instance);

void setSWITCH_PRORumble(uint8_t dev_addr, uint8_t instance, uint8_t rumbleLeft, uint8_t rumbleRight);

#endif