#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include "./Display/SPI/SSD_13xx_SPI.h"
#include "./Display/SPI/SSD_13xx_SPI_Teensy_3x.h"
#include "./Display/SSD_13xx.h"
#include "./Display/SSD_1331.h"
#include <SPI.h>
#include "display.h"

// OLED pins:
const uint8_t   OLED_pin_scl_sck        = 13;
const uint8_t   OLED_pin_sda_mosi       = 11;
const uint8_t   OLED_pin_cs_ss          = 9;
const uint8_t   OLED_pin_res_rst        = 22;
const uint8_t   OLED_pin_dc_rs          = 23;

// SSD1331 color definitions
const uint16_t  OLED_Color_Black        = 0x0000;
const uint16_t  OLED_Color_Blue         = 0x001F;
const uint16_t  OLED_Color_Red          = 0xF800;
const uint16_t  OLED_Color_Green        = 0x07E0;
const uint16_t  OLED_Color_Cyan         = 0x07FF;
const uint16_t  OLED_Color_Magenta      = 0xF81F;
const uint16_t  OLED_Color_Yellow       = 0xFFE0;
const uint16_t  OLED_Color_White        = 0xFFFF;

// The display.
static SSD_133x* oled;

/**
 * Check an SSD_13XX display for error.
 */
// static void checkError(SSD_13XX* display) {
//     uint8_t errorCode = display->getErrorCode();
//     if (errorCode != 0) {
// 		Serial.print("SSD_13XX Init error! ");
// 		if (bitRead(errorCode, 0)) {
//             Serial.print("MOSI or SCLK pin mismach!\n");
//         }
// 		if (bitRead(errorCode, 1)) {
//             Serial.print("CS or DC pin mismach!\n");
//         }
// 	}
// 	else {
// 		Serial.print("SSD_13XX ready!");
//     }
// }
static void checkError(uint8_t errorCode) {
    if (errorCode != 0) {
		Serial.print("SSD_13XX Init error! ");
		if (bitRead(errorCode, 0)) {
            Serial.print("MOSI or SCLK pin mismach!\n");
        }
		if (bitRead(errorCode, 1)) {
            Serial.print("CS or DC pin mismach!\n");
        }
	}
	else {
		Serial.print("SSD_13XX ready!");
    }
}

/**
 * Setup method.
 */
void displaySetup() {



    uint8_t errCode = 0;

    SSD_13XX_SPI* spi = SSD_13XX_SPI_Teensy_3x::init(
        OLED_pin_cs_ss, 
        OLED_pin_dc_rs, 
        OLED_pin_sda_mosi, 
        OLED_pin_scl_sck,
        false,
        &errCode
    );

    // Create the display object.
    oled =   new SSD_1331(
        spi,
        OLED_pin_res_rst
    );

    // Init and check for error.
   // oled->begin();
    checkError(errCode);

    oled->init();

    // Set rotation, clear screen, and set default text settings.
    oled->setRotation(3);
    oled->fillScreen(0x1234);
    // oled->setTextColor(OLED_Color_White);
    // oled->setTextScale(1);
    // oled->setCursor(0,0);

    oled->drawPixel(5, 5, 0xffff);
}

// void drawDigit(EditableDigit_t digit) {

// }

void displayLoop() {


}

