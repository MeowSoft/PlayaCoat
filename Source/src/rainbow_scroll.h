#ifndef RAINBOW_SCROLL_H
#define RAINBOW_SCROLL_H

#include <Arduino.h>

void rainbow_scroll_setup(uint32_t** buffer, int width, int height);

void rainbow_scroll_loop(uint32_t** buffer, int width, int height);

#endif
