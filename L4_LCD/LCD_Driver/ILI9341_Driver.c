#include "ILI9341_Driver.h"

#ifdef USING_ILI9341

volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH = ILI9341_SCREEN_WIDTH;

// void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//    if (hspi->Instance == SPI1)
//    {
//        ILI9341_CS_HIGH(); // 在传输完成时取消片选
//    }
//}

#ifdef STM_CONFIG
/**
 * @brief 初始化STM32 HAL库的硬件SPI
 */
void STM_HAL_SPI_Init()
{
	MX_SPI1_Init();						// 硬件 SPI 初始化
	MX_GPIO_Init();						// IO 初始化
//	ILI9341_CS_LOW(); 					// 复位 CS 引脚
}
#endif

/**
 * @brief ILI9341 写指令函数
 * 
 * @param Command 指令
 */
void ILI9341_Write_Command(uint8_t Command)
{
	ILI9341_DC_LOW();                   // DC 拉低，发送指令
//    ILI9341_CS_LOW();                   // 片选
    ILI9341_SPI_Transmit(Command);      // 硬件 SPI 发送
}

/**
 * @brief ILI9341 写数据函数
 * 
 * @param Data 数据
 */
void ILI9341_Write_Data(uint8_t Data)
{
	ILI9341_DC_HIGH();                  // DC 拉高，发送数据
//    ILI9341_CS_LOW();                   // 片选
    ILI9341_SPI_Transmit(Data);         // 硬件 SPI 发送
}

/**
 * @brief 指定ILI9341写入数据的位置
 * 
 * @param X1 起始列地址
 * @param Y1 起始页地址
 * @param X2 结束列地址
 * @param Y2 结束页地址
 * 
 * @note 函数返回后即可向芯片(x1,y1)到(x2,y2)的范围内写入显示内容
 */
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	// 设置列地址范围
	ILI9341_Write_Command(CMD_COL_ADDR_SET);
	
	uint8_t x[4] = {X1 >> 8, X1 & 0xFF, X2 >> 8, X2 & 0xFF};
	uint8_t y[4] = {Y1 >> 8, Y1 & 0xFF, Y2 >> 8, Y2 & 0xFF};
	
	ILI9341_DC_HIGH();
	HAL_SPI_Transmit_DMA(&hspi1, x, 4);
	
//	ILI9341_Write_Data(X1 >> 8);		// 写入高八位
//	ILI9341_Write_Data(X1);				// 写入低八位
//	ILI9341_Write_Data(X2 >> 8);		// 写入高八位
//	ILI9341_Write_Data(X2);				// 写入低八位

	// 设置页地址范围
	ILI9341_Write_Command(CMD_PAGE_ADDR_SET);
	
	ILI9341_DC_HIGH();
	HAL_SPI_Transmit_DMA(&hspi1, y, 4);
	
//	ILI9341_Write_Data(Y1 >> 8);		// 写入高八位
//	ILI9341_Write_Data(Y1);				// 写入低八位
//	ILI9341_Write_Data(Y2 >> 8);		// 写入高八位
//	ILI9341_Write_Data(Y2);				// 写入低八位
	
	// 准备向内存中写入信息
	ILI9341_Write_Command(CMD_MEMORRY_WRITE);
}

/**
 * @brief 填充整个屏幕为指定颜色
 * 
 * @param Colour 像素点颜色：RGB565 格式、
 */
