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
#include "ST7789_Driver.h"
#include "stdio.h"

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"

#include "multi_button.h"

#include "homepage.h"
#include "simple_oscilloscope.h"
#include "picture.h"
#include "init_menu.h"
#include "menu.h"

#include "arm_math.h"

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

//============================== ADC变量定义 ========================================
/* 定义ADC采样的数据个数 */
#define ADC_SAMPLE_NUM  1000

/* 定义ADC采样的数据缓存区 */
uint32_t ADC_Value[ADC_SAMPLE_NUM];

//FFT长度，默认是1024点FFT
#define FFT_LENGTH		ADC_SAMPLE_NUM

/*全局变量，在main之前定义*/
arm_cfft_radix4_instance_f32 scfft;//定义scfft结构体
float FFT_InputBuf[FFT_LENGTH*2]; //FFT输入数组
float FFT_OutputBuf[FFT_LENGTH]; //FFT输出数组
//============================== ADC变量定义 ========================================
//============================== MultiButton 结构体定义 ======================================
enum Button_ID
{
      btn1_id, btn2_id, btn3_id
};

struct Button btn1, btn2, btn3;
//============================== MultiButton 结构体定义 ======================================
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



//============================== MultiButton 回调函数 ======================================
uint8_t read_button_GPIO(uint8_t button_id)
{
	// you can share the GPIO read function with multiple Buttons
	switch(button_id)
	{
		case btn1_id:
			return HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin);
			break;
		case btn2_id:
			return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
			break;
		case btn3_id:
			return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
			break;
		default:
			return 0;
			break;
	}
}
//============================== MultiButton 回调函数 ======================================



//// Function prototypes for menu actions
//void init_menu_action(void);
//void oscilloscope_action(void);
//void lv_simple_oscilloscope_action(void);

////lv_simple_oscilloscope();
////img_wechat_donate();
////img_chat_head();
////img_icons8_oscilloscope_64();
////init_menu();
////lv_simple_oscilloscope();


//void init_anim_action()
//{
//	init_anim();
//}
void img_icons8_oscilloscope_64_action()
{
	img_icons8_oscilloscope_64();
}
void img_chat_head_action()
{
	img_chat_head();
}
void img_wechat_donate_action()
{
	img_wechat_donate();
}
bool shouldUpdateOsc = false;
void lv_simple_oscilloscope_action()
{
	lv_simple_oscilloscope();
	shouldUpdateOsc = true;
	user_main_debug("creat Simple Oscilloscope done!\n");
}


// 首先声明所有的菜单项
//struct MenuItem my_menu_init;
struct MenuItem menu_oscilloscope;
struct MenuItem menu_lv_simple_oscilloscope;
struct MenuItem menu_wechat_img;
struct MenuItem menu_head_img;

//struct MenuItem my_menu_init = { 
//    .action = init_anim_action, 
//    .hide_action = init_anim_hide_action, 
//    .subMenu = &menu_oscilloscope, 
//    .parentMenu = NULL,
//    .prev = NULL,
//    .next = NULL 
//};

struct MenuItem menu_oscilloscope = { 
    .action = img_icons8_oscilloscope_64_action, 
    .hide_action = img_icons8_oscilloscope_64_hide_action, 
    .subMenu = &menu_lv_simple_oscilloscope, 
    .parentMenu = NULL, 
    .prev = &menu_wechat_img, 
    .next = &menu_head_img 
};
struct MenuItem menu_wechat_img = { 
    .action = img_chat_head_action, 
    .hide_action = img_chat_head_hide_action, 
    .subMenu = NULL, 
    .parentMenu = NULL, 
    .prev = NULL, 
    .next = &menu_oscilloscope 
};
struct MenuItem menu_head_img = { 
    .action = img_wechat_donate_action, 
    .hide_action = img_wechat_donate_hide_action, 
    .subMenu = NULL, 
    .parentMenu = NULL, 
    .prev = &menu_oscilloscope, 
    .next = NULL 
};

struct MenuItem menu_lv_simple_oscilloscope = { 
    .action = lv_simple_oscilloscope_action, 
    .hide_action = lv_simple_oscilloscope_hide_action, 
    .subMenu = NULL,
    .parentMenu = &menu_oscilloscope,
    .prev = NULL,
    .next = NULL 
};

// Pointer to current menu
MenuItem *currentMenu = &menu_oscilloscope;

//============================== MultiButton 回调处理 ======================================

bool ClickToStart = false;

//void BTN2_SINGLE_Click_Handler(void* btn)
//{
//    shouldUpdateSer1 = false;  // 设置标志以防止更新ser1
//	ClickToStart = false;

//}

//void BTN2_DOUBLE_Click_Handler(void* btn)
//{
//    shouldUpdateSer1 = true;  // 重置标志以允许更新ser1
//	ClickToStart = true;
//}

//void BTN1_SINGLE_Click_Handler(void* btn)
//{
//	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
//}
//void BTN3_SINGLE_Click_Handler(void* btn)
//{
//	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,1);
//}


