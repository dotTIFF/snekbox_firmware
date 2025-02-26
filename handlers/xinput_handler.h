#ifndef _XINPUT_HANDLER_
#define _XINPUT_HANDLER_

#include "xinput_host.h"

usbh_class_driver_t const *usbh_app_driver_get_cb(uint8_t *driver_count);
void tuh_xinput_report_received_cb(uint8_t dev_addr, uint8_t instance, xinputh_interface_t const *xid_itf, uint16_t len);
void tuh_xinput_mount_cb(uint8_t dev_addr, uint8_t instance, const xinputh_interface_t *xinput_itf);

void setXINPUTRumble(uint8_t dev_addr, uint8_t instance, uint8_t rumbleLeft, uint8_t rumbleRight);

#endif