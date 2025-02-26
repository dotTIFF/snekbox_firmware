#include "generic_softmat.h"

bool is_SOFTMAT(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == SOFTMAT_VID && pid == SOFTMAT_PID);
}

void processSOFTMAT(uint8_t const *report, uint16_t len)
{
    if (len >= sizeof(softmat_report_t))
    {
        softmat_report_t new_SOFTMAT_state = {0};
        memcpy(&new_SOFTMAT_state, report, sizeof(new_SOFTMAT_state));
        
        reset_report();

        input_report.short_report.dpad_up = new_SOFTMAT_state.up;
        input_report.short_report.dpad_down = new_SOFTMAT_state.down;
        input_report.short_report.dpad_left = new_SOFTMAT_state.left;
        input_report.short_report.dpad_right = new_SOFTMAT_state.right;

        input_report.short_report.btn_north = new_SOFTMAT_state.triangle;
        input_report.short_report.btn_south = new_SOFTMAT_state.cross;
        input_report.short_report.btn_east = new_SOFTMAT_state.circle;
        input_report.short_report.btn_west = new_SOFTMAT_state.square;

        input_report.short_report.start = new_SOFTMAT_state.start;
        input_report.short_report.select = new_SOFTMAT_state.select;
    }
}
