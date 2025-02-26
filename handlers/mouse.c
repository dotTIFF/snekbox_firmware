#include "mouse.h"

// send mouse report to usb device CDC
void process_mouse_report(uint8_t dev_addr, hid_mouse_report_t const *report)
{
    //------------- button state  -------------//
    // uint8_t button_changed_mask = report->buttons ^ prev_report.buttons;
    char l = report->buttons & MOUSE_BUTTON_LEFT ? 'L' : '-';
    char m = report->buttons & MOUSE_BUTTON_MIDDLE ? 'M' : '-';
    char r = report->buttons & MOUSE_BUTTON_RIGHT ? 'R' : '-';

    // reset_report();

    // DebugPrintf("[%u] %c%c%c %d %d %d", dev_addr, l, m, r, report->x, report->y, report->wheel);

    // tud_cdc_write(tempbuf, count);
    // tud_cdc_write_flush();
}