#include "SSD_1331.h"

#include "Definitions/Displays/SSD_1331_96x64.h"
//#include "Definitions/Displays/SSD_1331_REDPCB.h"
#include "Definitions/Registers/SSD_1331_registers.h"

/**
 * Set grayscale table.
 */
void SSD_1331::setGrayscale() {
    _spi->writecommand_cont(CMD_GRAYSCALE); 
    for (uint8_t i =0;i<32;i++){
        _spi->writecommand_cont(SSD_GRAYTABLE[i]);
    }
}

void SSD_1331::setRotationRemap() {
  

    switch (_rotation) {
        case PORTRAIT:
            _remapReg |= ((1 << 4) | (1 << 1));
        break;
        case LANDSCAPE:
            _remapReg |= ((1 << 4) | (1 << 0));
        break;
        case PORTRAIT_180:
        break;
        case LANDSCAPE_180:
            _remapReg |= ((1 << 1) | (1 << 0));
        break;
    }

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
    //     swapVals(_width,_height);
    //     _portrait = true;
	// 	#if defined(_SSD_1331_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 0));//bit 4 & 0
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 1) | (1 << 0));//bit 4 & 1 & 0
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 4) | (1 << 1) | (1 << 0));//(2)
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
    //     swapVals(_width,_height);
    //     _portrait = true;
	// 	#if defined(_SSD_1331_REG_H_)
	// 		_remapReg |= ((1 << 1) | (1 << 0));//bit 1 & 0
	// 	#elif defined(_SSD_1332_REG_H_)
	// 		_remapReg |= ((1 << 0));//bit 0
	// 	#elif defined(_SSD_1351_REG_H_)
	// 		_remapReg |= ((1 << 0));//(0)
	// 	#else
	// 		//TODO
	// 	#endif
	// }

}
