#include <Arduino.h>
#include <OctoWS2811.h>

#include "random.h"

#define LEDS_PER_STRIP 28

bool ledState = false;

DMAMEM int displayMemory[LEDS_PER_STRIP * 6];
int drawingMemory[LEDS_PER_STRIP * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(LEDS_PER_STRIP, displayMemory, drawingMemory, config);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  random_setup(28, 8);
  leds.begin();
  leds.show();
}

void loop() {
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
    random_loop(leds);
    delay(200);
}