void ILI9341_Fill_Screen(uint16_t Colour)
{
    // 填充整个屏幕
    ILI9341_Set_Address(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    // 发送像素点颜色数据
//    uint8_t colorData[200] = {
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
//							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF
//							}; // RGB565 格式，高位在前，低位在后
    uint8_t colorData[] = {
							Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
		Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
		Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
		Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF,
		Colour >> 8, Colour & 0xFF, Colour >> 8, Colour & 0xFF
							}; // RGB565 格式，高位在前，低位在后
	
	ILI9341_DC_HIGH();
    for (uint32_t i = 0; i < 320*240; i++)
    {
        HAL_SPI_Transmit_DMA(&hspi1, colorData, 20);
    }
}

//void ILI9341_Fill_Screen(uint16_t Colour)
//{
//    // 填充整个屏幕
//    ILI9341_Set_Address(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

//	ILI9341_DC_HIGH();
//	for (uint32_t i = 0; i < 10; i++)
//	{
//		uint8_t sendData[32 * 24 * 2]; // 存储像素点颜色数据
//	
//		for (uint32_t i = 0; i < 32 * 24 * 2; i += 2)
//		{
//			sendData[i] = Colour >> 8; // 存储高 8 位的数据
//			sendData[i+1] = Colour & 0xFF; // 存储低 8 位的数据
//		}
//		
//		HAL_SPI_Transmit_DMA(&hspi1, sendData, 32*24*2);
//	}
//}

//uint8_t sendData1[32 * 24]; // 存储像素点颜色数据
//uint8_t sendData2[32 * 24]; // 存储像素点颜色数据
//	
//void ILI9341_Fill_Screen(uint16_t Colour)
//{
//    // 填充整个屏幕
//    ILI9341_Set_Address(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

//    // 将颜色数据存入数组

//	
//    for (uint16_t i = 0; i < (LCD_WIDTH/10) * (LCD_HEIGHT/10); i++)
//    {
//        sendData1[i] = Colour >> 8; // 存储高 8 位的数据
//        sendData2[i] = Colour & 0xFF; // 存储低 8 位的数据
//    }

//    // 使用 DMA 发送数据
////    uint16_t halfSize = (LCD_WIDTH * LCD_HEIGHT) / 2;
//	uint16_t halfSize=32*24;
//	
//	ILI9341_DC_HIGH();
//	for (uint16_t i = 0; i < 10; i++)
//	{
//		HAL_SPI_Transmit_DMA(&hspi1, sendData1, halfSize);
////		HAL_SPI_Transmit_DMA(&hspi1, sendData1+halfSize, halfSize);
//		HAL_SPI_Transmit_DMA(&hspi1, sendData2, halfSize);
////		HAL_SPI_Transmit_DMA(&hspi1, sendData2+halfSize, halfSize);
//	}
//    
//}





//#define 	LCD_RAM_SIZE 		LCD_WIDTH*LCD_HEIGHT*2		//长240 宽240 色深2bit
//#define 	Pixel_NUM 			(LCD_RAM_SIZE/2)

//void LCD_Fill_first_half(uint8_t *data)
//{
//    /* 指定显存操作地址为前半屏*/
//    ILI9341_Set_Address(0, 0, LCD_WIDTH - 1, LCD_HEIGHT/2 - 1);
//    ILI9341_DC_HIGH();/* 指定接下来的数据为数据 */
//    /* 写前半屏*/
//    HAL_SPI_Transmit_DMA(&hspi1, data, LCD_RAM_SIZE/2);
//}

//void LCD_Fill_last_half(uint8_t *data)
//{
//    /* 指定显存操作地址为后半屏*/
//    ILI9341_Set_Address(0, LCD_HEIGHT/2, LCD_WIDTH - 1, LCD_HEIGHT - 1);
//    ILI9341_DC_HIGH();/* 指定接下来的数据为数据 */
//    /*写后半屏*/
//    HAL_SPI_Transmit_DMA(&hspi1, data + LCD_RAM_SIZE/2, LCD_RAM_SIZE/2);
//}
//void ILI9341_Fill_Screen(uint16_t Colour)
//{
//    // 将颜色数据存入数组
//    uint8_t sendData[LCD_WIDTH * LCD_HEIGHT * 2]; // 存储像素点颜色数据

//    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT * 2; i += 2)
//    {
//        sendData[i] = Colour >> 8; // 存储高 8 位的数据
//        sendData[i+1] = Colour & 0xFF; // 存储低 8 位的数据
//    }

//    // 发送前半屏像素点颜色数据
//    LCD_Fill_first_half(sendData);

//    // 发送后半屏像素点颜色数据
//    LCD_Fill_last_half(sendData);
//}






/**
 * @brief 在指定坐标（X，Y）处绘制一个像素点
 * 
 * @param X     指定像素点的 X 坐标
 * @param Y     指定像素点的 Y 坐标
 * @param Color 像素点的颜色，使用 RGB565 格式
 */
void ILI9341_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Color)
{
    // 判断坐标是否超出屏幕边界
    if ((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT))
        return; // 超出范围

    // 设置要绘制的像素点的坐标
    ILI9341_Set_Address(X, Y, X + 1, Y + 1);

    // 发送像素点颜色数据
    uint8_t colorData[2] = {Color >> 8, Color & 0xFF}; // RGB565 格式，高位在前，低位在后
    ILI9341_Write_Data(colorData[0]);	// 发送高 8 位的数据
    ILI9341_Write_Data(colorData[1]);	// 发送低 8 位的数据
}

