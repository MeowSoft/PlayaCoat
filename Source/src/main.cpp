#include <Arduino.h>
#include <OctoWS2811.h>

#include "test2.h"

bool ledState = false;

void setup() {
  test2_setup();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
    test2_loop();
}


