#ifndef __JOYBUS_HPP
#define __JOYBUS_HPP

#include "pico/stdlib.h"
#include "debug.h"

#pragma pack(push, 1)

typedef union
{
    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t start : 1;
        uint8_t origin : 1; // Indicates if GetOrigin(0x41) was called (LOW)
        uint8_t errlatch : 1;
        uint8_t errstat : 1;

        uint8_t dLeft : 1;
        uint8_t dRight : 1;
        uint8_t dDown : 1;
        uint8_t dUp : 1;
        uint8_t z : 1;
        uint8_t r : 1;
        uint8_t l : 1;
        uint8_t use_origin : 1; // some games will ignore analog if this is zero.

        uint8_t xStick;
        uint8_t yStick;
        uint8_t cxStick;
        uint8_t cyStick;
        uint8_t analogL;
        uint8_t analogR;
    }; // mode3 (default reading mode)

    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t start : 1;
        uint8_t origin : 1; // Indicates if GetOrigin(0x41) was called (LOW)
        uint8_t errlatch : 1;
        uint8_t errstat : 1;

        uint8_t dLeft : 1;
        uint8_t dRight : 1;
        uint8_t dDown : 1;
        uint8_t dUp : 1;
        uint8_t z : 1;
        uint8_t r : 1;
        uint8_t l : 1;
        uint8_t use_origin : 1;

        uint8_t xStick;
        uint8_t yStick;
        uint8_t cxStick;
        uint8_t cyStick;

        uint8_t analogR : 4;
        uint8_t analogL : 4;

        uint8_t analogB : 4;
        uint8_t analogA : 4;
    } mode0;

    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t start : 1;
        uint8_t origin : 1; // Indicates if GetOrigin(0x41) was called (LOW)
        uint8_t errlatch : 1;
        uint8_t errstat : 1;

        uint8_t dLeft : 1;
        uint8_t dRight : 1;
        uint8_t dDown : 1;
        uint8_t dUp : 1;
        uint8_t z : 1;
        uint8_t r : 1;
        uint8_t l : 1;
        uint8_t use_origin : 1;

        uint8_t xStick;
        uint8_t yStick;
        uint8_t cyStick : 4;
        uint8_t cxStick : 4;
        uint8_t analogL;
        uint8_t analogR;
        uint8_t analogB : 4;
        uint8_t analogA : 4;
    } mode1;

    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t start : 1;
        uint8_t origin : 1; // Indicates if GetOrigin(0x41) was called (LOW)
        uint8_t errlatch : 1;
        uint8_t errstat : 1;

        uint8_t dLeft : 1;
        uint8_t dRight : 1;
        uint8_t dDown : 1;
        uint8_t dUp : 1;
        uint8_t z : 1;
        uint8_t r : 1;
        uint8_t l : 1;
        uint8_t use_origin : 1;

        uint8_t xStick;
        uint8_t yStick;
        uint8_t cyStick : 4;
        uint8_t cxStick : 4;
        uint8_t analogR : 4;
        uint8_t analogL : 4;
        uint8_t analogA;
        uint8_t analogB;
    } mode2;

    struct
    {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t start : 1;
        uint8_t origin : 1; // Indicates if GetOrigin(0x41) was called (LOW)
        uint8_t errlatch : 1;
        uint8_t errstat : 1;

        uint8_t dLeft : 1;
        uint8_t dRight : 1;
        uint8_t dDown : 1;
        uint8_t dUp : 1;
        uint8_t z : 1;
        uint8_t r : 1;
        uint8_t l : 1;
        uint8_t use_origin : 1;

        uint8_t xStick;
        uint8_t yStick;
        uint8_t cxStick;
        uint8_t cyStick;
        uint8_t analogA;
        uint8_t analogB;
    } mode4;

} GCReport;

#pragma pack(pop)

void gcn_setup(int dataPin);
void gcn_task();

extern GCReport gcReport;

#endif