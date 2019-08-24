#ifndef RAINBOW_RAND_H
#define RAINBOW_RAND_H

#include <Arduino.h>

void rainbowRand_setup(uint32_t** buffer, int width, int height);
void rainbowRand_loop(uint32_t** buffer, int width, int height);

#endif
