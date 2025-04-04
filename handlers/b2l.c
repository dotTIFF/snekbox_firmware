#include "b2l.h"

bool is_B2L(uint8_t dev_addr)
{
    uint16_t vid, pid;
    tuh_vid_pid_get(dev_addr, &vid, &pid);

    return (vid == B2L_VID && pid == B2L_PID);
}

// static uint8_t const keycode2ascii[128][2] = {HID_KEYCODE_TO_ASCII};
static hid_keyboard_report_t prev_report = {0, 0, {0}}; // previous report to check key released
uint8_t repeat_keycode[MAX_KEYBOARD_REPORT_SIZE] = {0};

void processKeyEvent(uint8_t keycode, bool pressed)
{
    switch (keycode)
    {
    // born to lead (b2l) dance pads register as keyboards with abcd inputs
    case HID_KEY_A:
        input_report.short_report.dpad_up = pressed;
        break;
    case HID_KEY_D:
        input_report.short_report.dpad_down = pressed;
        break;
    case HID_KEY_B:
        input_report.short_report.dpad_left = pressed;
        break;
    case HID_KEY_C:
        input_report.short_report.dpad_right = pressed;
        break;

    default:
        break;
    }
}

void processModifierEvent(uint8_t modifier)
{
    input_report.short_report.btn_east = (modifier & (KEYBOARD_MODIFIER_LEFTALT));
}

// look up new key in previous keys
static inline bool find_key_in_report(hid_keyboard_report_t const *report, uint8_t keycode, uint16_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        if (report->keycode[i] == keycode)
            return true;
    }

    return false;
}

// release logic from https://github.com/dquadros/RPTerm/blob/main/keybd.cpp
// press logic from tinyusb host example

// convert hid keycode to ascii and print via usb device CDC (ignore non-printable)
void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report, uint16_t len)
{
    (void)dev_addr;

    // TODO: figure out if we need to reset since every report coming in
    // might not contain the full state of the keyboard.
    // reset_report();

    // DebugOutputBuffer("KEY", report->keycode, len);

    // handle the modifier presses
    if (prev_report.modifier != report->modifier)
    {
        DebugPrintf("MOD CHANGE: %02x", report->modifier);

        processModifierEvent(report->modifier);
    }

    // check for key release
    for (uint8_t i = 0; i < len; i++)
    {
        if (repeat_keycode[i] && !find_key_in_report(report, repeat_keycode[i], len))
        {
            DebugPrintf("Key released %02x", repeat_keycode[i]);
            processKeyEvent(repeat_keycode[i], false);

            repeat_keycode[i] = 0;
        }
    }

    for (uint8_t i = 0; i < len; i++)
    {
        uint8_t keycode = report->keycode[i];

        if (keycode)
        {
            if (find_key_in_report(&prev_report, keycode, len))
            {
                // exist in previous report means the current key is holding
                // DebugPrintf("%02x held!", keycode);
            }
            else
            {
                // not existed in previous report means the current key is pressed
                DebugPrintf("Key pressed %02x", keycode);

                processKeyEvent(keycode, true);

                // bool const is_shift = report->modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT);

                // save the key as being held as it was just pressed
                for (int j = 0; j < len; j++)
                {
                    if (repeat_keycode[j] == 0)
                    {
                        repeat_keycode[j] = keycode;
                        break;
                    }
                }
            }
        }
    }

    prev_report = *report;
}
