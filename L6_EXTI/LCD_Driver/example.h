#ifndef LCD_BASIC_H
#define LCD_BASIC_H

#include "ST7789_Driver.h"

void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor, uint16_t bc);
void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor, uint16_t bc);
#endif