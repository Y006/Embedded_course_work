#include "ST7789_Driver.h"
#include "front.h"
#include "example.h"
//#include <math.h>

//extern uint16_t LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
//extern uint16_t LCD_WIDTH = ST7789_SCREEN_WIDTH;

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
//    ST7789_Set_Address(x, y, x+8-1, y+16-1);
	ILI9341_Set_Address(x, y, x+8-1, y+16-1);
    
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
//                ST7789_Draw_Pixel(x, y, fontColor);
				ILI9341_Draw_Pixel(x, y, fontColor);
            else  // �������λΪ0�����ڸ�λ�û��Ʊ�����ɫ
//                ST7789_Draw_Pixel(x, y, bc);
				ILI9341_Draw_Pixel(x, y, bc);
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

//void ST7789_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour)
//{
//	int x = Radius-1;
//    int y = 0;
//    int dx = 1;
//    int dy = 1;
//    int err = dx - (Radius << 1);

//    while (x >= y)
//    {
//        ST7789_Draw_Pixel(X + x, Y + y, Colour);
//        ST7789_Draw_Pixel(X + y, Y + x, Colour);
//        ST7789_Draw_Pixel(X - y, Y + x, Colour);
//        ST7789_Draw_Pixel(X - x, Y + y, Colour);
//        ST7789_Draw_Pixel(X - x, Y - y, Colour);
//        ST7789_Draw_Pixel(X - y, Y - x, Colour);
//        ST7789_Draw_Pixel(X + y, Y - x, Colour);
//        ST7789_Draw_Pixel(X + x, Y - y, Colour);

//        if (err <= 0)
//        {
//            y++;
//            err += dy;
//            dy += 2;
//        }
//        if (err > 0)
//        {
//            x--;
//            dx += 2;
//            err += (-Radius << 1) + dx;
//        }
//    }
//}

//void draw_square(int x, int y, int square_size, uint16_t color) 
//{
//    for (int i = 0; i < square_size; i++) 
//	{
//		for (int j = 0; j < square_size; j++) 
//		{
//			if (i == 0 || i == square_size - 1 || j == 0 || j == square_size - 1) 
//			{
//				ST7789_Draw_Pixel(x + i, y + j, color);
//			}
//		}
//	}
//}



//void ST7789_Draw_Line(int x0, int y0, int x1, int y1, uint16_t color) {
//    int dx = abs(x1 - x0);
//    int dy = abs(y1 - y0);
//    int sx = (x0 < x1) ? 1 : -1;
//    int sy = (y0 < y1) ? 1 : -1;
//    int err = dx - dy;

//    while (1) {
//        ST7789_Draw_Pixel(x0, y0, color);

//        if (x0 == x1 && y0 == y1) break;

//        int e2 = 2 * err;

//        if (e2 > -dy) {
//            err -= dy;
//            x0 += sx;
//        }

//        if (e2 < dx) {
//            err += dx;
//            y0 += sy;
//        }
//    }
//}

//void ST7789_Draw_Hollow_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color) {
//    ST7789_Draw_Line(x1, y1, x2, y2, color);
//    ST7789_Draw_Line(x2, y2, x3, y3, color);
//    ST7789_Draw_Line(x3, y3, x1, y1, color);
//}

