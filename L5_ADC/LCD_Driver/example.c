#include "ST7789_Driver.h"
#include "front.h"
#include "example.h"
//#include <math.h>

//extern uint16_t LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
//extern uint16_t LCD_WIDTH = ST7789_SCREEN_WIDTH;

/**
 * @brief 在 LCD 屏幕上显示一个字符
 * 
 * @param x 字符起始横坐标
 * @param y 字符起始纵坐标
 * @param character 要显示的字符
 * @param fontColor 字符颜色
 */
void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor,uint16_t bc)
{
    uint8_t pixelData;
    uint16_t startX = x;
    
    // 将输入的字符转化为对应字库中的索引
    character = character - ' ';
    
    // 设置ST7789 LCD屏幕上要显示的区域
//    ST7789_Set_Address(x, y, x+8-1, y+16-1);
	ILI9341_Set_Address(x, y, x+8-1, y+16-1);
    
    // 遍历16x8的像素矩阵
    for(uint16_t row = 0; row < 16; row++)
    {
        // 获取当前行的像素数据
        pixelData = ascii_1608[character][row];
        
        // 遍历当前行中的每个像素
        for(uint8_t column = 0; column < 8; column++)
        {
            // 如果当前像素位为1，则在该位置绘制一个点
            if(pixelData & (0x01<<column))
//                ST7789_Draw_Pixel(x, y, fontColor);
				ILI9341_Draw_Pixel(x, y, fontColor);
            else  // 如果像素位为0，则在该位置绘制背景颜色
//                ST7789_Draw_Pixel(x, y, bc);
				ILI9341_Draw_Pixel(x, y, bc);
            x++;
            // 如果该行中的8个像素全部绘制完毕，则将绘制位置重置为该行起始位置，并开始下一行的绘制
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
 * @brief 在LCD屏幕上显示一个字符串
 *
 * @param x 字符串的起始x坐标
 * @param y 字符串的起始y坐标
 * @param string 要显示的字符串
 * @param fontColor 字符的字体颜色
 */
void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor,uint16_t bc)
{
    // 从字符串的第一个字符开始，循环遍历每个字符
    while (*string != '\0')
    {
        // 在LCD屏幕上显示当前字符
        LCD_Display_Char(x, y, *string, fontColor, bc);
        // 增加x坐标的值，使得下一个字符可以紧接着当前字符绘制
        x += 8;
        
        // 将指针移动到下一个字符的位置
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

