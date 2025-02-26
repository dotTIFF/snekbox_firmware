#ifndef _WS2812_H_
#define _WS2812_H_

#include <stdint.h>

void init_ws2812();

void set_rgb0(uint8_t r, uint8_t g, uint8_t b);
void set_rgb1(uint8_t r, uint8_t g, uint8_t b);

#endif