//*****************************************************************************
//
// Filename     : 'ssd1306.h'
// Title        : SSD1306 OLED Display Controller Driver
// Author       : M.Samolutchenko
// Date         : 03/01/2022
//
//*****************************************************************************

#include "ssd1306.h"

// ============================================================================
///
///                    		Global variables
///
// ============================================================================

SSD1306_t 	SSD1306;
uint8_t 	SSD1306_Buffer[SSD1306_BUFFER_SIZE] = {0};

// ============================================================================
///
///                     Command/parameter write function
///
// ============================================================================
/// \param	*hi2c       	Pointer to I2C handler
/// \param	command     	Command/parameter
/// \return			Result (0 - successfully)
// ============================================================================

uint8_t SSD1306_WriteCommand (I2C_HandleTypeDef *hi2c, uint8_t command)
{
	return HAL_I2C_Mem_Write(hi2c, SSD1306_I2C_ADDR, 0x00, 1, &command, 1, 10);
}

// ============================================================================
///
///                     SSD1306 Initialization function
///
// ============================================================================
/// \param	*hi2c     	Pointer to I2C handler
/// \return			Result (0 - successfully)
// ============================================================================

uint8_t SSD1306_Init (I2C_HandleTypeDef *hi2c)
{
	HAL_Delay(100);

	SSD1306_WriteCommand(hi2c, SSD1306_DISPLAYOFF);
	SSD1306_WriteCommand(hi2c, SSD1306_SETMULTIPLEX);
	SSD1306_WriteCommand(hi2c, 0x1F);
	SSD1306_WriteCommand(hi2c, SSD1306_SETDISPLAYOFFSET);
	SSD1306_WriteCommand(hi2c, 0x00);
	SSD1306_WriteCommand(hi2c, SSD1306_SETSTARTLINE);
	SSD1306_WriteCommand(hi2c, SSD1306_SEGREMAP);
	SSD1306_WriteCommand(hi2c, SSD1306_COMSCANDEC);
	SSD1306_WriteCommand(hi2c, SSD1306_SETCOTRAST);
	SSD1306_WriteCommand(hi2c, 0x7F);
	SSD1306_WriteCommand(hi2c, SSD1306_DISPLAYALLON_RESUME);
	SSD1306_WriteCommand(hi2c, SSD1306_NORMALDISPLAY);
	SSD1306_WriteCommand(hi2c, SSD1306_SETDISPLAYCLOCKDIV);
	SSD1306_WriteCommand(hi2c, 0x80);
	SSD1306_WriteCommand(hi2c, SSD1306_CHARGEPUMP);
	SSD1306_WriteCommand(hi2c, 0x14);
	SSD1306_WriteCommand(hi2c, SSD1306_DEACTIVATE_SCROLL);
	SSD1306_WriteCommand(hi2c, SSD1306_MEMORYMODE);
	SSD1306_WriteCommand(hi2c, 0x10);
	SSD1306_WriteCommand(hi2c, SSD1306_SETCOMPINS);
	SSD1306_WriteCommand(hi2c, 0x02);
	SSD1306_WriteCommand(hi2c, SSD1306_SETPRECHARGE);
	SSD1306_WriteCommand(hi2c, 0x22);
	SSD1306_WriteCommand(hi2c, SSD1306_SETVCOMDETECT);
	SSD1306_WriteCommand(hi2c, 0x20);
	SSD1306_WriteCommand(hi2c, SSD1306_SETPAGESTARTADDR);
	SSD1306_WriteCommand(hi2c, 0x00);
	SSD1306_WriteCommand(hi2c, 0x10);
	SSD1306_WriteCommand(hi2c, SSD1306_DISPLAYON);

	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;

	SSD1306.Initialized = 1;

	return 0;
}

// ============================================================================
///
///                         Display color fill function
///
// ============================================================================
/// \param	color    	Fill color
// ============================================================================

void SSD1306_FillScreen (SSD1306_Color color)
{
	uint32_t i;

	for(i = 0; i < sizeof(SSD1306_Buffer); i++)
	{
		SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
	}
}

