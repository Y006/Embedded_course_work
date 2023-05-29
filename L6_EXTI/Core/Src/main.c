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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ST7789_Driver.h"
#include "example.h"
#include "stdio.h"
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
char EXTI0_num_str[20];
uint32_t EXTI0_num = 0;
char EXTI1_num_str[20];
uint32_t EXTI1_num = 0;
char EXTI2_num_str[20];
uint32_t EXTI2_num = 0;

uint8_t update_num = 0;
uint8_t update_led = 0;
uint8_t is_falling_edge_captured = 0;

uint8_t LED01_ON = 0;
uint8_t LED23_ON = 0;

uint32_t timer_led01_off = 0;
uint32_t timer_led23_off = 0;

uint8_t sorft_exti = 0;

uint8_t SWIT1_Flag, SWIT0_Flag;

uint8_t speed;
uint8_t flow_led;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void water_led(uint16_t delay_t);
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
  /* USER CODE BEGIN 2 */
ST7789_Init();
ST7789_Fill_Screen(BLACK);

LCD_Display_String(50,150,"Default interface",YELLOW,BLACK);

sprintf(EXTI0_num_str,"EXTI0_num: %d", EXTI0_num);
LCD_Display_String(65,60,EXTI0_num_str,WHITE,BLACK);
sprintf(EXTI1_num_str,"EXTI1_num: %d", EXTI1_num);
LCD_Display_String(65,80,EXTI1_num_str,WHITE,BLACK);
sprintf(EXTI2_num_str,"EXTI2_num: %d", EXTI2_num);
LCD_Display_String(65,100,EXTI2_num_str,WHITE,BLACK);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	  
	  if(EXTI0_num - EXTI1_num == 4) // EXTI0触发次数比EXTI1触发次数多4次或以上
				__HAL_GPIO_EXTI_GENERATE_SWIT(KEY1_Pin);
	  if(EXTI1_num - EXTI0_num == 4) // EXTI1触发次数比EXTI0触发次数多4次或以上
				__HAL_GPIO_EXTI_GENERATE_SWIT(KEY0_Pin);
	  
	  if(update_num)
	  {
		sprintf(EXTI0_num_str,"EXTI0_num: %d", EXTI0_num);
		LCD_Display_String(65,60,EXTI0_num_str,WHITE,BLACK);
		sprintf(EXTI1_num_str,"EXTI1_num: %d", EXTI1_num);
		LCD_Display_String(65,80,EXTI1_num_str,WHITE,BLACK);
		sprintf(EXTI2_num_str,"EXTI2_num: %d", EXTI2_num);
		LCD_Display_String(65,100,EXTI2_num_str,WHITE,BLACK);
		
		update_num = 0;
		is_falling_edge_captured = 0;
	  }
	  
	  if(update_led)
	  {
		if(LED01_ON) 
		{
			HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,1);
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
		}
		else
		{
			HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,0);
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
		}
		if(LED23_ON) 
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,1);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
		}
		else
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
		}
		update_led = 0;
	  }
	  
	  if(flow_led)
	  {
		  sprintf(EXTI2_num_str,"EXTI2_num: %d", EXTI2_num);
		 LCD_Display_String(65,100,EXTI2_num_str,WHITE,BLACK);
		  if(speed == 1)
		  {
			  water_led(1000);
		  }
		  else if(speed == 2)
		  {
			  water_led(500);
		  }
		  else if(speed == 3)
		  {
			  water_led(100);
		  }
	  }
	  
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
void HAL_SYSTICK_Callback()
{
	if(LED01_ON)
	{
		timer_led01_off++;
		if(timer_led01_off >= 2000)
		{
			update_led = 1;
			LED01_ON = 0;
			timer_led01_off = 0;
		}
	}
	if(LED23_ON)
	{
		timer_led23_off++;
		if(timer_led23_off >= 2000)
		{
			update_led = 1;
			LED23_ON = 0;
			timer_led23_off = 0;
		}
	}
	
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  update_num = 1;
	
  if (GPIO_Pin == KEY0_Pin && !is_falling_edge_captured) {
    EXTI0_num++;
	LED01_ON = 1;
	update_led = 1;
	is_falling_edge_captured = 1;
  }
  else if (GPIO_Pin == KEY1_Pin && !is_falling_edge_captured) {
    EXTI1_num++;
	update_led = 1;
	LED23_ON = 1;
	is_falling_edge_captured = 1;
//	HAL_Delay(1000);
  }
  else if (GPIO_Pin == KEY2_Pin && !is_falling_edge_captured) {
    EXTI2_num++;
	switch (EXTI2_num % 3) {
        case 0:
            speed = 3;
            break;
        case 1:
            speed = 1;
            break;
        case 2:
            speed = 2;
            break;
    }
	flow_led = 1;
	is_falling_edge_captured = 1;
  }

}
void water_led(uint16_t delay_t)
{
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	HAL_Delay(delay_t);
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	HAL_Delay(delay_t);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	HAL_Delay(delay_t);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	

	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	HAL_Delay(delay_t);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
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
