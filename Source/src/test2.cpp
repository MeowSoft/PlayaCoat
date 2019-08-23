
#include "test2.h"

//#define USE_TEST_2
#ifdef USE_TEST_2

#include <OctoWS2811.h>

#define LEDS_PER_STRIP 28
#define NUM_STRIPS 8

static const int CONFIG = WS2811_GRB | WS2811_800kHz;
static const int NUM_LEDS = LEDS_PER_STRIP * NUM_STRIPS;

DMAMEM int displayMemory[NUM_LEDS];
int drawingMemory[NUM_LEDS];

OctoWS2811 leds(LEDS_PER_STRIP, displayMemory, drawingMemory ,CONFIG);

void setAllColor(unsigned int color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds.setPixel(i, color);
    }
    leds.show();
}

void test2_setup() {
  leds.begin();
}

void test2_loop() {
  setAllColor(0xff0000);
  delay(1500);

  setAllColor(0x00ff00);
  delay(1500);

  setAllColor(0x0000ff);
  delay(1500);

  setAllColor(0x00000);
  delay(1500);
}
#endif