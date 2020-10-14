#ifndef SSD_1351_H
#define SSD_1351_H

#include "SSD_13xx.h"
#include "SPI/SSD_1351_SPI_Teensy_3x.h"

class SSD_1351 : public SSD_13xx {
    public:
    void fillScreen(uint16_t color);

    protected:

    SSD_1351_SPI_Teensy_3x *_spi;

    void setRemap(uint8_t remap);
    void setRegister_cont(const uint8_t cmd,uint8_t data);
    void setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix);
};

#endif
