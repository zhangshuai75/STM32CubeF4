/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "nrf24l01_driver.h"
#include "api_rf_common.h"
#include "main.h"


int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Nrf24l01 = nrf24l01_device_binding();
	rf_init(Nrf24l01);
	printf("All device init finish\r\n");
	
	rf_device_test(Nrf24l01);
	
	while(1) {
	}
}
