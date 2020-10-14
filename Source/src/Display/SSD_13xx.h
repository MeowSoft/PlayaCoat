#ifndef SSD_13XX_H
#define SSD_13XX_H

#include "SPI/SSD_13xx_SPI.h"

enum SSD_13XX_modes{
    NORMAL = 0,
    PWRSAVE,
    INVERT,
    DISP_ON, 
    DISP_DIM,
    DISP_OFF,
    PROTECT,
    ALL_ON,
    ALL_OFF
};

typedef enum SSD_13xx_Rotation_Modes {
    LANDSCAPE,
    PORTRAIT,
    LANDSCAPE_180,
    PORTRAIT_180
} SSD_13xx_Rotation_Modes_t;

class SSD_13xx
{
public:

    SSD_13xx(SSD_13XX_SPI *spi, uint8_t resetPin);

    virtual void init() = 0;

    void setRotation(uint8_t m);
    virtual void fillScreen(uint16_t color) = 0;
    virtual void changeMode(const enum SSD_13XX_modes m);
    void		drawPixel(int16_t x, int16_t y, uint16_t color);

protected:

    static const uint32_t	SSD_CGRAM;//		=	SSD_WIDTH * SSD_HEIGHT;


    SSD_13XX_SPI *_spi;
    uint8_t _resetPin;
    volatile uint8_t _remapReg;
    volatile int16_t		_width, _height;

	uint8_t					_rotation;
	boolean					_portrait;
	uint8_t					_currentMode;

    void toggleReset();
    
    
    virtual void setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix);


    static void _convertColor(uint16_t color,uint8_t &r,uint8_t &g,uint8_t &b);
    void _fillUtility(bool filling);
    void _sendColor_cont(uint8_t r,uint8_t g,uint8_t b);
    void drawPixel_cont(int16_t x, int16_t y, uint16_t color);
    void initPre();
    void initPost();
    void setColorDepth(uint8_t depth);
    void setColorOrder(bool order);
    virtual void setRemap(uint8_t remap) = 0;
    virtual void setRegister_cont(const uint8_t cmd,uint8_t data) = 0;
    virtual void setRotationRemap() = 0;
};

#endif
