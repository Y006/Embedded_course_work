#ifndef ST7789_DRIVER_H
#define ST7789_DRIVER_H

//#define USING_ST7789

#ifdef USING_ST7789
/**
 * ============================== ��ʼ ѡ�����÷�ʽ ==================================
 *
 * ���ʹ�õ��ǻ���stm32cubeMX��HAL�Ⲣʹ����Ӳ��SPI����ô�Ƽ�ѡ��STM_CONFIG��
 * ���ʹ��������оƬ�����÷�ʽ����ѡ��USER_DEFINED�Լ���������
 */
 
// #define USER_DEFINED
#define STM_CONFIG

#ifdef USER_DEFINED
/**
 * �û��Լ�������
 */
#endif

#ifdef STM_CONFIG
/**
 * ����stm32cubeMX��HAL�Ⲣʹ����Ӳ��SPI������
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
/* ============================== ���� ѡ�����÷�ʽ ================================== */

/* ============================== ������RGB565��ɫֵ ��ʼ ============================== */
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
/* ============================== ������RGB565��ɫֵ ���� ============================== */

/* ============================== оƬ�궨�� ��ʼ ================================== */

// ��ʾ�ߴ�
#define USE_HORIZONTAL 0
#if USE_HORIZONTAL == 0||USE_HORIZONTAL == 1
	#define ST7789_SCREEN_HEIGHT 	280
	#define ST7789_SCREEN_WIDTH 	240
#else
	#define ST7789_SCREEN_HEIGHT 	240
	#define ST7789_SCREEN_WIDTH 	280
#endif

// ��ʾ����
#define SCREEN_VERTICAL_1 		0	// ��������
#define SCREEN_HORIZONTAL_1 	1	// ��������
#define SCREEN_VERTICAL_2 		2	// ��������
#define SCREEN_HORIZONTAL_2 	3	// ��������

/* ST7789 Command List ��ָ���б�*/

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

/* ============================== оƬ�궨�� ���� ================================== */

/* ============================== ���������б� ��ʼ================================== */

/**
 * @brief ST7789 дָ���
 * 
 * @param Command ָ��
 */
void ST7789_Write_Command(uint8_t Command);
	
/**
 * @brief ST7789 д���ݺ���
 * 
 * @param Data ����
 */
void ST7789_Write_Data(uint8_t Data);
	
/**
 * @brief ָ��ST7789д�����ݵ�λ��
 * 
 * @param X1 ��ʼ�е�ַ
 * @param Y1 ��ʼҳ��ַ
 * @param X2 �����е�ַ
 * @param Y2 ����ҳ��ַ
 * 
 * @note �������غ󼴿���оƬ(x1,y1)��(x2,y2)�ķ�Χ��д����ʾ����
 */
void ST7789_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
	
/**
 * @brief ���������Ļ
 * @note  ��������Ļ����Ϊ��������ɫ
 * @param Colour ���ص���ɫ��RGB565 ��ʽ����λ��ǰ����λ�ں�
 * @retval None
 */
void ST7789_Fill_Screen(uint16_t Colour);
	
/**
 * @brief ��ָ�����꣨X��Y��������һ�����ص�
 * 
 * @param X     ָ�����ص�� X ����
 * @param Y     ָ�����ص�� Y ����
 * @param Color ���ص����ɫ��ʹ�� RGB565 ��ʽ
 */
void ST7789_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Color);
	
/**
 * @brief ���� ST7789 оƬ�� LCD ��ʾ����
 * 
 * @param Rotation ��ʾ���򣬿�ѡֵΪ��
 *                 SCREEN_VERTICAL_1: 	��ֱ��Ļ����
 *                 SCREEN_HORIZONTAL_1: ˮƽ��Ļ����
 *                 SCREEN_VERTICAL_2: 	��ֱ��Ļ����
 *                 SCREEN_HORIZONTAL_2: ˮƽ��Ļ����
 * 
 * @note ���øú����������� ST7789 оƬ����ʾ����ͬʱ����� LCD_WIDTH �� LCD_HEIGHT �궨���ֵ��
 * 
 * @note ���� ST7789 оƬд������ǰ��Ҫ���ú���ʾ���򣬷���д���ͼ�����ֵ��õ����⡣
 */
void ST7789_Set_Rotation(uint8_t Rotation);
	
/**
 * @brief ��ʼ�� ST7789 оƬ
 */
void ST7789_Init(void);

/* ============================== ���������б� ����================================== */
//void ST7789_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
//void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t Colour);
#endif

#endif


