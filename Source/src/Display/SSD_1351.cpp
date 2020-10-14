#include "SSD_1351.h"

#include "Definitions/Registers/SSD_1351_Registers.h"
#include "Definitions/Displays/SSD_1351_128x96.h"
//#include "Definitions/Displays/SSD_1351_128x128.h"

void SSD_1351::setRemap(uint8_t remap) {
    _spi->startTransaction();
	setAddrWindow_cont(0,0,_height-1,_width-1,false);
	_spi->writecommand_cont(CMD_SETREMAP);
	_spi->writedata8_last(remap);
	_spi->endTransaction();
}

void SSD_1351::setRegister_cont(const uint8_t cmd,uint8_t data)
{
	_spi->writecommand_cont(cmd);
	_spi->writedata8_cont(data);

}

void SSD_1351::fillScreen(uint16_t color)
{

		_spi->startTransaction();
		setAddrWindow_cont(
				0,
				0,
				SSD_WIDTH - 1,
				SSD_HEIGHT - 1,
				false
		);
		_spi->_pushColors_cont(color, SSD_CGRAM);

	_spi->closeTransaction(CMD_NOP);
}

void SSD_1351::setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix)
	{
		SSD_13xx::setAddrWindow_cont(x0, y0, x1, y1, rotFix);
	
			_spi->writecommand_cont(CMD_SETCOLUMN); //Column
			_spi->writedata8_cont(x0); 
            _spi->writedata8_cont(x1);
			_spi->writecommand_cont(CMD_SETROW); //Page
			_spi->writedata8_cont(y0); 
            _spi->writedata8_cont(y1);
			
			_spi->writecommand_cont(CMD_WRITERAM);

	}
