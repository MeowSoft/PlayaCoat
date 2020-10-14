#include "SSD_13xx.h"

#include "Utils.h"
#include "Config.h"

const uint32_t SSD_CGRAM		=	SSD_WIDTH * SSD_HEIGHT;

SSD_13xx::SSD_13xx(SSD_13XX_SPI *spi, uint8_t resetPin)
{
    _spi = spi;
    _resetPin = resetPin;
    
}

void SSD_13xx::setRotation(uint8_t m)
{
	_rotation = m % 4; // can't be higher than 3
	_portrait = false;
	_remapReg &= ~(0x1B);//clear bit 0,1,3,4
	_width  = SSD_WIDTH;
	_height = SSD_HEIGHT;


    if (_rotation == PORTRAIT || _rotation == PORTRAIT_180) {
        swapVals(_width,_height);
        _portrait = true;
    }

    setRotationRemap();

	// if (_rotation == 0){
	// 	#if defined(_SSD_1331_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 1));//bit 4 & 1
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 4));//bit 4
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 4));//(1)
	// 	#else
	// 		//TODO
	// 	#endif
	// } else if (_rotation == 1){
	// 	#if defined(_SSD_1331_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 0));//bit 4 & 0
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 1) | (1 << 0));//bit 4 & 1 & 0
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 1) | (1 << 0));//(2)
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#else
	// 		//TODO
	// 	#endif
	// } else if (_rotation == 2){
	// 	#if defined(_SSD_1331_REG_H_)
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 1));//bit 1
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 1));//(3)
	// 	#else
	// 		//TODO
	// 	#endif
	// } else {
	// 	#if defined(_SSD_1331_REG_H_)
	// 		_remapReg |= ((1 << 1) | (1 << 0));//bit 1 & 0
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 0));//bit 0
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 0));//(0)
	// 		swapVals(_width,_height);
	// 		_portrait = true;
	// 	#else
	// 		//TODO
	// 	#endif
	// }


    setRemap(_remapReg);

	// _spi->startTransaction();
	// 	setAddrWindow_cont(0,0,_height-1,_width-1,false);
	// 	_spi->writecommand_cont(CMD_SETREMAP);//set remap
	// 	#if defined(_SSD_USECMDASDATA)
	// 		_spi->writecommand_last(_remapReg);
	// 	#else
	// 		writedata8_last(_remapReg);
	// 	#endif
	// _spi->endTransaction();
}



void SSD_13xx::_sendColor_cont(uint8_t r,uint8_t g,uint8_t b)
	{
		_spi->writecommand_cont(r);
        _spi->writecommand_cont(g);
        _spi->writecommand_cont(b);
	}
	
	void SSD_13xx::_fillUtility(bool filling)
	{
        static bool _filled = false;
		if (filling != _filled){
			_filled = filling;
			_spi->writecommand_cont(CMD_FILL);
			if (_filled){
				_spi->writecommand_cont(0x01);
			} else {
				_spi->writecommand_cont(0x00);
			}
		}
	}



	void SSD_13xx::_convertColor(uint16_t color,uint8_t &r,uint8_t &g,uint8_t &b)
	{
		r = (uint8_t)((color >> 11) << 1);
		g =	(uint8_t)((color >> 5) & 0x3F);
		b = (uint8_t)((color << 1) & 0x3F);
	}
		


void SSD_13xx::setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix)
	{
		if (rotFix && _portrait){
			swapVals(x0, y0);
			swapVals(x1, y1);
		}

	}


// void SSD_13xx::setRegister_cont(const uint8_t cmd,uint8_t data)
// {
// 	_spi->writecommand_cont(cmd);
// 	#if defined(_SSD_USECMDASDATA)
// 		_spi->writecommand_cont(data);
// 	#else
// 		_spi->writedata8_cont(data);
// 	#endif
// }




void SSD_13xx::initPre() {

	setColorDepth(SSD_COLORDEPTH);
	setColorOrder(SSD_RGBORDER);

    toggleReset();
    delay(30);
	_spi->startTransaction();


        if (SSD_COMSPLIT == 1){
			_remapReg |= ((1 << 5));
		} else {
			_remapReg |= ((0 << 5));
		}
        
}

void SSD_13xx::setColorDepth(uint8_t depth)
{
	if (depth == 16){
		//_colorDepth = 16;
		_remapReg |= ((0 << 7) | (1 << 6));
	#if defined(_SSD_1351_REG_H_)
	} else if (depth == 18) {
		_colorDepth = 16;
		_remapReg |= ((1 << 7) | (0 << 6));
	#endif
	} else {
		//_colorDepth = 8;
		_remapReg |= ((0 << 7) | (0 << 6));
	}
}

void SSD_13xx::setColorOrder(bool order)
{
	#if defined(_SSD_1331_REG_H_) || defined(_SSD_1351_REG_H_)
		_remapReg |= ((order << 2));
	#endif
}


