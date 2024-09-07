/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "pwm3_1.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct pwm_api *Pwm3_1 = pwm3_1_binding();
	Pwm3_1->init();
	
	//max clk = 90Mhz
	uint32_t prescaler = 9000; // /9K, max clk = 10Khz
	
	uint32_t period1 = 10000; // /10K ,pwm = 1   hz
	uint32_t period2 = 1000;  // /1K  ,pwm = 10  hz
	uint32_t period3 = 100;   // /100 ,pwm = 100 hz
	uint32_t period4 = 10;    // /10  ,pwm = 1K  hz
	uint32_t period5 = 2;     // /2   ,pwm = 5K  hz
	
	uint32_t period_test;
	uint32_t prescaler_test;
	
	while(1) {
		Pwm3_1->pin_set(period1-1, period1/2, prescaler-1); //(90M/period1*perscaler) = 1
		HAL_Delay(5000);
		Pwm3_1->pin_set(period2-1, period2/2, prescaler-1); //(90M/period2*perscaler) = 10
		HAL_Delay(5000);
		Pwm3_1->pin_set(period3-1, period3/2, prescaler-1); //(90M/period3*perscaler) = 100
		HAL_Delay(5000);
		Pwm3_1->pin_set(period4-1, period4/2, prescaler-1); //(90M/period4*perscaler) = 1K
		HAL_Delay(5000);
		Pwm3_1->pin_set(period5-1, period5/2, prescaler-1); //(90M/period5*perscaler) = 5K
		HAL_Delay(5000);
		
		//frequency count to 1000hz from 100hz use period
		for(period_test = 100; period_test >= 10; period_test -= 1) {
			Pwm3_1->pin_set(period_test-1, period_test/2, prescaler-1);
			HAL_Delay(500);
		}
		
		//frequency count to 1000hz from 100hz use perscaler
		for(prescaler_test = 9000; prescaler_test >= 900; prescaler_test -= 10) {
			Pwm3_1->pin_set(period3-1, period3/2, prescaler_test-1);
			HAL_Delay(100);
		}
	}
}
