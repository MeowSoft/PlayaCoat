#ifndef RAINBOW_SCROLL_H
#define RAINBOW_SCROLL_H

#include <OctoWS2811.h>

void rainbow_scroll_setup(int displayX, int displayY);

void rainbow_scroll_loop(OctoWS2811 leds);

#endif
