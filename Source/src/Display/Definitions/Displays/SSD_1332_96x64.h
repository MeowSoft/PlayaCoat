/**
 * Definitions for SSD1332 displays.
 */

#ifndef SSD_1332_96X64_H
#define SSD_1332_96X64_H

#include "SSD_133x_Common.h"

static const int CMD_DLY_LINE			= 300;
static const int CMD_DLY_FILL			= 600;
static const int CMD_DLY_MIN			= 10;

static const uint8_t SSD_SETMASTER		= 0x8F;
static const uint8_t SSD_MASTERCURRENT	= 0x0F;

#endif