/**
 * @brief 设置 ILI9341 芯片的 LCD 显示方向
 * 
 * @param Rotation 显示方向，可选值为：
 *                 SCREEN_VERTICAL_1: 	垂直屏幕向上
 *                 SCREEN_HORIZONTAL_1: 水平屏幕向上
 *                 SCREEN_VERTICAL_2: 	垂直屏幕向下
 *                 SCREEN_HORIZONTAL_2: 水平屏幕向下
 * 
 * @note 调用该函数可以设置 ILI9341 芯片的显示方向，同时会更新 LCD_WIDTH 和 LCD_HEIGHT 宏定义的值。
 * 
 * @note 在向 ILI9341 芯片写入数据前需要设置好显示方向，否则写入的图像会出现倒置等问题。
 */
void ILI9341_Set_Rotation(uint8_t Rotation)
{
	ILI9341_Write_Command(CMD_MEMORY_ACCESS_CTRL);

	switch (Rotation)
	{
		case SCREEN_VERTICAL_1:
			ILI9341_Write_Data(0x40 | 0x08);
			LCD_WIDTH = ILI9341_SCREEN_HEIGHT; LCD_HEIGHT = ILI9341_SCREEN_WIDTH;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9341_Write_Data(0x20 | 0x08);
			LCD_WIDTH = ILI9341_SCREEN_WIDTH; LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
			break;
		case SCREEN_VERTICAL_2:
			ILI9341_Write_Data(0x80 | 0x08);
			LCD_WIDTH = ILI9341_SCREEN_HEIGHT; LCD_HEIGHT = ILI9341_SCREEN_WIDTH;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9341_Write_Data(0x40 | 0x80 | 0x20 | 0x08);
			LCD_WIDTH = ILI9341_SCREEN_WIDTH; LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
			break;
		default:
			break; // 显示方向定义无效则退出函数
	}
}

/**
 * @brief 初始化 ILI9341 芯片
 */
void ILI9341_Init()
{
	
	ILI9341_SPI_Init();			                    			// 初始化 MCU 控制引脚
	ILI9341_RST_HIGH();                                         // 硬件复位 ILI9341

	ILI9341_Write_Command(CMD_SOFTWARE_RESET);					// 软件复位 ILI9341
	ILI9341_Delay(1000);

	ILI9341_Write_Command(CMD_COLMOD_PIXEL_FORMAT_SET);			// 配置颜色信息
	ILI9341_Write_Data(0x55);									// RGB565

	ILI9341_Write_Command(CMD_SLEEP_OUT);						// 关闭休眠模式
	ILI9341_Delay(120);

	ILI9341_Write_Command(CMD_DISPLAY_ON);						// 开启显示

	ILI9341_Set_Rotation(SCREEN_VERTICAL_1);					// 设置显示方向
}

void LCD_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Colour)
{
    ILI9341_Set_Address(x, y, w - 1, 20+h - 1);

    // 发送像素点颜色数据
    uint8_t colorData[2] = {Colour >> 8, Colour & 0xFF}; // RGB565 格式，高位在前，低位在后

	ILI9341_DC_HIGH();
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        HAL_SPI_Transmit_DMA(&hspi1, colorData, 2);
    }
//    for (uint32_t i = 0; i < w * h; i++)
//    {
//        ILI9341_Write_Data(colorData[0]); // 发送高 8 位的数据
//        ILI9341_Write_Data(colorData[1]); // 发送低 8 位的数据
//    }
}


#endif


