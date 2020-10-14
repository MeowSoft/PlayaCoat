#ifndef SSD_13XX_SPI_TEENSY_3X_H
#define SSD_13XX_SPI_TEENSY_3X_H

#include <SPI.h>
#include "SSD_13xx_SPI.h"

/**
 * This is the Teensy 3.x version of the 
 * SPI interface for an SSD_13XX display.
 */
class SSD_13XX_SPI_Teensy_3x : public SSD_13XX_SPI {

public:

    /**
     * Create the SPI interface with the given pins.
     */
    static SSD_13XX_SPI_Teensy_3x* init(
        const uint8_t cspin,
        const uint8_t dcpin,
        const uint8_t mosi,
        const uint8_t sclk,
        bool avoidSPIinit,
        uint8_t* initError
    );

    SSD_13XX_SPI_Teensy_3x(
        SPIClass *spi,
        SPISettings spiSettings,
        uint8_t pcsCommand,
        uint8_t pcsData
    );

    void startTransaction(void) __attribute__((always_inline));
    void endTransaction(void) __attribute__((always_inline));
    void closeTransaction(const uint8_t nopCmd);
    void writecommand_cont(const uint8_t c) __attribute__((always_inline));
    void writecommand16_cont(uint16_t c) __attribute__((always_inline));
    void writedata8_cont(uint8_t d) __attribute__((always_inline));
    void writedata16_cont(uint16_t d) __attribute__((always_inline));
    void writecommand_last(const uint8_t c) __attribute__((always_inline));
    void writedata8_last(uint8_t c) __attribute__((always_inline));
    void writedata16_last(uint16_t d) __attribute__((always_inline));

    

private:

    SPISettings _spiSettings;
    SPIClass *_spi;
    uint8_t _pcsData; 
    uint8_t _pcsCommand;

    void waitFifoNotFull(void);
    void waitTransmitComplete(uint32_t mcr) __attribute__((always_inline));
};

#endif