void SSD_13xx::initPost() {
    //setAddrWindow_cont(0,0,SSD_WIDTH-1,SSD_HEIGHT-1,false);// ???
	//_pushColors_cont(_defaultBgColor, SSD_CGRAM);//???
	//Normal Display and turn ON
	_spi->writecommand_cont(CMD_NORMALDISPLAY);
	_spi->writecommand_last(CMD_DISPLAYON);
	_spi->endTransaction();
	delay(60);
	setRotation(SSD_DEFAULT_ROTATION);
	fillScreen(0x1234);

	delay(1);
	changeMode(NORMAL);
}

/*
This change the mode of the display as:
	NORMAL: Normal mode.
	PWRSAVE: Consume much less power
	PROTECT: Display protect his serial comm, accept only a change mode as normal to exit protected state
	INVERT: It invert the display
	DISP_ON: Turn on display (if off) and enable backlight pin if used
	DISP_DIM: The all display goe dim
	DISP_OFF: The opposite of above
*/
void SSD_13xx::changeMode(const enum SSD_13XX_modes m)
{
	if (m != _currentMode){
		_spi->startTransaction();
		switch(m){

			case NORMAL:
				if (_currentMode == 6) {//was in off display?
					_spi->writecommand_cont(CMD_DISPLAYON);
				}
				/*
				if (_currentMode == 2) {//was in idle?
					//writecommand_cont(CMD_IDLEOF);
				}
				*/
				
				#if defined(SSD_1331_REGISTERS_H) || defined(SSD_1332_REGISTERS_H)
				if (_currentMode == 8) {//was in powerMode?
					setRegister_cont(CMD_POWERMODE,SSD_POWERMODE);
					//delay(120);//needed
				}
				#endif
				
				//SSD1332 should need only CMD_NORMALDISPLAY!?!
				#if defined(SSD_1331_REGISTERS_H)
				if (_currentMode == 4){//was inverted?
					_spi->writecommand_cont(CMD_DINVOF);
				}
				#endif

				#if defined(SSD_1331_REGISTERS_H) || defined(SSD_1351_REGISTERS_H)
				if (_currentMode == 9){//was in protect mode?
					setRegister_cont(CMD_CMDLOCK,0x12);//unlock
				}
				#endif
				/*
				if (_currentMode == 12 || _currentMode == 13){//all on or off?
					//nothing
				}
				*/
				_spi->writecommand_cont(CMD_NORMALDISPLAY);
				_currentMode = 0;
			break;

			case PWRSAVE: //power mode ON
				#if defined(SSD_1331_REGISTERS_H) || defined(SSD_1332_REGISTERS_H)
					_spi->writecommand_cont(CMD_POWERMODE);
					_spi->writecommand_last(0x1A);
					_currentMode = 8;
					delay(5);//needed
				#else
					//TODO: exist?
					//writedata8_last(0x1A);
				#endif
				_spi->endTransaction();
				return;

			case PROTECT:
				#if defined(SSD_1331_REGISTERS_H) || defined(SSD_1351_REGISTERS_H)
				setRegister_cont(CMD_CMDLOCK,0x16);//lock
				_currentMode = 9;
				#else
					endTransaction();
					return;
				#endif
			break;


			case ALL_ON:
				_spi->writecommand_cont(CMD_DISPLAYALLON);
				_currentMode = 12;
			break;
			case ALL_OFF:
				_spi->writecommand_cont(CMD_DISPLAYALLOFF);
				_currentMode = 13;
			break;
            
			case INVERT:
				_spi->writecommand_cont(CMD_INVERTDISPLAY);//OK
				_currentMode = 4;
			break;
			case DISP_ON:
				_spi->writecommand_cont(CMD_DISPLAYON);
				_currentMode = 5;
			break;
			case DISP_OFF:
				_spi->writecommand_cont(CMD_DISPLAYOFF);
				_currentMode = 6;
			break;
			/*
			case DISP_DIM:
				writecommand_cont(CMD_DISPLAYDIM);
				_currentMode = 7;
			break;
			*/
			default:
				_spi->endTransaction();
				return;
			break;
		}
		_spi->closeTransaction(CMD_NOP);
	}
}


void SSD_13xx::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	//if (boundaryCheck(x,y)) return;
	//if ((x < 0) || (y < 0)) return;
	_spi->startTransaction();
	drawPixel_cont(x,y,color);
	_spi->closeTransaction(CMD_NOP);
}
void SSD_13xx::drawPixel_cont(int16_t x, int16_t y, uint16_t color)
{
		setAddrWindow_cont(x, y, x + 1, y + 1,true);
		_spi->writedata16_cont(color);
}

void SSD_13xx::toggleReset() 
{
    if (_resetPin != 255)
    {
        pinMode(_resetPin, OUTPUT);
        digitalWrite(_resetPin, HIGH);
        delay(10);
        digitalWrite(_resetPin, LOW);
        delay(10);
        digitalWrite(_resetPin, HIGH);
        delay(10);
    }
}
