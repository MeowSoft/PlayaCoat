#ifndef SSD_1351_SPI_TEENSY_3X_H
#define SSD_1351_SPI_TEENSY_3X_H

#include "SSD_13xx_SPI_Teensy_3x.h"

class SSD_1351_SPI_Teensy_3x : public SSD_13XX_SPI_Teensy_3x {
    public:
    void _pushColors_cont(uint16_t data,uint32_t times);
};

#endif
