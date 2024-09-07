/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "device.h"
#include "gpio_driver.h"
#include "api_gpio_common.h"
#include "main.h"


static void main_thread(const void *argument)
{
	struct device *Gpio_a0 = gpio_a0_device_binding();
	struct device *Gpio_g13 = gpio_g13_device_binding();
	gpio_init(Gpio_a0);
	gpio_init(Gpio_g13);
	printf("GPIO device init\r\n");
	
	#ifdef A0_EXTI
	while(1) {
	}
	#elif A0_INPUT
	printf("PA0 Counter %d msec\r\n", gpio_press_time(Gpio_a0, MILLISECOND));
	printf("PA0 Counter %d sec\r\n", gpio_press_time(Gpio_a0, SECOND));
	while(1) {
		if(gpio_read(Gpio_a0)) {
			gpio_write(Gpio_g13, 1);
			printf("PA0 STATE %d\r\n", gpio_read(Gpio_a0));
			HAL_Delay(100);
		}else {
			gpio_write(Gpio_g13, 0);
			printf("PA0 STATE %d\r\n", gpio_read(Gpio_a0));
			HAL_Delay(100);
		}
	}
	#endif
}

void a0_exti_handel(void)
{
	struct device *Gpio_g13 = gpio_g13_device_binding();
	gpio_toggle_write(Gpio_g13);
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	osThreadDef(main, main_thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(main), NULL);
	
	osKernelStart();
	while(1) {
	}
}
