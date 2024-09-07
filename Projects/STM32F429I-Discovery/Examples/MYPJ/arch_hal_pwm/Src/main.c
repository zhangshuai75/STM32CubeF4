/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "pwm_driver.h"
#include "api_pwm_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Pwm3_1 = pwm3_1_device_binding();
	pwm_init(Pwm3_1);
	printf("PWM device init\r\n");
	
	uint8_t duty_cycle;
	uint16_t frequency;
	
	while(1) {
		for(frequency = 14; frequency < 20000; frequency++) {
			for(duty_cycle = 0; duty_cycle < 100; duty_cycle++) {
				pwm_output(Pwm3_1, frequency, duty_cycle);
				printf("frequency: %d, duty cycle: %d\r\n", frequency, duty_cycle);
				HAL_Delay(10);
			}
			for(duty_cycle = 100; duty_cycle > 0; duty_cycle--) {
				pwm_output(Pwm3_1, frequency, duty_cycle);
				printf("frequency: %d, duty cycle: %d\r\n", frequency, duty_cycle);
				HAL_Delay(10);
			}
		}
	}
}
