#include "bsp_device.h"

extern uint32_t led_cnt;
extern int8_t device_state;

void water_led(int8_t device_state)
{
	led_cnt++;
	if (HAL_GPIO_ReadPin(LED0_GPIO_Port, LED0_Pin) == 1)
	{
		if (device_state == 1)
		{
			if (led_cnt > 50)
			{
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
		else if (device_state == 2)
		{
			if (led_cnt > 500)
			{
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
	}
	else if (HAL_GPIO_ReadPin(LED1_GPIO_Port, LED1_Pin) == 1)
	{
		if (device_state == 1)
		{
			if (led_cnt > 50)
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
		else if (device_state == 2)
		{
			if (led_cnt > 500)
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
	}
	else if (HAL_GPIO_ReadPin(LED2_GPIO_Port, LED2_Pin) == 1)
	{
		if (device_state == 1)
		{
			if (led_cnt > 50)
			{
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
		else if (device_state == 2)
		{
			if (led_cnt > 500)
			{
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
	}
	else if (HAL_GPIO_ReadPin(LED3_GPIO_Port, LED3_Pin) == 1)
	{
		if (device_state == 1)
		{
			if (led_cnt > 50)
			{
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
		else if (device_state == 2)
		{
			if (led_cnt > 500)
			{
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				led_cnt = 0;
			}
		}
	}
}

void turn_on_beep(void)
{
	HAL_GPIO_WritePin(BEEP1_GPIO_Port, BEEP1_Pin, GPIO_PIN_SET);
}

void turn_off_all(void)
{
	HAL_GPIO_WritePin(BEEP1_GPIO_Port, BEEP1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
}

void key_scan(void)
{
	if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == 0)
	{
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == 0)
		{
			while (HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == 0)
				;
			turn_off_all();
			HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
			device_state = 1;
		}
	}
	if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
	{
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0)
		{
			turn_off_all();
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
			device_state = 2;
		}
	}
	if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
	{
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == 0)
		{
			turn_off_all();
			device_state = 3;
		}
	}
	if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)
	{
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == 0)
			device_state = 4;
	}
}
