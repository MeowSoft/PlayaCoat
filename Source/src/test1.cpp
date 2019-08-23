
#include <OctoWS2811.h>
#include "test1.h"

// #define USE_TEST_1
#ifdef USE_TEST_1
#define ledsPerStrip 28

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void colorWipe(int color, int wait);

void test1_setup() {
  leds.begin();
  leds.show();
}

#define RED    0x7F0000
#define GREEN  0x007F00
#define BLUE   0x00007F
#define YELLOW 0x7F7F00
#define PINK   0x7F1078
#define ORANGE 0x605800
#define WHITE  0x7F7F7F

// Less intense...
/*
#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010
*/

void test1_loop() {
  int microsec = 200000 / leds.numPixels();  // change them all in 2 seconds

  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}

#endif