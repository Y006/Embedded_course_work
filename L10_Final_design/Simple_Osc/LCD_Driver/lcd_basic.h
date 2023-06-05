#ifndef LCD_BASIC_H
#define LCD_BASIC_H

#include "ILI9341_Driver.h"
#include "ST7789_Driver.h"

/**
 * @brief 在 LCD 屏幕上显示一个字符
 * 
 * @param x 字符起始横坐标
 * @param y 字符起始纵坐标
 * @param character 要显示的字符
 * @param fontColor 字符颜色
 */
void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor);
/**
 * @brief 在LCD屏幕上显示一个字符串
 *
 * @param x 字符串的起始x坐标
 * @param y 字符串的起始y坐标
 * @param string 要显示的字符串
 * @param fontColor 字符的字体颜色
 */
void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor);


/* ============================== 实验课使用 =================================================*/
//#define BURST_MAX_SIZE 500

//void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
//void Fill_Screen(uint16_t Colour);
//void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
//void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
//void led_init();
//void choose_led(uint8_t num);
/* ============================== 实验课使用 =================================================*/

#endif
