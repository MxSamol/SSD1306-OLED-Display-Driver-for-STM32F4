//*****************************************************************************
//
// Filename     : 'ssd1306.h'
// Title        : SSD1306 OLED Display Controller Driver
// Author       : M.Samolutchenko
// Date         : 03/01/2022
//
//*****************************************************************************
#pragma once

#include "stm32f4xx_hal.h"
#include "fonts.h"

// ============================================================================
///
///                               Definitions
///
// ============================================================================

#define SSD1306_I2C_ADDR				0x78

#define SSD1306_WIDTH					128
#define SSD1306_HEIGHT					32

#define SSD1306_BUFFER_SIZE				(SSD1306_WIDTH * SSD1306_HEIGHT) / 8

#define SSD1306_DISPLAYOFF				0xAE
#define SSD1306_SETMULTIPLEX				0xA8
#define SSD1306_SETDISPLAYOFFSET			0xD3
#define SSD1306_SETSTARTLINE				0x40
#define SSD1306_SEGREMAP				0xA1
#define SSD1306_COMSCANDEC				0xC8
#define SSD1306_SETCOTRAST				0x81
#define SSD1306_DISPLAYALLON_RESUME			0xA4
#define SSD1306_NORMALDISPLAY				0xA6
#define SSD1306_SETDISPLAYCLOCKDIV			0xD5
#define SSD1306_CHARGEPUMP				0x8D
#define SSD1306_DEACTIVATE_SCROLL			0x2E
#define SSD1306_MEMORYMODE				0x20
#define SSD1306_SETCOMPINS				0xDA
#define SSD1306_SETPRECHARGE				0xD9
#define SSD1306_SETVCOMDETECT				0xDB
#define SSD1306_SETPAGESTARTADDR			0x0B
#define SSD1306_DISPLAYON				0xAF

// ============================================================================
///
///                               Data types
///
// ============================================================================

typedef enum {
	Black = 0x00,
	White = 0x01,
} SSD1306_Color;

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t  Inverted;
	uint8_t  Initialized;
} SSD1306_t;

// ============================================================================
///
///                            Function prototypes
///
// ============================================================================

uint8_t SSD1306_WriteCommand (I2C_HandleTypeDef *hi2c, uint8_t command);
uint8_t SSD1306_Init (I2C_HandleTypeDef *hi2c);
void	SSD1306_FillScreen (SSD1306_Color color);
uint8_t SSD1306_UpdateScreen (I2C_HandleTypeDef *hi2c);
void 	SSD1306_DrawPixel (uint8_t x, uint8_t y, SSD1306_Color color);
void	SSD1306_SetCursor (uint8_t x, uint8_t y);
char 	SSD1306_WriteChar (char ch, FontDef font, SSD1306_Color color);
char 	SSD1306_WriteString (char *str, FontDef font, SSD1306_Color color);
void	SSD1306_DrawBitmap (uint8_t x, uint8_t y, const uint8_t bitmap[], uint8_t width, uint8_t height, SSD1306_Color color);


