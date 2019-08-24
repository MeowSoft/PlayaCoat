#include "rainbow_scroll.h"
#include <Arduino.h>

#define R 0x00ff0000
#define O 0x00aa5500
#define Y 0x007f7f00
#define G 0x0000ff00
#define B 0x000000ff
#define I 0x005500aa
#define V 0x007f007f

void rainbow_scroll_setup(uint32_t** buffer, int width, int height) {
    uint32_t colors[] = { R, O, Y, G ,B, I, V };
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t c = colors[(x + y) % 7];
            // Serial.printf("x: %d, y: %d c: %x\r\n", x, y, c);
            buffer[x][y] = c;
        }
    }
}

void rainbow_scroll_loop(uint32_t** buffer, int width, int height) {
    for (int y = 0; y < height; y++) {
        uint32_t tmp = buffer[width - 1][y];
        for (int x = 0; x < (width - 1); x++) {
            buffer[x + 1][y] = buffer[x][y];
        }
        buffer[0][y] = tmp;
    }
}
