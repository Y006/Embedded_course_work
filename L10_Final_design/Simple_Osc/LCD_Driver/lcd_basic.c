//#include "lcd_basic.h"
//#include "lcd_font.h"

///**
// * @brief 在 LCD 屏幕上显示一个字符
// * 
// * @param x 字符起始横坐标
// * @param y 字符起始纵坐标
// * @param character 要显示的字符
// * @param fontColor 字符颜色
// */
////void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor)
////{
////    uint8_t pixelData;
////    uint16_t startX = x;
////    
////    // 将输入的字符转化为对应字库中的索引
////    character = character - ' ';
////    
////    // 设置ILI9341 LCD屏幕上要显示的区域
////    ILI9341_Set_Address(x, y, x+8-1, y+16-1);
////    
////    // 遍历16x8的像素矩阵
////    for(uint16_t row = 0; row < 16; row++)
////    {
////        // 获取当前行的像素数据
////        pixelData = ascii_1608[character][row];
////        
////        // 遍历当前行中的每个像素
////        for(uint8_t column = 0; column < 8; column++)
////        {
////            // 如果当前像素位为1，则在该位置绘制一个点
////            if(pixelData & (0x01<<column))
////                ILI9341_Draw_Pixel(x, y, fontColor);
////            x++;
////            // 如果该行中的8个像素全部绘制完毕，则将绘制位置重置为该行起始位置，并开始下一行的绘制
////            if((x - startX) == 8)
////            {
////                x = startX;
////                y++;
////                break;
////            }
////        }
////    }
////}

//void LCD_Display_Char(uint16_t x, uint16_t y, uint8_t character, uint16_t fontColor)
//{
//    uint8_t pixelData;
//    uint16_t startX = x;
//    
//    // 将输入的字符转化为对应字库中的索引
//    character = character - ' ';
//    
//    // 设置ILI9341 LCD屏幕上要显示的区域
//    ST7789_Set_Address(x, y, x+8-1, y+16-1);
//    
//    // 遍历16x8的像素矩阵
//    for(uint16_t row = 0; row < 16; row++)
//    {
//        // 获取当前行的像素数据
//        pixelData = ascii_1608[character][row];
//        
//        // 遍历当前行中的每个像素
//        for(uint8_t column = 0; column < 8; column++)
//        {
//            // 如果当前像素位为1，则在该位置绘制一个点
//            if(pixelData & (0x01<<column))
//                ST7789_Draw_Pixel(x, y, fontColor);
//            else  // 如果像素位为0，则在该位置绘制背景颜色
//                ST7789_Draw_Pixel(x, y, WHITE);
//            x++;
//            // 如果该行中的8个像素全部绘制完毕，则将绘制位置重置为该行起始位置，并开始下一行的绘制
//            if((x - startX) == 8)
//            {
//                x = startX;
//                y++;
//                break;
//            }
//        }
//    }
//}

//	 	  
///**
// * @brief 在LCD屏幕上显示一个字符串
// *
// * @param x 字符串的起始x坐标
// * @param y 字符串的起始y坐标
// * @param string 要显示的字符串
// * @param fontColor 字符的字体颜色
// */
//void LCD_Display_String(uint16_t x, uint16_t y, char* string, uint16_t fontColor)
//{
//    // 从字符串的第一个字符开始，循环遍历每个字符
//    while (*string != '\0')
//    {
//        // 在LCD屏幕上显示当前字符
//        LCD_Display_Char(x, y, *string, fontColor);
//        // 增加x坐标的值，使得下一个字符可以紧接着当前字符绘制
//        x += 8;
//        
//        // 将指针移动到下一个字符的位置
//        string++;
//    }
//}





/////* ============================== 实验课使用 =================================================*/




////void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
////{
////	// SENDS COLOUR
////	uint32_t Buffer_Size = 0;
////	if ((Size * 2) < BURST_MAX_SIZE)
////	{
////		Buffer_Size = Size;
////	}
////	else
////	{
////		Buffer_Size = BURST_MAX_SIZE;
////	}

////	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
////	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);

////	unsigned char chifted = Colour >> 8;
////	;
////	unsigned char burst_buffer[Buffer_Size];
////	for (uint32_t j = 0; j < Buffer_Size; j += 2)
////	{
////		burst_buffer[j] = chifted;
////		burst_buffer[j + 1] = Colour;
////	}

////	uint32_t Sending_Size = Size * 2;
////	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
////	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

