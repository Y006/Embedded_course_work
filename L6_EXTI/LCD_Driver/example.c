#include "ST7789_Driver.h"
#include "front.h"
#include "example.h"
#include <math.h>

/**
 * @brief �� LCD ��Ļ����ʾһ���ַ�
 * 
 * @param x �ַ���ʼ������
 * @param y �ַ���ʼ������
 * @param character Ҫ��ʾ���ַ�
 * @param fontColor �ַ���ɫ
 */
void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor,uint16_t bc)
{
    uint8_t pixelData;
    uint16_t startX = x;
    
    // ��������ַ�ת��Ϊ��Ӧ�ֿ��е�����
    character = character - ' ';
    
    // ����ST7789 LCD��Ļ��Ҫ��ʾ������
    ST7789_Set_Address(x, y, x+8-1, y+16-1);
    
    // ����16x8�����ؾ���
    for(uint16_t row = 0; row < 16; row++)
    {
        // ��ȡ��ǰ�е���������
        pixelData = ascii_1608[character][row];
        
        // ������ǰ���е�ÿ������
        for(uint8_t column = 0; column < 8; column++)
        {
            // �����ǰ����λΪ1�����ڸ�λ�û���һ����
            if(pixelData & (0x01<<column))
                ST7789_Draw_Pixel(x, y, fontColor);
            else  // �������λΪ0�����ڸ�λ�û��Ʊ�����ɫ
                ST7789_Draw_Pixel(x, y, bc);
            x++;
            // ��������е�8������ȫ��������ϣ��򽫻���λ������Ϊ������ʼλ�ã�����ʼ��һ�еĻ���
            if((x - startX) == 8)
            {
                x = startX;
                y++;
                break;
            }
        }
    }
}
	 	  
/**
 * @brief ��LCD��Ļ����ʾһ���ַ���
 *
 * @param x �ַ�������ʼx����
 * @param y �ַ�������ʼy����
 * @param string Ҫ��ʾ���ַ���
 * @param fontColor �ַ���������ɫ
 */
void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor,uint16_t bc)
{
    // ���ַ����ĵ�һ���ַ���ʼ��ѭ������ÿ���ַ�
    while (*string != '\0')
    {
        // ��LCD��Ļ����ʾ��ǰ�ַ�
        LCD_Display_Char(x, y, *string, fontColor, bc);
        // ����x�����ֵ��ʹ����һ���ַ����Խ����ŵ�ǰ�ַ�����
        x += 8;
        
        // ��ָ���ƶ�����һ���ַ���λ��
        string++;
    }
}