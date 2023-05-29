#include "ST7789_Driver.h"

#ifdef USING_ST7789
volatile uint16_t LCD_HEIGHT = ST7789_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH = ST7789_SCREEN_WIDTH;

//#ifdef STM_CONFIG
/**
 * @brief ��ʼ��STM32 HAL���Ӳ��SPI
 */
void STM_HAL_SPI_Init()
{
	MX_SPI1_Init();						// Ӳ�� SPI ��ʼ��
	MX_GPIO_Init();						// IO ��ʼ��
}
//#endif

/**
 * @brief ST7789 дָ���
 * 
 * @param Command ָ��
 */
void ST7789_Write_Command(uint8_t Command)
{
	ST7789_DC_LOW();                   // DC ���ͣ�����ָ��
    ST7789_CS_LOW();                   // Ƭѡ
    ST7789_SPI_Transmit(Command);      // Ӳ�� SPI ����
	ST7789_CS_HIGH();
}

/**
 * @brief ST7789 д���ݺ���
 * 
 * @param Data ����
 */
void ST7789_Write_Data(uint8_t Data)
{
	ST7789_DC_HIGH();                  // DC ���ߣ���������
    ST7789_CS_LOW();                   // Ƭѡ
    ST7789_SPI_Transmit(Data);         // Ӳ�� SPI ����
	ST7789_CS_HIGH();
}

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
void ST7789_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	// �����е�ַ��Χ
	ST7789_Write_Command(ST7789_CASET);
	ST7789_Write_Data(X1 >> 8);		// д��߰�λ
	ST7789_Write_Data(X1);			// д��Ͱ�λ
	ST7789_Write_Data(X2 >> 8);		// д��߰�λ
	ST7789_Write_Data(X2);			// д��Ͱ�λ

	Y1 = Y1 + 20;
	// ����ҳ��ַ��Χ
	ST7789_Write_Command(ST7789_RASET);
	ST7789_Write_Data(Y1 >> 8);		// д��߰�λ
	ST7789_Write_Data(Y1);			// д��Ͱ�λ
	ST7789_Write_Data(Y2 >> 8);		// д��߰�λ
	ST7789_Write_Data(Y2);			// д��Ͱ�λ
	
	// ׼�����ڴ���д����Ϣ
	ST7789_Write_Command(ST7789_RAMWR);
}

/**
 * @brief ���������ĻΪָ����ɫ
 * 
 * @param Colour ���ص���ɫ��RGB565 ��ʽ��
 */
void ST7789_Fill_Screen(uint16_t Colour)
{
	ST7789_FillRectangle(0,0,240,280,Colour);
}

/**
 * @brief ��ָ�����꣨X��Y��������һ�����ص�
 * 
 * @param X     ָ�����ص�� X ����
 * @param Y     ָ�����ص�� Y ����
 * @param Color ���ص����ɫ��ʹ�� RGB565 ��ʽ
 */
void ST7789_Draw_Pixel(uint16_t X, uint16_t Y, uint16_t Color)
{
    // �ж������Ƿ񳬳���Ļ�߽�
    if ((X >= LCD_WIDTH) || (Y >= LCD_HEIGHT))
        return; // ������Χ

    // ����Ҫ���Ƶ����ص������
    ST7789_Set_Address(X, Y, X + 1, Y + 1);

    // �������ص���ɫ����
    uint8_t colorData[2] = {Color >> 8, Color & 0xFF}; // RGB565 ��ʽ����λ��ǰ����λ�ں�
    ST7789_Write_Data(colorData[0]);	// ���͸� 8 λ������
    ST7789_Write_Data(colorData[1]);	// ���͵� 8 λ������
}

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
			break; // ��ʾ��������Ч���˳�����
	}
}

/**
 * @brief ��ʼ�� ST7789 оƬ
 */
void ST7789_Init()
{
	ST7789_SPI_Init();			                    	  		// ��ʼ�� MCU ��������

	ST7789_RST_HIGH();  
	
	ST7789_Write_Command(ST7789_SWRESET);						// �����λ ST7789
	ST7789_Delay(1000);


	ST7789_Write_Command(ST7789_SLPOUT);						// �ر�����ģʽ
	ST7789_Delay(120);
	
	ST7789_Write_Command(ST7789_MADCTL);						// ������ʾ����
	
	if(USE_HORIZONTAL == 0)
		ST7789_Write_Data(0x00);
	else if(USE_HORIZONTAL == 1)
		ST7789_Write_Data(0xC0);
	else if(USE_HORIZONTAL == 2)
		ST7789_Write_Data(0x70);
	else 
		ST7789_Write_Data(0xA0);
	
	ST7789_Write_Command(ST7789_COLMOD);						// ������ɫ��Ϣ
	ST7789_Write_Data(COLOR_MODE_16BIT);						// RGB565
	
	ST7789_Write_Command(ST7789_INVON);

	ST7789_Write_Command(ST7789_DISPON);						// ������ʾ
}

void ST7789_FillRectangle(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t colour)
{
    uint16_t height, width;
    width = ex - sx + 1;            //�õ����Ŀ��
    height = ey - sy + 1;           //�߶�

    ST7789_Set_Address(sx, sy, ex, ey + 20);

    // �����Ҫ�����Ը�����ʾ�������ݸ�ʽҪ������ֽ�˳��
    // ʹ��SWAP_BYTES�꽻���ֽ�˳��
    colour = SWAP_BYTES(colour);

    uint32_t size = width * height;

    // ʹ��һ���ϴ�Ļ��������洢��ͬ����ɫֵ
    uint16_t buf[256]; // �������MCU RAM������������������С
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
            // �������һЩ��ʱ������������ִ��
        }

        remaining_pixels -= pixels_to_send;
    }
}

#endif
