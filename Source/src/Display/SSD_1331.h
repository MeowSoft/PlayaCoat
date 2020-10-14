#ifndef SSD_1331_H
#define SSD_1331_H

#include "SSD_133x.h"

class SSD_1331 : public SSD_133x {
    public:
    SSD_1331(SSD_13XX_SPI *spi, uint8_t resetPin) : SSD_133x(spi, resetPin) {}
    protected:
    void setGrayscale();
    void setRotationRemap();
};

#endif
