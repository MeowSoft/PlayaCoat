
#include <Arduino.h>
#include "buttons.h"

// Button arrangement: < > ^ v

#define LEFT_PIN 16
#define RIGHT_PIN 15
#define UP_PIN 10
#define DOWN_PIN 17

#define DEBOUNCE_LIMIT_MS 200

static void (*onLeftPressed)();

void leftInterrupt() {
    static unsigned long debounceLeft = 0;
    unsigned long now = millis();
    if (now - debounceLeft > DEBOUNCE_LIMIT_MS) {
        if (onLeftPressed != 0) {
            onLeftPressed();
        }
    }
    debounceLeft = now;
}

void buttonsSetUp() {
    pinMode(LEFT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(LEFT_PIN), leftInterrupt, RISING);
}

void setOnLeftPressedListener(void (*listener)()) {
    onLeftPressed = listener;
}
