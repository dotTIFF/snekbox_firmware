#ifndef _XBOXOG_H_
#define _XBOXOG_H_

#include "xboxog_descriptors.h"

#define XID_REQ_GET_DESCRIPTOR 0x06
#define XID_MSFT_VENDREQ 0xC1
#define XID_GET_DESCRIPTOR_VALUE 0x4200

#define XID_GETCAP_IN 0x0100
#define XID_GETCAP_OUT 0x0200

#define XID_REPORTSIZE_IN 0x14
#define XID_REPORTSIZE_OUT 0x06

extern uint8_t xbox_input_data[XBOX_EPINSIZE];
extern USB_XboxGamepad_Data_t xbox_controller_state;

void xboxog_setup(void);
void xboxog_task(void);

void xboxog_process_output(uint8_t report_size);

void xboxog_makeReport(void);

#endif