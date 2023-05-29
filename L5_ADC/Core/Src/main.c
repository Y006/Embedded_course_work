/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ILI9341_Driver.h"
#include "stdio.h"
#include "example.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* ============================== ADC采样变量 =============================== */
#define ADC_SAMPLE_NUM 30
uint32_t ADC_Value[ADC_SAMPLE_NUM];
uint8_t i, page, chage_page;
uint32_t ad1;
char ADC_Value_Str[ADC_SAMPLE_NUM];
char immediate_data[ADC_SAMPLE_NUM];
uint32_t adc_min = 4096;
uint32_t adc_value;
uint32_t adc_max = 0;
char adc_max_string[ADC_SAMPLE_NUM];
char adc_min_string[ADC_SAMPLE_NUM];
/* ============================== ADC采样变量 =============================== */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
ILI9341_Init();
ILI9341_Fill_Screen(BLACK);
HAL_TIM_Base_Start_IT(&htim2); 
HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, ADC_SAMPLE_NUM);
if(page == 0)
{
	LCD_Display_String(10,30,"======= DC Voltmeter =======",WHITE,BLACK);
	LCD_Display_String(60,70,"Voltage:  ",WHITE,BLACK);
	LCD_Display_String(60,110,"ADCnum:   ",WHITE,BLACK);
	LCD_Display_String(10,150,"===========================",WHITE,BLACK);
}

if(page == 1)
{
	LCD_Display_String(10,30,"======= MAX-MIN VALUE =======",WHITE,BLACK);
	LCD_Display_String(60,70,"MAX_Volt:  ",WHITE,BLACK);
	LCD_Display_String(60,110,"MIN_Volt:   ",WHITE,BLACK);
	LCD_Display_String(10,150,"============================",WHITE,BLACK);
}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(page == 0 && chage_page == 1)
	  {
		  ILI9341_Fill_Screen(BLACK);
		  LCD_Display_String(10,30,"======= DC Voltmeter =======",WHITE,BLACK);
		  LCD_Display_String(60,70,"Voltage:  ",WHITE,BLACK);
		  LCD_Display_String(60,110,"ADCnum:   ",WHITE,BLACK);
		  LCD_Display_String(10,150,"===========================",WHITE,BLACK);
	  }

	  if(page == 1 && chage_page == 0)
	  {
		  ILI9341_Fill_Screen(BLACK);
		  adc_min = 4096;
		  adc_value = 0;
		  adc_max = 0;
		  LCD_Display_String(10,30,"======= MAX-MIN VALUE =======",WHITE,BLACK);
		  LCD_Display_String(60,70,"MAX_Volt:  ",WHITE,BLACK);
		  LCD_Display_String(60,110,"MIN_Volt:   ",WHITE,BLACK);
		  LCD_Display_String(10,150,"============================",WHITE,BLACK);
	  }
	  
	  if(page == 0)
	  {
		  chage_page = 0;
		  sprintf(ADC_Value_Str," %1.2fV", adc_value*3.3f/4096);
		  LCD_Display_String(120,70,ADC_Value_Str,WHITE,BLACK);
		  
		  sprintf(immediate_data," %04d",adc_value);
		  LCD_Display_String(120,110,immediate_data,WHITE,BLACK);
	  }
	  
	  if(page == 1)
	  {
		  chage_page = 1;
		  sprintf(adc_max_string," %1.2fV", adc_max*3.3f/4096);
		  LCD_Display_String(140,70,adc_max_string,WHITE,BLACK);
		  
		  sprintf(adc_min_string," %1.2fV",adc_min*3.3f/4096);
		  LCD_Display_String(140,110,adc_min_string,WHITE,BLACK);
	  }
	  
	  
	  // 测试最值
//	  sprintf(adc_max_string," %04d", adc_max);
//	  LCD_Display_String(140,70,adc_max_string,WHITE,BLACK);
//	  
//	  sprintf(adc_min_string," %04d",adc_min);
//	  LCD_Display_String(140,110,adc_min_string,WHITE,BLACK);
	  
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	
	// 使用定时器2实现一个均值滤波
	if(htim->Instance == htim2.Instance) 
	{
		for(i = 0, ad1 = 0; i < ADC_SAMPLE_NUM;)
			ad1 += ADC_Value[i++];
		
		adc_value = ad1 / ADC_SAMPLE_NUM;
		
		if(page == 1)
		{
			if(adc_value > adc_max)
				adc_max = adc_value;
			if(adc_value < adc_min && adc_value != 0)
				adc_min = adc_value;
		}
	}
}
uint8_t timer = 0;
void HAL_SYSTICK_Callback()
{
	timer++;
	
	if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin) == 0)
	{
		if(timer > 20)
		{
			if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin) == 0)
			{
				page = 0;chage_page = 1;
			}
			timer = 0;
		}
	}
	
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)
	{
		if(timer > 20)
		{
			if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)
			{
				page = 1;chage_page = 0;
			}
			timer = 0;
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
