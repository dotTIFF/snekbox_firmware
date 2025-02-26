#include "zuiki.h"

bool is_ZUIKI(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == ZUIKI_VID && pid == ZUIKI_PID);
}

void processZUIKI(uint8_t const *report, uint16_t len)
{
    if (report[0] == ZUIKI_REPORT_ID && len >= sizeof(zuiki_report_t))
    {
        zuiki_report_t new_ZUIKI_state = {0};
        memcpy(&new_ZUIKI_state, report, sizeof(new_ZUIKI_state));

        reset_report();

        input_report.short_report.dpad_up = new_ZUIKI_state.up;
        input_report.short_report.dpad_down = new_ZUIKI_state.down;
        input_report.short_report.dpad_left = new_ZUIKI_state.left;
        input_report.short_report.dpad_right = new_ZUIKI_state.right;

        input_report.short_report.btn_south = new_ZUIKI_state.menu_left;
        input_report.short_report.btn_east = new_ZUIKI_state.menu_right;

        input_report.short_report.start = new_ZUIKI_state.green;
        input_report.short_report.select = new_ZUIKI_state.red;

        // new input was a new output for reactive lights.
        output_report.new_output_report = true;
    }
}

void setZuikiLights(uint8_t dev_addr, uint8_t instance)
{
    outputReport05_t newRpt = {0};

    newRpt.reportId = ZUIKI_OUTPUT_REPORT_ID;

    newRpt.lights[0] = input_report.short_report.dpad_right ? 0xFF : 0x00;
    newRpt.lights[1] = input_report.short_report.dpad_down ? 0xFF : 0x00;
    newRpt.lights[2] = input_report.short_report.dpad_left ? 0xFF : 0x00;
    newRpt.lights[3] = input_report.short_report.dpad_up ? 0xFF : 0x00;

    tuh_hid_send_report(dev_addr, instance, 0, &newRpt, sizeof(newRpt));
}
