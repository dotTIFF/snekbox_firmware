#include "b2l.h"

bool is_B2L(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == B2L_VID && pid == B2L_PID);
}

void processB2L(uint8_t const *report, uint16_t len)
{
    if (report[0] == B2L_REPORT_ID && len >= sizeof(b2l_report_t))
    {
        b2l_report_t new_B2L_state = {0};
        memcpy(&new_B2L_state, report, sizeof(new_B2L_state));
        
        reset_report();

        input_report.short_report.dpad_up = new_B2L_state.up;
        input_report.short_report.dpad_down = new_B2L_state.down;
        input_report.short_report.dpad_left = new_B2L_state.left;
        input_report.short_report.dpad_right = new_B2L_state.right;
    }
}
