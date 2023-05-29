#include "ST7789_Driver.h"

#ifdef USING_ST7789
volatile uint16_t LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH = ST7789_SCREEN_WIDTH;

//#ifdef STM_CONFIG
/**
 * @brief 初始化STM32 HAL库的硬件SPI
 */
void STM_HAL_SPI_Init()
{
	MX_SPI1_Init();						// 硬件 SPI 初始化
	MX_GPIO_Init();						// IO 初始化
}
//#endif

/**
 * @brief ST7789 写指令函数
 * 
 * @param Command 指令
 */
void ST7789_Write_Command(uint8_t Command)
{
	ST7789_DC_LOW();                   // DC 拉低，发送指令
    ST7789_CS_LOW();                   // 片选
    ST7789_SPI_Transmit(Command);      // 硬件 SPI 发送
	ST7789_CS_HIGH();
}

/**
 * @brief ST7789 写数据函数
 * 
 * @param Data 数据
 */
void ST7789_Write_Data(uint8_t Data)
{
	ST7789_DC_HIGH();                  // DC 拉高，发送数据
    ST7789_CS_LOW();                   // 片选
    ST7789_SPI_Transmit(Data);         // 硬件 SPI 发送
	ST7789_CS_HIGH();
}

/**
 * @brief 指定ST7789写入数据的位置
 * 
 * @param X1 起始列地址
 * @param Y1 起始页地址
 * @param X2 结束列地址
 * @param Y2 结束页地址
 * 
 * @note 函数返回后即可向芯片(x1,y1)到(x2,y2)的范围内写入显示内容
 */
void ST7789_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	// 设置列地址范围
	ST7789_Write_Command(ST7789_CASET);
	ST7789_Write_Data(X1 >> 8);		// 写入高八位
	ST7789_Write_Data(X1);			// 写入低八位
	ST7789_Write_Data(X2 >> 8);		// 写入高八位
	ST7789_Write_Data(X2);			// 写入低八位

	Y1 = Y1 + 20;
	// 设置页地址范围
	ST7789_Write_Command(ST7789_RASET);
	ST7789_Write_Data(Y1 >> 8);		// 写入高八位
	ST7789_Write_Data(Y1);			// 写入低八位
	ST7789_Write_Data(Y2 >> 8);		// 写入高八位
	ST7789_Write_Data(Y2);			// 写入低八位
	
	// 准备向内存中写入信息
	ST7789_Write_Command(ST7789_RAMWR);
}

/**
 * @brief 填充整个屏幕为指定颜色
 * 
 * @param Colour 像素点颜色：RGB565 格式、
 */
void ST7789_Fill_Screen(uint16_t Colour)
{
	ST7789_FillRectangle(0,0,240,280,Colour);
}

/**
 * @brief 在指定坐标（X，Y）处绘制一个像素点
 * 
 * @param X     指定像素点的 X 坐标
 * @param Y     指定像素点的 Y 坐标
 * @param Color 像素点的颜色，使用 RGB565 格式
 */
void ST7789_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Color)
{
    // 判断坐标是否超出屏幕边界
    if ((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT))
        return; // 超出范围

    // 设置要绘制的像素点的坐标
    ST7789_Set_Address(X, Y, X + 1, Y + 1);

    // 发送像素点颜色数据
    uint8_t colorData[2] = {Color >> 8, Color & 0xFF}; // RGB565 格式，高位在前，低位在后
    ST7789_Write_Data(colorData[0]);	// 发送高 8 位的数据
    ST7789_Write_Data(colorData[1]);	// 发送低 8 位的数据
}

/**
 * @brief 设置 ST7789 芯片的 LCD 显示方向
 * 
 * @param Rotation 显示方向，可选值为：
 *                 SCREEN_VERTICAL_1: 	垂直屏幕向上
 *                 SCREEN_HORIZONTAL_1: 水平屏幕向上
 *                 SCREEN_VERTICAL_2: 	垂直屏幕向下
 *                 SCREEN_HORIZONTAL_2: 水平屏幕向下
 * 
 * @note 调用该函数可以设置 ST7789 芯片的显示方向，同时会更新 LCD_WIDTH 和 LCD_HEIGHT 宏定义的值。
 * 
 * @note 在向 ST7789 芯片写入数据前需要设置好显示方向，否则写入的图像会出现倒置等问题。
 */
