#include <Arduino.h>
#include <OctoWS2811.h>

#include "random.h"
#include "rainbow_scroll.h"
#include "rainbow_rand.h"

// #define SERIAL
// #define RANDOM
// #define RAINBOW_SCROLL
#define RAINBOW_RANDOM

#define LEDS_PER_STRIP 28

#define BUFFER_WIDTH 16
#define BUFFER_HEIGHT 14

// LED blinker.
bool ledState = false;

// Allocs for OctoWS.
DMAMEM int displayMemory[LEDS_PER_STRIP * 6];
int drawingMemory[LEDS_PER_STRIP * 6];
const int config = WS2811_GRB | WS2811_800kHz;
OctoWS2811 leds(LEDS_PER_STRIP, displayMemory, drawingMemory, config);

// Buffer to hold pixel data.
static uint32_t* buffer[BUFFER_WIDTH];

// col. strip. px addrs.
// 0 -> 0 -> px 0 .. 13
// 1 -> 0 -> px 27 .. 14
// 2 -> 3 -> px 84 .. 93
// 3 -> 3 -> px 103 .. 94
// 4 -> 1 -> px 28 .. 41
// 5 -> 1 -> px 55 .. 42
// 6 -> 2 -> px 56 .. 69
// 7 -> 2 -> px 83 .. 70
// 8 -> 7 -> px 180 .. 193
// 9 -> 7 -> px 203 .. 194
// 10 -> 4 -> px 104 .. 117
// 11 -> 4 -> px 131 .. 118
// 12 -> 6 -> px 160 .. 169
// 13 -> 6 -> px 179 .. 170
// 14 -> 5 -> px 132 .. 145
// 15 -> 5 -> px 159 .. 146

static int addrMap[] = { 0, 27, 84, 103, 28, 55, 56, 83, 180, 203, 104, 131, 160, 179, 132, 159 };

// Map an x, y location in a 2d array to the actual pixel address.
int getPixelAddr(int x, int y) {
    switch (x) {
        case 2:
        case 12:
            if (y < 10) {
                return (addrMap[x] + y);
            } 

            return -1;
            
        case 3:
        case 13:
            if (y < 10) {
                return (addrMap[x] - y);
            }

            return -1;

        case 0:
        case 4:
        case 6:
        case 8:
        case 10:
        case 14:
            return (addrMap[x] + y);

        case 1:
        case 5:
        case 7:
        case 9:
        case 11:
        case 15:
            return (addrMap[x] - y);

        default:
            return -1;
    }
}

/**
 * Write pixel data from 2d array buffer out to LEDs and then show it.
 */
void pushPixelData(uint32_t** buffer) {
    for (int x = 0; x < BUFFER_WIDTH; x ++) { 
        for (int y = 0; y < BUFFER_HEIGHT; y ++) {
            uint32_t color = buffer[x][y];
            int addr = getPixelAddr(x, y);
            leds.setPixel(addr, color);
        }
    }
    while (leds.busy()) {;}
    leds.show();
}

void setup() {

    // Init serial.
    // #ifdef SERIAL
    // Serial.begin(9600);
    // while (!Serial) {;}
    // #endif

    // Init pixel buffer.
    for (int x = 0; x < BUFFER_WIDTH; x++) {
        buffer[x] = (uint32_t*) malloc(BUFFER_HEIGHT * 4);
    }

    // Set LED pin.
    pinMode(LED_BUILTIN, OUTPUT);

    // Serial.println("Start!");

    // Init random.
    #ifdef RANDOM
    random_setup(28, 8);
    #endif

    // Init rainbow scroll.
    #ifdef RAINBOW_SCROLL
    rainbow_scroll_setup(buffer, BUFFER_WIDTH, BUFFER_HEIGHT);
    #endif

    // Init rainbow random.
    #ifdef RAINBOW_RANDOM
    rainbowRand_setup(buffer, BUFFER_WIDTH, BUFFER_HEIGHT);
    #endif

    // Init octo.
    leds.begin();
}

void loop() {

    // Blink LED.
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;

    // Loop random.
    #ifdef RANDOM
    random_loop(leds);
    #endif

    // Loop rainbow scroll.
    #ifdef RAINBOW_SCROLL
    rainbow_scroll_loop(buffer, BUFFER_WIDTH, BUFFER_HEIGHT);
    #endif

    // Loop rainbow random.
    #ifdef RAINBOW_RANDOM
    rainbowRand_loop(buffer, BUFFER_WIDTH, BUFFER_HEIGHT);
    #endif

    // Show pixel data.
    pushPixelData(buffer);
    delay(200);
}
