#include "random.h"

static uint32_t* buffer;

static int _displayX;
static int _displayY;
static int _displaySize;

uint32_t cappedRand() {

    uint32_t rand = random(0, 0x00ffffff);

    int sum = 
        (rand & 0xff) +
        ((rand >> 8) & 0xff) + 
        ((rand >> 16) & 0xff);

    int diff = sum - 256;

    if (diff < 0) return rand;

    for (int x = (diff / 3); x > 0; x--) {
        rand -= 0x00010101;
    }
    return rand;
}

void show(OctoWS2811 leds) {
    for (int x = 0; x < _displaySize; x++) {
        leds.setPixel(x, buffer[x]);
    }
    leds.show();
}

void random_setup(int displayX, int displayY) {
    _displayX = displayX;
    _displayY = displayY;
    _displaySize = displayX * displayY;
    buffer = (uint32_t*) malloc(_displaySize * 4);
}

void random_loop(OctoWS2811 leds) {
    for (int x = 0; x < _displaySize; x++) {
        buffer[x] = cappedRand();
    }
    show(leds);
}