// ============================================================================
///
///                         Display update function
///
// ============================================================================
/// \param	*hi2c     	Pointer to I2C handler
/// \return			Result (0 - successfully)
// ============================================================================

uint8_t SSD1306_UpdateScreen (I2C_HandleTypeDef *hi2c)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		SSD1306_WriteCommand(hi2c, 0xB0 + i);
		SSD1306_WriteCommand(hi2c, 0x00);
		SSD1306_WriteCommand(hi2c, 0x10);

		HAL_I2C_Mem_Write(hi2c, SSD1306_I2C_ADDR, 0x40, 1, &SSD1306_Buffer[SSD1306_WIDTH * i], SSD1306_WIDTH, 100);
	}
}

// ============================================================================
///
///                        Pixel drawing function
///
// ============================================================================
/// \param	x    	Pixel X coordinate
/// \param	y     	Pixel Y coordinate
/// \param  	color	Pixel color
// ============================================================================

void SSD1306_DrawPixel (uint8_t x, uint8_t y, SSD1306_Color color)
{
	if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return;
	}
<<<<<<< HEAD

	if (color == White)
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
	}
	else
	{
		SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
	}
=======
    if (color == White)
    {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    }
    else
    {
       	SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
>>>>>>> 962235675dcf38e99c1f9cb1bfb3f6c5e771ec2e
}

// ============================================================================
///
///                           Cursor setting function
///
// ============================================================================
/// \param	x    	Cursor X coordinate
/// \param	y     	Cursor Y coordinate
// ============================================================================

void SSD1306_SetCursor (uint8_t x, uint8_t y)
{
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

// ============================================================================
///
///                           Char write function
///
// ============================================================================
/// \param	ch    	Char
/// \param	Font    Font type
/// \param  	color	Color
/// \return 		Written char
// ============================================================================

char SSD1306_WriteChar (char ch, FontDef font, SSD1306_Color color)
{
	uint32_t i, b, j;

	if (SSD1306_WIDTH <= (SSD1306.CurrentX + font.FontWidth) || SSD1306_HEIGHT <= (SSD1306.CurrentY + font.FontHeight))
	{
		return 0;
	}

	for (i = 0; i < font.FontHeight; i++)
	{
		b = font.data[(ch - 32) * font.FontHeight + i];
		for (j = 0; j < font.FontWidth; j++)
		{
			if ((b << j) & 0x8000)
			{
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_Color) color);
			}
			else
			{
				SSD1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_Color) !color);
			}
		}
	}

<<<<<<< HEAD
	SSD1306.CurrentX += font.FontWidth;

	return ch;
=======
    SSD1306.CurrentX += font.FontWidth;
    return ch;
>>>>>>> 962235675dcf38e99c1f9cb1bfb3f6c5e771ec2e
}

// ============================================================================
///
///                           String write function
///
// ============================================================================
/// \param	*str    Pointer to string
/// \param	Font    Font type
/// \param  	color	Color
/// \return 		Pointer to written string
// ============================================================================

char SSD1306_WriteString (char *str, FontDef font, SSD1306_Color color)
{
	while (*str)
	{
		if (SSD1306_WriteChar(*str, font, color) != *str)
		{
			return *str;
		}
		str++;
	}
	return *str;
}

// ============================================================================
///
///                           	Draw bitmap function
///
// ============================================================================
/// \param	x			Initial X coordinate
/// \param	y			Initial Y coordiante
///	\param  bitmap[]	Picture bitmap
/// \param	width		Width of picture
///	\param	height		Height of picture
/// \param	color		Picture color
// ============================================================================

void SSD1306_DrawBitmap (uint8_t x, uint8_t y, const uint8_t bitmap[], uint8_t width, uint8_t height, SSD1306_Color color)
{
	uint8_t byteWidth = (width + 7) / 8;
	uint8_t byte = 0;

	for (uint8_t j = 0; j < height; j++, y++)
	{
		for (uint8_t i = 0; i < width; i++)
		{
			if (i & 7)
			{
				byte <<= 1;
			}
			else
			{
				byte = bitmap[j * byteWidth + i / 8];
			}
			if (byte & 0x80)
			{
				SSD1306_DrawPixel(x + i, y, color);
			}
	    }
	}
}
