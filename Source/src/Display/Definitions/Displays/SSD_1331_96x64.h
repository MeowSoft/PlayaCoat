/**
 * Definitions for SSD1331 displays.
 */

#ifndef SSD_1331_96X64_H
#define SSD_1331_96X64_H

#include "SSD_133x_Common.h"

// Timing values for modules except for red PCB.
#ifndef SSD_1331_REDPCB_H
static const int CMD_DLY_LINE			    = 200;
static const int CMD_DLY_FILL			    = 400;
static const int CMD_DLY_MIN			    = 4;
#endif

static const uint8_t SSD_SETMASTER		    = 0x8E;
static const uint8_t SSD_PRECHARGE		    = 0x31;
static const uint8_t SSD_PRECHARGE_A	    = 0x64;
static const uint8_t SSD_PRECHARGE_B	    = 0x78;
static const uint8_t SSD_PRECHARGE_C	    = 0x64;
static const uint8_t SSD_PRECHARGELEVEL     = 0x3A;
static const uint8_t SSD_MASTERCURRENT	    = 0x06;
static const uint8_t SSD_DIMMDESET_A	    = 128;
static const uint8_t SSD_DIMMDESET_B	    = 128;
static const uint8_t SSD_DIMMDESET_C	    = 128;
static const uint8_t SSD_DIMMDESET_PC	    = 0x0F;

static const uint8_t SSD_GRAYTABLE[32] = {
    0x01,0x03,0x05,0x07,0x0A,0x0D,0x10,0x13,
    0x16,0x19,0x1C,0x20,0x24,0x28,0x2C,0x30,
    0x34,0x38,0x3C,0x40,0x44,0x48,0x4C,0x50,
    0x54,0x58,0x5C,0x60,0x64,0x68,0x6C,0x70
};

#endif
