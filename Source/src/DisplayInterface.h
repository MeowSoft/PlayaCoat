#ifndef DISPLAY_INTERFACE_H
#define DISPLAY_INTERFACE_H

#include "Digit.h"

// class DisplayInterface {
//     public:
//     virtual void DrawDigit(EditableDigit digit) = 0;
//     virtual void DrawDigit(Digit digit) = 0;
// }

// class SSD_13XX_Display : DisplayInterface {

//     public:
//     SSD_13XX_Display(SSD_13XX* display);
//     virtual void DrawDigit(EditableDigit digit);
//     virtual void DrawDigit(Digit digit);

//     private:
//     SSD_13XX* _display;

//     void getTextBounds(const __FlashStringHelper *str, int16_t x,
//                                  int16_t y, int16_t *x1, int16_t *y1,
//                                  uint16_t *w, uint16_t *h);

//     void charBounds(unsigned char c, int16_t *x, int16_t *y,
//                               int16_t *minx, int16_t *miny, int16_t *maxx,
//                               int16_t *maxy);
// }

#endif
