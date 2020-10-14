#include "SSD_13xx_SPI_Teensy_3x.h"
#include <wiring.h>

static const uint32_t _common_max_SPI_speed = 30000000;

SSD_13XX_SPI_Teensy_3x* SSD_13XX_SPI_Teensy_3x::init(
    const uint8_t cspin,
    const uint8_t dcpin,
    const uint8_t mosi,
    const uint8_t sclk,
    bool avoidSPIinit,
    uint8_t* initError
) {
    // Are we using hardware pins?
    bool hwPins = (
        (mosi == 11 || mosi == 7) && 
        (sclk == 13 || sclk == 14)
    );
    
    // If not then bail.
    if (!hwPins) {
        if (initError == 0) return NULL;
		bitSet(*initError,0);
		return NULL;
	}

    // Set up SPI.
    SPI.setMOSI(mosi);
    SPI.setSCK(sclk);
	if (!avoidSPIinit) SPI.begin();

    // If dc and cd aren't independantly selectable, then bail.
	if (!SPI.pinIsChipSelect(cspin, dcpin)) {
        if (initError == 0) return NULL;
		bitSet(*initError,1);
		return NULL;
    }

    // Create our SPI instance.
    uint8_t pcsData = SPI.setCS(cspin);
    uint8_t pcsCommand = pcsData | SPI.setCS(dcpin);
    SPISettings settings = SPISettings(_common_max_SPI_speed, MSBFIRST, SPI_MODE0);
    return new SSD_13XX_SPI_Teensy_3x(&SPI, settings, pcsCommand, pcsData);
}

SSD_13XX_SPI_Teensy_3x::SSD_13XX_SPI_Teensy_3x(
    SPIClass *spi,
    SPISettings spiSettings,
    uint8_t pcsCommand,
    uint8_t pcsData
) {
    _spi = spi;
    _spiSettings = spiSettings;
    _pcsCommand = pcsCommand;
    _pcsData = pcsData;
}

inline void SSD_13XX_SPI_Teensy_3x::startTransaction(void) {
    _spi->beginTransaction(_spiSettings);
}

inline void SSD_13XX_SPI_Teensy_3x::endTransaction(void) {
    _spi->endTransaction();
}

void SSD_13XX_SPI_Teensy_3x::closeTransaction(const uint8_t nopCmd)
{
    writecommand_last(nopCmd);
    endTransaction();
}

/**
 * Here's Paul Stoffregen SPI FIFO magic in action...
 */
void SSD_13XX_SPI_Teensy_3x::waitFifoNotFull(void) {
    uint32_t sr;
    uint32_t tmp __attribute__((unused));
    do {
        sr = KINETISK_SPI0.SR;
        if (sr & 0xF0) tmp = KINETISK_SPI0.POPR;  // drain RX FIFO
    } while ((sr & (15 << 12)) > (3 << 12));
}

inline void SSD_13XX_SPI_Teensy_3x::waitTransmitComplete(uint32_t mcr) {
    uint32_t tmp __attribute__((unused));
    while (1) {
        uint32_t sr = KINETISK_SPI0.SR;
        if (sr & SPI_SR_EOQF) break;  // wait for last transmit
        if (sr &  0xF0) tmp = KINETISK_SPI0.POPR;
    }
    KINETISK_SPI0.SR = SPI_SR_EOQF;
    SPI0_MCR = mcr;
    while (KINETISK_SPI0.SR & 0xF0) {tmp = KINETISK_SPI0.POPR;}
}

inline void SSD_13XX_SPI_Teensy_3x::writecommand_cont(const uint8_t c) {
    KINETISK_SPI0.PUSHR = c | (_pcsCommand << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
    waitFifoNotFull();
}

inline void SSD_13XX_SPI_Teensy_3x::writecommand16_cont(uint16_t c) {
    KINETISK_SPI0.PUSHR = c | (_pcsCommand << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
    waitFifoNotFull();
}

inline void SSD_13XX_SPI_Teensy_3x::writedata8_cont(uint8_t d) {
    KINETISK_SPI0.PUSHR = d | (_pcsData << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_CONT;
    waitFifoNotFull();
}

inline void SSD_13XX_SPI_Teensy_3x::writedata16_cont(uint16_t d) {
    KINETISK_SPI0.PUSHR = d | (_pcsData << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_CONT;
    waitFifoNotFull();
}

inline void SSD_13XX_SPI_Teensy_3x::writecommand_last(const uint8_t c) {
    uint32_t mcr = SPI0_MCR;
    KINETISK_SPI0.PUSHR = c | (_pcsCommand << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
    waitTransmitComplete(mcr);
}

inline void SSD_13XX_SPI_Teensy_3x::writedata8_last(uint8_t c) {
    uint32_t mcr = SPI0_MCR;
    KINETISK_SPI0.PUSHR = c | (_pcsData << 16) | SPI_PUSHR_CTAS(0) | SPI_PUSHR_EOQ;
    waitTransmitComplete(mcr);
}

inline void SSD_13XX_SPI_Teensy_3x::writedata16_last(uint16_t d) {
    uint32_t mcr = SPI0_MCR;
    KINETISK_SPI0.PUSHR = d | (_pcsData << 16) | SPI_PUSHR_CTAS(1) | SPI_PUSHR_EOQ;
    waitTransmitComplete(mcr);
}