void ST7789_Set_Rotation(uint8_t Rotation)
{
	ST7789_Write_Command(ST7789_MADCTL);

	switch (Rotation)
	{
		case SCREEN_VERTICAL_1:
			ST7789_Write_Data(0x40 | 0x08);
			LCD_WIDTH = ST7789_SCREEN_HEIGHT; LCD_HEIGHT = ST7789_SCREEN_WIDTH;
			break;
		case SCREEN_HORIZONTAL_1:
			ST7789_Write_Data(0x20 | 0x08);
			LCD_WIDTH = ST7789_SCREEN_WIDTH; LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
			break;
		case SCREEN_VERTICAL_2:
			ST7789_Write_Data(0x80 | 0x08);
			LCD_WIDTH = ST7789_SCREEN_HEIGHT; LCD_HEIGHT = ST7789_SCREEN_WIDTH;
			break;
		case SCREEN_HORIZONTAL_2:
			ST7789_Write_Data(0x40 | 0x80 | 0x20 | 0x08);
			LCD_WIDTH = ST7789_SCREEN_WIDTH; LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
			break;
		default:
			break; // 显示方向定义无效则退出函数
	}
}

/**
 * @brief 初始化 ST7789 芯片
 */
void ST7789_Init()
{
	ST7789_SPI_Init();			                    	  		// 初始化 MCU 控制引脚

	ST7789_RST_HIGH();  
	
	ST7789_Write_Command(ST7789_SWRESET);						// 软件复位 ST7789
	ST7789_Delay(1000);


	ST7789_Write_Command(ST7789_SLPOUT);						// 关闭休眠模式
	ST7789_Delay(120);
	
	ST7789_Write_Command(ST7789_MADCTL);						// 设置显示方向
	
	if(USE_HORIZONTAL == 0)
		ST7789_Write_Data(0x00);
	else if(USE_HORIZONTAL == 1)
		ST7789_Write_Data(0xC0);
	else if(USE_HORIZONTAL == 2)
		ST7789_Write_Data(0x70);
	else 
		ST7789_Write_Data(0xA0);
	
	ST7789_Write_Command(ST7789_COLMOD);						// 配置颜色信息
	ST7789_Write_Data(COLOR_MODE_16BIT);						// RGB565
	
	ST7789_Write_Command(ST7789_INVON);

	ST7789_Write_Command(ST7789_DISPON);						// 开启显示
}

void ST7789_FillRectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t colour)
{
    uint16_t height, width;
    width = ex - sx + 1;            //得到填充的宽度
    height = ey - sy + 1;           //高度

    ST7789_Set_Address(sx, sy, ex, ey + 20);

    // 如果需要，可以根据显示器的数据格式要求调整字节顺序
    // 使用SWAP_BYTES宏交换字节顺序：
    colour = SWAP_BYTES(colour);

    uint32_t size = width * height;

    // 使用一个较大的缓冲区来存储相同的颜色值
    uint16_t buf[256]; // 根据你的MCU RAM容量来调整缓冲区大小
    for (int i = 0; i < sizeof(buf) / sizeof(buf[0]); i++) {
        buf[i] = colour;
    }

    ST7789_DC_HIGH();
	ST7789_CS_LOW();

    uint32_t remaining_pixels = size;
    while (remaining_pixels > 0) {
        uint32_t pixels_to_send = (remaining_pixels > (sizeof(buf) / sizeof(buf[0]))) ? (sizeof(buf) / sizeof(buf[0])) : remaining_pixels;
        HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)buf, pixels_to_send * 2);

        while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY) {
            // 可以添加一些延时，让其他任务执行
        }

        remaining_pixels -= pixels_to_send;
    }
}

#endif
