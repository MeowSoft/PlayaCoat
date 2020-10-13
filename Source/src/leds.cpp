
#include <Arduino.h>

#define LED_PIN 4

void ledsOn() {
    digitalWrite(LED_PIN, true);
}

void ledsOff() {
    digitalWrite(LED_PIN, false);
}

void ledsSetUp() {
    pinMode(LED_PIN, OUTPUT);
    ledsOff();
}
