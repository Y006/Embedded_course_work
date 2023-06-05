#ifndef LCD_BASIC_H
#define LCD_BASIC_H

#include "ILI9341_Driver.h"
#include "ST7789_Driver.h"

/**
 * @brief �� LCD ��Ļ����ʾһ���ַ�
 * 
 * @param x �ַ���ʼ������
 * @param y �ַ���ʼ������
 * @param character Ҫ��ʾ���ַ�
 * @param fontColor �ַ���ɫ
 */
void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor);
/**
 * @brief ��LCD��Ļ����ʾһ���ַ���
 *
 * @param x �ַ�������ʼx����
 * @param y �ַ�������ʼy����
 * @param string Ҫ��ʾ���ַ���
 * @param fontColor �ַ���������ɫ
 */
void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor);


/* ============================== ʵ���ʹ�� =================================================*/
//#define BURST_MAX_SIZE 500

//void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);
//void Fill_Screen(uint16_t Colour);
//void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
//void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour);
//void led_init();
//void choose_led(uint8_t num);
/* ============================== ʵ���ʹ�� =================================================*/

#endif
