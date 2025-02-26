#ifndef _SMX_TYPES_H_
#define _SMX_TYPES_H_

#include <stdint.h>

#include "tusb.h"

#include "common_types.h"

#define SMX_VID 0x2341
#define SMX_PID 0x8037

#define SMX_REPORT_GAMEPAD_STATE 0x03

#pragma pack(push, 1)

typedef union
{
    struct
    {
        bool ul : 1;
        bool uc : 1;
        bool ur : 1;
        bool cl : 1;
        bool cc : 1;
        bool cr : 1;
        bool dl : 1;
        bool dc : 1;
        bool dr : 1;
        uint16_t padding : 7;
    } val;
    uint16_t raw;
} smx_buttons_t;

typedef struct
{
    uint8_t hid_report_id;
    smx_buttons_t buttons;
} smx_state;

#pragma pack(pop)

bool is_SMX(uint8_t dev_addr);

void processSMX(uint8_t const *report, uint16_t len);

#endif