void BTN1_SINGLE_Click_Handler(void* btn)
{
    menu_prev(&currentMenu);
}
void BTN3_SINGLE_Click_Handler(void* btn)
{
	menu_next(&currentMenu);
}
void BTN2_SINGLE_Click_Handler(void* btn)
{
	menu_select(&currentMenu);
}
void BTN2_DOUBLE_Click_Handler(void* btn)
{
    menu_back(&currentMenu);
}

//============================== MultiButton 回调处理 ======================================

void ChangeTimerParameters(TIM_HandleTypeDef *htim, uint32_t prescaler, uint32_t period)
{
    HAL_TIM_Base_Stop(htim); // Stop the timer

    htim->Init.Prescaler = prescaler; // Change the prescaler
    htim->Init.Period = period; // Change the period

    if (HAL_TIM_Base_Init(htim) != HAL_OK) // Re-initialize the timer with the new parameters
    {
        // Handle the error
    }

    HAL_TIM_Base_Start(htim); // Start the timer
}

//============================== 串口重定向开始 ======================================
int fputc(int ch, FILE *f)
{
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart2, temp, 1, 2);//hlpuart1需要根据你的配置修改
	return ch;
}
//============================== 串口重定向结束 ======================================

//============================== FFT 函数开始 ======================================
/* 初始化FFT实例 */
//void FFT_Init(void)
//{
//    arm_cfft_radix4_init_f32(&scfft, FFT_LENGTH, 0, 1);
//}
//float32_t frequency = 0;
///* 计算FFT并提取频率 */
//void ComputeFFT(void)
//{
//    for (uint32_t i = 0; i < FFT_LENGTH; i++)
//    {
//        /* 注意: 这里假设了ADC输出是12位的 */
//        FFT_InputBuf[2 * i] = ((float32_t)ADC_Value[i]) / 4096.0f;
//        FFT_InputBuf[2 * i + 1] = 0;
//    }

//    arm_cfft_radix4_f32(&scfft, FFT_InputBuf);

//    arm_cmplx_mag_f32(FFT_InputBuf, FFT_OutputBuf, FFT_LENGTH);

//    /* 找到频谱中最大值的索引 */
//    uint32_t maxIndex;
//    arm_max_f32(FFT_OutputBuf, FFT_LENGTH, NULL, &maxIndex);

//    /* 计算频率: 这里采样率是20kHz */
//    frequency = ((float32_t)maxIndex) * 20000.0f / FFT_LENGTH;

//    /* 这里可以使用计算得到的频率值 */
//}
//============================== FFT 函数结束 ======================================

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
  MX_TIM1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
ST7789_Init();

lv_init();
lv_port_disp_init();
lv_port_indev_init();

HAL_TIM_Base_Start_IT(&htim2);
HAL_TIM_Base_Start(&htim3);
HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, ADC_SAMPLE_NUM);

//lv_simple_oscilloscope();
//img_wechat_donate();
//img_chat_head();
//img_icons8_oscilloscope_64();
//lv_simple_oscilloscope();
//init_anim();

//lv_obj_t * arc_init = init_anim();

currentMenu->action();
//cleanup_lvgl_components(arc_init);

HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

button_init(&btn2, read_button_GPIO, 0, btn2_id);
button_attach(&btn2, SINGLE_CLICK,     BTN2_SINGLE_Click_Handler);
button_attach(&btn2, DOUBLE_CLICK,     BTN2_DOUBLE_Click_Handler);
button_start(&btn2);

button_init(&btn1, read_button_GPIO, 0, btn1_id);
button_attach(&btn1, SINGLE_CLICK,     BTN1_SINGLE_Click_Handler);
button_start(&btn1);

button_init(&btn3, read_button_GPIO, 0, btn3_id);
button_attach(&btn3, SINGLE_CLICK,     BTN3_SINGLE_Click_Handler);
button_start(&btn3);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  lv_task_handler();
	  if(shouldUpdateOsc)
		lv_update_value_mul(ADC_SAMPLE_NUM, ADC_Value);
//	  cleanup_lvgl_components();
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
uint8_t timer = 0;
void HAL_SYSTICK_Callback()
{
	timer++;
	if(timer > 5)
	{
		button_ticks(); //1ms ticks
		timer = 0;
	}
	lv_tick_inc(1);//在中断里面进行刷新
}

//uint8_t timer1 = 0;
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	if(htim-> Instance == htim2.Instance) {
//		timer1++;
//		if(timer1 > 51)
//			
////			// 将采样的 100 个电压数据进行均值滤波
////		  for(i = 0, ad1 = 0; i < ADC_SAMPLE_NUM;)
////			ad1 += ADC_Value[i++];
////		  ad1 /= ADC_SAMPLE_NUM;
//	}
//	
//}
/* ADC DMA中断服务程序 */
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//    if(hadc->Instance == ADC1) 
//    {
//        ComputeFFT();
//    }
//}
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
