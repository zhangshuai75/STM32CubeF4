/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "timer3.h"
#include "main.h"


extern uint32_t count;

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct timer_api *Timer3 = timer3_binding();
	Timer3->init();
	
	//max clk = 90Mhz
	uint32_t prescaler = 9000;
	
	uint32_t period1 = 10000;
	uint32_t period2 = 20000;
	uint32_t period3 = 5000;
	uint32_t period4 = 60000;
	uint32_t period5 = 1000;
	
	while(1) {
		count = 0;
		printf("1 sec of 60 sec\r\n");
		Timer3->timer_start_it(period1-1, prescaler-1); // 1/(90M/period1*perscaler) = 1 sec
		HAL_Delay(8000);
		Timer3->timer_stop_it();
		HAL_Delay(5000);
		Timer3->timer_start_it(period1-1, prescaler-1);
		HAL_Delay(15000);
		Timer3->timer_stop_it();
		HAL_Delay(12000);
		Timer3->timer_start_it(period1-1, prescaler-1);
		HAL_Delay(20000);
		Timer3->timer_stop_it();
		
		count = 0;
		printf("2 sec of 60 sec\r\n");
		Timer3->timer_start_it(period2-1, prescaler-1); // 1/(90M/period2*perscaler) = 2 sec
		HAL_Delay(60000);
		Timer3->timer_stop_it();
		
		count = 0;
		printf("0.5 sec of 60 sec\r\n");
		Timer3->timer_start_it(period3-1, prescaler-1); // 1/(90M/period3*perscaler) = 0.5 sec
		HAL_Delay(60000);
		Timer3->timer_stop_it();
		
		count = 0;
		printf("6 sec of 60 sec\r\n");
		Timer3->timer_start_it(period4-1, prescaler-1); // 1/(90M/period4*perscaler) = 6 sec
		HAL_Delay(60000);
		Timer3->timer_stop_it();
		
		count = 0;
		printf("0.1 sec of 60 sec\r\n");
		Timer3->timer_start_it(period5-1, prescaler-1); // 1/(90M/period5*perscaler) = 0.1 sec
		HAL_Delay(60000);
		Timer3->timer_stop_it();
	}
}
