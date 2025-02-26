#include "gamo.h"

bool is_PHOENIXWAN(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == PHOENIXWAN_VID && pid == PHOENIXWAN_PID);
}

void processPHOENIXWAN(uint8_t const *report, uint16_t len)
{
    // no report ID...
    if (len >= sizeof(PHOENIXWAN_report_t))
    {
        PHOENIXWAN_report_t new_PHOENIXWAN_state = {0};
        memcpy(&new_PHOENIXWAN_state, report, sizeof(new_PHOENIXWAN_state));

        // reset_report();

        // DebugPrintf("%d", new_PHOENIXWAN_state.turntable);

        // new_PHOENIXWAN_state.turntable clockwise is positive, counter is negative.
        // zero when not turning in gamepad mode.
        // PS2 games want clockwise up and counter down.
        input_report.short_report.dpad_up = new_PHOENIXWAN_state.turntable > 0;
        input_report.short_report.dpad_down = new_PHOENIXWAN_state.turntable < 0;

        input_report.short_report.btn_west = new_PHOENIXWAN_state.B1;
        input_report.short_report.l1 = new_PHOENIXWAN_state.B2;
        input_report.short_report.btn_south = new_PHOENIXWAN_state.B3;
        input_report.short_report.r1 = new_PHOENIXWAN_state.B4;
        input_report.short_report.btn_east = new_PHOENIXWAN_state.B5;
        input_report.short_report.l2 = new_PHOENIXWAN_state.B6;
        input_report.short_report.dpad_left = new_PHOENIXWAN_state.B7;

        input_report.short_report.start = new_PHOENIXWAN_state.E1;
        input_report.short_report.select = new_PHOENIXWAN_state.E2;
    }
}
