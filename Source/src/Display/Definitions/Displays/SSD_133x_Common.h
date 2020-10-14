/**
 * Definitions common to all SSD133x displays.
 */

#ifndef SSD_133X_COMMON_H
#define SSD_133X_COMMON_H

static const int16_t SSD_WIDTH	        = 96;
static const int16_t SSD_HEIGHT 	    = 64;

static const int16_t SSD_COMSPLIT 		= 1;
static const uint8_t SSD_COLORDEPTH  	= 16;
static const uint8_t SSD_RGBORDER		= 0;
static const uint8_t SSD_DISPLAYOFFSET  = 0x00;
static const uint8_t SSD_PHASEPERIOD	= 0b10110001;
static const uint8_t SSD_SETMULTIPLEX	= 0x3F;
static const uint8_t SSD_STARTLINE		= 0x00;
static const uint8_t SSD_POWERMODE		= 0x0B;
static const uint8_t SSD_CLOCKDIV		= 0xF0;
static const uint8_t SSD_VCOMH			= 0x3E;
static const uint8_t SSD_CONTRAST_A		= 0x91;
static const uint8_t SSD_CONTRAST_B		= 0x50;
static const uint8_t SSD_CONTRAST_C		= 0x7D;
static const uint8_t SSD_VPACOLORLVL	= 0b00111111;
static const uint8_t SSD_VPBCOLORLVL	= 0b00111111;
static const uint8_t SSD_VPCCOLORLVL	= 0b00111111;

#endif
