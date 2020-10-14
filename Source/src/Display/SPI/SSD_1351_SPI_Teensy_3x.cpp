#include "SSD_1351_SPI_Teensy_3x.h"

void SSD_1351_SPI_Teensy_3x::_pushColors_cont(uint16_t data,uint32_t times)
	{
		do {
			writedata16_cont(data);
		} while (--times > 0);
	}