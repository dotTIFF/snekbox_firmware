#include "dforce.h"

bool is_DFORCE(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == DFORCE_VID && pid == DFORCE_PID);
}

void processDFORCE(uint8_t const *report, uint16_t len)
{
    if (report[0] == DFORCE_REPORT_ID && len >= sizeof(DFORCE_report_t))
    {
        DFORCE_report_t new_dforce_state = {0};
        memcpy(&new_dforce_state, report, sizeof(new_dforce_state));

        reset_report();

        input_report.short_report.dpad_up = new_dforce_state.up;
        input_report.short_report.dpad_down = new_dforce_state.down;
        input_report.short_report.dpad_left = new_dforce_state.left;
        input_report.short_report.dpad_right = new_dforce_state.right;

        input_report.short_report.btn_north = new_dforce_state.down_left;
        input_report.short_report.btn_south = new_dforce_state.up_left;
        input_report.short_report.btn_east = new_dforce_state.up_right;
        input_report.short_report.btn_west = new_dforce_state.down_right;

        input_report.short_report.start = new_dforce_state.select;
        input_report.short_report.select = new_dforce_state.back;
    }
}
