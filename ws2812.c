#include "ws2812.h"
#include "ws2812.pio.h"

#include "hardware/pio.h"
#include "pico/stdlib.h"

#define WS2812_PIO pio1

#define WS2812_MAX_BRIGHTNESS (0.01)

#define NUM_PIXELS 2
uint32_t led_data[NUM_PIXELS];

int sm_ws2812;

void init_ws2812()
{
    sm_ws2812 = pio_claim_unused_sm(WS2812_PIO, true);
    uint offset = pio_add_program(WS2812_PIO, &ws2812_program);

    ws2812_program_init(WS2812_PIO, sm_ws2812, offset, PIN_SNEKBOX_WS2812, 800000, false);

    // clear LED state.
    set_rgb0(0, 0, 0);
    set_rgb1(0, 0, 0);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    // clamp values of rgb to make it less bright.
    return ((uint32_t)(r * WS2812_MAX_BRIGHTNESS) << 8) |
           ((uint32_t)(g * WS2812_MAX_BRIGHTNESS) << 16) |
           (uint32_t)(b * WS2812_MAX_BRIGHTNESS);
}

void push_ws1812_state()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        pio_sm_put_blocking(WS2812_PIO, sm_ws2812, led_data[i] << 8);
    }
}

void set_rgb0(uint8_t r, uint8_t g, uint8_t b)
{
    led_data[0] = urgb_u32(r, g, b);
    push_ws1812_state();
}

void set_rgb1(uint8_t r, uint8_t g, uint8_t b)
{
    led_data[1] = urgb_u32(r, g, b);
    push_ws1812_state();
}
