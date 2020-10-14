
#include "SSD_133x.h"
#include "_display/SSD_1331_96x64.h"


void SSD_133x::init() {
    SSD_13xx::initPre();
    initSSD1331();
    SSD_13xx::initPost();
}

void SSD_133x::initSSD1331()
{
 _spi->writecommand_cont(CMD_DISPLAYOFF);
		setRegister_cont(CMD_CLOCKDIV,SSD_CLOCKDIV);
		setRegister_cont(CMD_SETMULTIPLEX,SSD_SETMULTIPLEX);
		setRegister_cont(CMD_STARTLINE,SSD_STARTLINE);
		setRegister_cont(CMD_DISPLAYOFFSET,SSD_DISPLAYOFFSET);
		setRegister_cont(CMD_PHASEPERIOD,SSD_PHASEPERIOD);
		setRegister_cont(CMD_SETMASTER,SSD_SETMASTER);
		setRegister_cont(CMD_POWERMODE,SSD_POWERMODE);
		setRegister_cont(CMD_MASTERCURRENT,SSD_MASTERCURRENT);

setGrayscale();
        // // Set grayscale
		// #if defined(SSD_GAMMASET)
        //     //SSD1331:
		// 	_spi->writecommand_cont(CMD_GRAYSCALE); 
        //     for (uint8_t i =0;i<32;i++){
        //         _spi->writecommand_cont(SSD_GRAYTABLE[i]);
        //     }
		// #else
        // // SSD1332:
		// 	writecommand_cont(CMD_LINEARGRAY);
		// #endif

		setRegister_cont(CMD_CONTRASTA,SSD_CONTRAST_A);
		setRegister_cont(CMD_CONTRASTB,SSD_CONTRAST_B);
		setRegister_cont(CMD_CONTRASTC,SSD_CONTRAST_C);
		setRegister_cont(CMD_VPACOLORLVL,SSD_VPACOLORLVL);
		setRegister_cont(CMD_VPBCOLORLVL,SSD_VPBCOLORLVL);
		setRegister_cont(CMD_VPCCOLORLVL,SSD_VPCCOLORLVL);
		#if defined(_SSD_1331_96X64_H)
			_spi->writecommand_cont(CMD_DIMMODESET);
			_spi->writecommand_cont(0);
			_spi->writecommand_cont(SSD_DIMMDESET_A);
			_spi->writecommand_cont(SSD_DIMMDESET_B);
			_spi->writecommand_cont(SSD_DIMMDESET_C);
			_spi->writecommand_cont(SSD_DIMMDESET_PC);
			setRegister_cont(CMD_PRECHARGE,SSD_PRECHARGE);
			setRegister_cont(CMD_PRECHARGEA,SSD_PRECHARGE_A);
			setRegister_cont(CMD_PRECHARGEB,SSD_PRECHARGE_B);
			setRegister_cont(CMD_PRECHARGEC,SSD_PRECHARGE_C);
			setRegister_cont(CMD_PRECHARGELEVEL,SSD_PRECHARGELEVEL);
		#endif
		setRegister_cont(CMD_VCOMH,SSD_VCOMH);
		_fillUtility(1);   
}

void SSD_133x::fillScreen(uint16_t color)
{
		uint8_t r1,g1,b1;
		_convertColor(color,r1,g1,b1);
		_spi->startTransaction();
		_fillUtility(1);
		_spi->writecommand_cont(CMD_DRAWRECT);
		_spi->writecommand16_cont(0);
		_spi->writecommand_cont(SSD_WIDTH-1);
		_spi->writecommand_cont(SSD_HEIGHT-1);
		_sendColor_cont(r1,g1,b1);
		_sendColor_cont(r1,g1,b1);
		delayMicroseconds(CMD_DLY_FILL);//CMD_DLY_FILL

	_spi->closeTransaction(CMD_NOP);
}

void SSD_133x::setRemap(uint8_t remap) {
    _spi->startTransaction();
		setAddrWindow_cont(0,0,_height-1,_width-1,false);
		_spi->writecommand_cont(CMD_SETREMAP);//set remap

			_spi->writecommand_last(remap);
	
	_spi->endTransaction();
}

void SSD_133x::setRegister_cont(const uint8_t cmd,uint8_t data)
{
	_spi->writecommand_cont(cmd);

		_spi->writecommand_cont(data);

}

void SSD_133x::setAddrWindow_cont(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,bool rotFix)
	{
		// if (rotFix && _portrait){
		// 	swapVals(x0, y0);
		// 	swapVals(x1, y1);
		// }
        SSD_13xx::setAddrWindow_cont(x0, y0, x1, y1, rotFix);
        
	
			_spi->writecommand_cont(CMD_SETCOLUMN); //Column
			_spi->writecommand_cont(x0); _spi->writecommand_cont(x1);
			_spi->writecommand_cont(CMD_SETROW); //Page
			_spi->writecommand_cont(y0); _spi->writecommand_cont(y1);

	}