////	if (Sending_in_Block != 0)
////	{
////		for (uint32_t j = 0; j < (Sending_in_Block); j++)
////		{
////			HAL_SPI_Transmit(&hspi1, (unsigned char *)burst_buffer, Buffer_Size, 10);
////		}
////	}

////	// REMAINDER!
////	HAL_SPI_Transmit(&hspi1, (unsigned char *)burst_buffer, Remainder_from_block, 10);

////	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
////}
////void Fill_Screen(uint16_t Colour)
////{
////	ILI9341_Set_Address(0, 0, 320, 240);
////	ILI9341_Draw_Colour_Burst(Colour, 320 * 240);
////}

////void ILI9341_Draw_Hollow_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour)
////{
////  int x = Radius - 1;
////  int y = 0;
////  int dx = 1;
////  int dy = 1;
////  int err = dx - (Radius << 1);

////  while (x >= y)
////  {
////    ILI9341_Draw_Pixel(X + x, Y + y, Colour);
////    ILI9341_Draw_Pixel(X + y, Y + x, Colour);
////    ILI9341_Draw_Pixel(X - y, Y + x, Colour);
////    ILI9341_Draw_Pixel(X - x, Y + y, Colour);
////    ILI9341_Draw_Pixel(X - x, Y - y, Colour);
////    ILI9341_Draw_Pixel(X - y, Y - x, Colour);
////    ILI9341_Draw_Pixel(X + y, Y - x, Colour);
////    ILI9341_Draw_Pixel(X + x, Y - y, Colour);

////    if (err <= 0)
////    {
////      y++;
////      err += dy;
////      dy += 2;
////    }
////    if (err > 0)
////    {
////      x--;
////      dx += 2;
////      err += (-Radius << 1) + dx;
////    }
////  }
////}
////void ILI9341_Draw_Filled_Circle(uint16_t X, uint16_t Y, uint16_t Radius, uint16_t Colour)
////{

////  int x = Radius;
////  int y = 0;
////  int xChange = 1 - (Radius << 1);
////  int yChange = 0;
////  int radiusError = 0;

////  while (x >= y)
////  {
////    for (int i = X - x; i <= X + x; i++)
////    {
////      ILI9341_Draw_Pixel(i, Y + y, Colour);
////      ILI9341_Draw_Pixel(i, Y - y, Colour);
////    }
////    for (int i = X - y; i <= X + y; i++)
////    {
////      ILI9341_Draw_Pixel(i, Y + x, Colour);
////      ILI9341_Draw_Pixel(i, Y - x, Colour);
////    }

////    y++;
////    radiusError += yChange;
////    yChange += 2;
////    if (((radiusError << 1) + xChange) > 0)
////    {
////      x--;
////      radiusError += xChange;
////      xChange += 2;
////    }
////  }
////}

////void led_init()
////{
////	ILI9341_Draw_Hollow_Circle(120,50,20,RED);
////	ILI9341_Draw_Hollow_Circle(120,100,20,RED);
////	ILI9341_Draw_Hollow_Circle(120,150,20,RED);
////	ILI9341_Draw_Hollow_Circle(120,200,20,RED);
////	ILI9341_Draw_Hollow_Circle(120,250,20,RED);
////}

////void choose_led(uint8_t num)
////{
////	switch(num)
////	{
////		case 1: 
////			ILI9341_Draw_Filled_Circle(120,50,20,RED);
////			ILI9341_Draw_Filled_Circle(120,100,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,150,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,200,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,250,19,WHITE);
////			break;
////		case 2:
////			ILI9341_Draw_Filled_Circle(120,50,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,100,20,RED);
////			ILI9341_Draw_Filled_Circle(120,150,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,200,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,250,19,WHITE);
////			break;
////		case 3:
////			ILI9341_Draw_Filled_Circle(120,50,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,100,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,150,20,RED);
////			ILI9341_Draw_Filled_Circle(120,200,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,250,19,WHITE);
////			break;
////		case 4:
////			ILI9341_Draw_Filled_Circle(120,50,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,100,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,150,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,200,20,RED);
////			ILI9341_Draw_Filled_Circle(120,250,19,WHITE);
////			break;
////		case 5:
////			ILI9341_Draw_Filled_Circle(120,50,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,100,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,150,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,200,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,250,20,RED);
////			break;
////		default: 
////			ILI9341_Draw_Filled_Circle(120,50,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,100,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,150,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,200,19,WHITE);
////			ILI9341_Draw_Filled_Circle(120,250,19,WHITE);
////			break;
////	}
////}
/////* ============================== 实验课使用 =================================================*/

