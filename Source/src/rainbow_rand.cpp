#include "rainbow_rand.h"

#define R 0x00ff0000
#define O 0x00aa5500
#define Y 0x007f7f00
#define G 0x0000ff00
#define B 0x000000ff
#define I 0x005500aa
#define V 0x007f007f

static uint32_t colors[] = { R, O, Y, G, B, I, V };

void rainbowRand_setup(uint32_t** buffer, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t color = colors[random(0, 7)];
            buffer[x][y] = color;
        }
    }
}

void rainbowRand_loop(uint32_t** buffer, int width, int height) {
    rainbowRand_setup(buffer, width, height);
}
