/**
 * This file defines all registers common to both SSD1331 and SSD1332
 */

#ifndef SSD_133X_REGISTERS_H
#define SSD_133X_REGISTERS_H

static const uint8_t CMD_NOP     			= 0xE3;
static const uint8_t CMD_DRAWLINE 			= 0x21;
static const uint8_t CMD_DRAWRECT 			= 0x22;
static const uint8_t CMD_DRAWCOPY 			= 0x23;
static const uint8_t CMD_DIMWINDOW 			= 0x24;
static const uint8_t CMD_CLRWINDOW 			= 0x25;
static const uint8_t CMD_FILL 				= 0x26;
static const uint8_t CMD_SCROLL_OFF 		= 0x2E;
static const uint8_t CMD_SCROLL_ON  		= 0x2F;
static const uint8_t CMD_SCROLL_SET  		= 0x2F;
static const uint8_t CMD_STARTLINE 			= 0xA1;
static const uint8_t CMD_DISPLAYALLON 		= 0xA5;
static const uint8_t CMD_DISPLAYALLOFF 		= 0xA6;
static const uint8_t CMD_PHASEPERIOD 		= 0x12;
static const uint8_t CMD_CONTRASTA 			= 0x81;
static const uint8_t CMD_CONTRASTB 			= 0x82;
static const uint8_t CMD_CONTRASTC 			= 0x83;
static const uint8_t CMD_MASTERCURRENT 		= 0x87;
static const uint8_t CMD_SETREMAP 			= 0xA0;
static const uint8_t CMD_DISPLAYOFFSET 		= 0xA2;
static const uint8_t CMD_SETMULTIPLEX 		= 0xA8;
static const uint8_t CMD_SETMASTER			= 0xAD;
static const uint8_t CMD_POWERMODE 			= 0xB0;
static const uint8_t CMD_CLOCKDIV 			= 0xB3;
static const uint8_t CMD_GRAYSCALE 			= 0xB8;
static const uint8_t CMD_LINEARGRAY 		= 0xB9;
static const uint8_t CMD_VCOMH 				= 0xBE;
static const uint8_t CMD_VPACOLORLVL 		= 0xBB;
static const uint8_t CMD_VPBCOLORLVL 		= 0xBC;
static const uint8_t CMD_VPCCOLORLVL 		= 0xBD;
static const uint8_t CMD_NORMALDISPLAY   	= 0xA4;
static const uint8_t CMD_INVERTDISPLAY   	= 0xA7;
static const uint8_t CMD_DISPLAYOFF 		= 0xAE;
static const uint8_t CMD_DISPLAYDIM 		= 0xAC;
static const uint8_t CMD_DISPLAYON  		= 0xAF;
static const uint8_t CMD_SETCOLUMN   		= 0x15;
static const uint8_t CMD_SETROW   			= 0x75;

/** Remap register structure for SSD1331:
 * 
 * Bit: 0                           1
 * 0    H Addr increment            V addr increment
 * 1    RAM col 0->95               RAM col 95->0
 * 2    RGB                         GBR
 * 3    L/R swap disable            L/R swap enable
 * 4    Scan from COM0 to COM(n-1)  Scan from COM(n-1) to COM0
 * 5    Disable com split           Enable com split
 *
 *      00                          01                          10
 * 6,7  256 colors                  65k colors format 1         65k colors format 2
 */

/** Remap register structure for SSD1332:
 * 
 * Bit: 0                           1
 * 0    H Addr increment            V addr increment
 * 1    RAM col 0->95               RAM col 95->0
 * 2    NA
 * 3    NA
 * 4    Scan from COM0 to COM(n-1)  Scan from COM(n-1) to COM0
 * 5    Disable com split           Enable com split
 *
 *      00                          01
 * 6,7  256 colors                  65k colors       
 */

#endif
