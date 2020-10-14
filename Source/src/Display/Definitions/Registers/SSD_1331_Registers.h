/**
 * This file defines registers only available in SSD1331.
 */

#ifndef SSD_1331_REGISTERS_H
#define SSD_1331_REGISTERS_H

#include "SSD_133x_registers.h"

static const uint8_t CMD_DINVOF  			= 0x20;
static const uint8_t CMD_DIMMODESET 		= 0xAB;
static const uint8_t CMD_PRECHARGE 			= 0xB1;
static const uint8_t CMD_PRECHARGEA 		= 0x8A;
static const uint8_t CMD_PRECHARGEB			= 0x8B;
static const uint8_t CMD_PRECHARGEC 		= 0x8C;
static const uint8_t CMD_PRECHARGELEVEL 	= 0xBB;
static const uint8_t CMD_CMDLOCK	 		= 0xFD;

#endif
