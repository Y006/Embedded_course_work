#ifndef LCD_BASIC_H
#define LCD_BASIC_H

#include "ST7789_Driver.h"

void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor, uint16_t bc);

void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor, uint16_t bc);
void ST7789_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
void draw_square(int x, int y, int square_size, uint16_t color);
void ST7789_Draw_Hollow_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color);
#endif