#ifndef SSD_13XX_SPI_H
#define SSD_13XX_SPI_H

#include <Arduino.h>

/**
 * This class defines a generic SPI interface to an SSD_13XX display.
 */
class SSD_13XX_SPI
{
public:

    virtual void startTransaction(void) = 0;
    virtual void endTransaction(void) 
    __attribute__((always_inline)) = 0;
    virtual void closeTransaction(const uint8_t nopCmd) = 0;
    virtual void writecommand_cont(const uint8_t c) 
    __attribute__((always_inline)) = 0;
    virtual void writecommand16_cont(uint16_t c) 
    __attribute__((always_inline)) = 0;
    virtual void writedata8_cont(uint8_t d) 
    __attribute__((always_inline)) = 0;
    virtual void writedata16_cont(uint16_t d) 
    __attribute__((always_inline)) = 0;
    virtual void writecommand_last(const uint8_t c) 
    __attribute__((always_inline)) = 0;
    virtual void writedata8_last(uint8_t c) 
    __attribute__((always_inline)) = 0;
    virtual void writedata16_last(uint16_t d) 
    __attribute__((always_inline)) = 0;
};


#endif