#ifndef ST7789_DRIVER_H
#define ST7789_DRIVER_H

//#define USING_ST7789

#ifdef USING_ST7789
/**
 * ============================== 开始 选择配置方式 ==================================
 *
 * 如果使用的是基于stm32cubeMX的HAL库并使用了硬件SPI，那么推荐选择STM_CONFIG；
 * 如果使用其他的芯片和配置方式，请选择USER_DEFINED自己进行配置
 */
 
// #define USER_DEFINED
#define STM_CONFIG

#ifdef USER_DEFINED
/**
 * 用户自己的配置
 */
#endif

#ifdef STM_CONFIG
/**
 * 基于stm32cubeMX的HAL库并使用了硬件SPI的配置
 */

#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "dma.h"

#define ST7789_CS_LOW()    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define ST7789_CS_HIGH()   HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define ST7789_DC_LOW()    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)
#define ST7789_DC_HIGH()   HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)
#define ST7789_RST_HIGH()  HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET)
#define ST7789_RST_LOW()   HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET)

//#define ST7789_SPI_Transmit(Data)                \
//    do {                                          \
//        HAL_SPI_Transmit_DMA(&hspi1, &(Data), 1);  \
//    } while(0)

//#define ST7789_SPI_Transmit(Data)                \
//    do {                                          \
//        HAL_SPI_Transmit_IT(&hspi1, &(Data), 1);  \
//    } while(0)

#define ST7789_SPI_Transmit(Data)                \
    do {                                          \
        HAL_SPI_Transmit(&hspi1, &(Data), 1,1);  \
    } while(0)
	
//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCallback ( SPI_HandleTypeDef *hspi);
	
//void LCD_Writ_Bus(uint8_t dat);

//#define ST7789_SPI_Transmit(Data)                \
//    do {                                          \
//        LCD_Writ_Bus(Data);  \
//    } while(0)

#define ST7789_Delay(ms)           \
    do {                            \
        HAL_Delay(ms);              \
    } while(0)

void STM_HAL_SPI_Init(void);
	
#define ST7789_SPI_Init()          \
    do {                            \
        STM_HAL_SPI_Init();         \
    } while(0)

#endif
/* ============================== 结束 选择配置方式 ================================== */

/* ============================== 常见的RGB565颜色值 开始 ============================== */
#define BLACK 		0x0000
#define PURPLE 		0x780F
#define BLUE 		0x001F
#define GREEN 		0x07E0
#define CYAN 		0x07FF
#define RED 		0xF800
#define YELLOW 		0xFFE0
#define WHITE 		0xFFFF
#define ORANGE 		0xFD20
#define PINK 		0xF81F
/* ============================== 常见的RGB565颜色值 结束 ============================== */

/* ============================== 芯片宏定义 开始 ================================== */

// 显示尺寸
#define USE_HORIZONTAL 0
#if USE_HORIZONTAL == 0||USE_HORIZONTAL == 1
	#define ST7789_SCREEN_HEIGHT 	280
	#define ST7789_SCREEN_WIDTH 	240
#else
	#define ST7789_SCREEN_HEIGHT 	240
	#define ST7789_SCREEN_WIDTH 	280
#endif

// 显示方向
#define SCREEN_VERTICAL_1 		0	// 引脚在上
#define SCREEN_HORIZONTAL_1 	1	// 引脚在左
#define SCREEN_VERTICAL_2 		2	// 引脚在下
#define SCREEN_HORIZONTAL_2 	3	// 引脚在右

/* ST7789 Command List （指令列表）*/

#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN    0x10
#define ST7789_SLPOUT   0x11
#define ST7789_PTLON    0x12
#define ST7789_NORON    0x13

#define ST7789_INVOFF   0x20
#define ST7789_INVON    0x21
#define ST7789_DISPOFF  0x28
#define ST7789_DISPON   0x29
#define ST7789_CASET    0x2A
#define ST7789_RASET    0x2B
#define ST7789_RAMWR    0x2C
#define ST7789_RAMRD    0x2E

#define ST7789_PTLAR    0x30
#define ST7789_VSCRDEF  0x33
#define ST7789_COLMOD   0x3A
#define ST7789_MADCTL   0x36
#define ST7789_VSCSAD   0x37

#define ST7789_MADCTL_MY    0x80
#define ST7789_MADCTL_MX    0x40
#define ST7789_MADCTL_MV    0x20
#define ST7789_MADCTL_ML    0x10
#define ST7789_MADCTL_BGR   0x08
#define ST7789_MADCTL_MH    0x04
#define ST7789_MADCTL_RGB   0x00

#define ST7789_RDID1    0xDA
#define ST7789_RDID2    0xDB
#define ST7789_RDID3    0xDC
#define ST7789_RDID4    0xDD

#define COLOR_MODE_65K      0x50
#define COLOR_MODE_262K     0x60
#define COLOR_MODE_12BIT    0x03
#define COLOR_MODE_16BIT    0x05
#define COLOR_MODE_18BIT    0x06
#define COLOR_MODE_16M      0x07

/* ============================== 芯片宏定义 结束 ================================== */

/* ============================== 函数声明列表 开始================================== */

/**
 * @brief ST7789 写指令函数
 * 
 * @param Command 指令
 */
void ST7789_Write_Command(uint8_t Command);
	
/**
 * @brief ST7789 写数据函数
 * 
 * @param Data 数据
 */
void ST7789_Write_Data(uint8_t Data);
	
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
void ST7789_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
	
/**
 * @brief 填充整个屏幕
 * @note  将整个屏幕设置为给定的颜色
 * @param Colour 像素点颜色，RGB565 格式，高位在前，低位在后
 * @retval None
 */
void ST7789_Fill_Screen(uint16_t Colour);
	
/**
 * @brief 在指定坐标（X，Y）处绘制一个像素点
 * 
 * @param X     指定像素点的 X 坐标
 * @param Y     指定像素点的 Y 坐标
 * @param Color 像素点的颜色，使用 RGB565 格式
 */
void ST7789_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Color);
	
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
void ST7789_Set_Rotation(uint8_t Rotation);
	
/**
 * @brief 初始化 ST7789 芯片
 */
void ST7789_Init(void);

/* ============================== 函数声明列表 结束================================== */
//void ST7789_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
//void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Colour);
#endif

#endif


