#ifndef SSD_133X_H
#define SSD_133X_H

#include "SSD_13xx.h"

class SSD_133x : public SSD_13xx {

    public:
        SSD_133x(SSD_13XX_SPI *spi, uint8_t resetPin) : SSD_13xx(spi, resetPin) {}
        void init();
void fillScreen(uint16_t color);

        protected:
void setRemap(uint8_t remap);
void setRegister_cont(const uint8_t cmd,uint8_t data);
virtual void setGrayscale() = 0;
void setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix);

        private: 
     void initSSD1331();
     
};

#endif