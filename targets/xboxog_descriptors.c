#include "xboxog_descriptors.h"

// array of pointer to string descriptors
char const *xboxog_string_desc_arr[] =
    {
        (const char[]){0x09, 0x04}, // 0: is supported language is English (0x0409)
        "icedragon.io",             // 1: Manufacturer
        "xbox og controller s",     // 2: Product
        "snekbox",                  // 3: Serials will use unique ID if possible
        "xbox og interface",
};

tusb_desc_device_t const xboxog_desc_device =
    {
        .bLength = sizeof(tusb_desc_device_t),
        .bDescriptorType = TUSB_DESC_DEVICE,

        .bcdUSB = 0x0110,

        .bDeviceClass = 0x00,
        .bDeviceSubClass = 0x00,
        .bDeviceProtocol = 0x00,

        .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,

        .idVendor = VID_XBOX,
        .idProduct = PID_XBOX_CTRL_S,
        .bcdDevice = 0x0120,

        .iManufacturer = STRID_XBOXOG_MANUFACTURER,
        .iProduct = STRID_XBOXOG_PRODUCT,
        .iSerialNumber = STRID_XBOXOG_SERIAL,

        .bNumConfigurations = 1,
};

const xboxog_cfg_desc_t xboxog_desc_fs_configuration = {
    .config = {
        .bLength = sizeof(tusb_desc_configuration_t),
        .bDescriptorType = TUSB_DESC_CONFIGURATION,

        .wTotalLength = sizeof(xboxog_cfg_desc_t),
        .bNumInterfaces = INTERFACE_ID_XBOX_Total,
        .bConfigurationValue = 1,
        .iConfiguration = 0,
        .bmAttributes = 0xc0,
        .bMaxPower = 100 / 2,
    },
    .xboxog_interface = {
        .bLength = sizeof(tusb_desc_interface_t),
        .bDescriptorType = TUSB_DESC_INTERFACE,

        .bInterfaceNumber = INTERFACE_ID_XBOX_Gamepad,
        .bAlternateSetting = 0,
        .bNumEndpoints = 2,
        .bInterfaceClass = XID_INTERFACE_CLASS,
        .bInterfaceSubClass = XID_INTERFACE_SUBCLASS,
        .bInterfaceProtocol = 0,
        .iInterface = STRID_XBOXOG_INTERFACE,
    },
    .xboxog_reportINEndpoint = {
        .bLength = sizeof(tusb_desc_endpoint_t),
        .bDescriptorType = TUSB_DESC_ENDPOINT,

        .bEndpointAddress = XBOX_IN_EPADDR,
        .bmAttributes = {
            .xfer = TUSB_XFER_INTERRUPT,
            .sync = TUSB_ISO_EP_ATT_NO_SYNC,
            .usage = 0x00,
        },
        .wMaxPacketSize = XBOX_EPINSIZE,
        .bInterval = 0x04,
    },
    .xboxog_reportOUTEndpoint = {
        .bLength = sizeof(tusb_desc_endpoint_t),
        .bDescriptorType = TUSB_DESC_ENDPOINT,

        .bEndpointAddress = XBOX_OUT_EPADDR,
        .bmAttributes = {
            .xfer = TUSB_XFER_INTERRUPT,
            .sync = TUSB_ISO_EP_ATT_NO_SYNC,
            .usage = 0x00,
        },
        .wMaxPacketSize = XBOX_EPOUTSIZE,
        .bInterval = 0x04,
    },
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const *tud_descriptor_device_cb(void)
{
    return (uint8_t const *)&xboxog_desc_device;
}

uint8_t const *tud_descriptor_configuration_cb(uint8_t index)
{
    (void)index; // for multiple configurations
    return (uint8_t const *)&xboxog_desc_fs_configuration;
}

static uint16_t _desc_str[32 + 1];

uint16_t const *tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
    (void)langid;
    size_t chr_count;

    switch (index)
    {
    case STRID_XBOXOG_LANGID:
        memcpy(&_desc_str[1], xboxog_string_desc_arr[0], 2);
        chr_count = 1;
        break;

        // case STRID_SERIAL:
        // chr_count = board_usb_get_serial(_desc_str + 1, 32);
        // break;

    default:
        // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

        if (!(index < sizeof(xboxog_string_desc_arr) / sizeof(xboxog_string_desc_arr[0])))
            return NULL;

        const char *str = xboxog_string_desc_arr[index];

        // Cap at max char
        chr_count = strlen(str);
        size_t const max_count = sizeof(_desc_str) / sizeof(_desc_str[0]) - 1; // -1 for string type
        if (chr_count > max_count)
            chr_count = max_count;

        // Convert ASCII string into UTF-16
        for (size_t i = 0; i < chr_count; i++)
        {
            _desc_str[1 + i] = str[i];
        }
        break;
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

    return _desc_str;
}
