/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "uart_driver.h"
#include "api_uart_common.h"
#include "main.h"


uint8_t u3_rx[1];
uint8_t u6_rx[1];
uint8_t u7_rx[1];
uint8_t u3[] = "u3";
uint8_t u6[] = "u6";
uint8_t u7[] = "u7";

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Uart3 = uart3_device_binding();
	struct device *Uart6 = uart6_device_binding();
	struct device *Uart7 = uart7_device_binding();
	uart_init(Uart3);
	uart_init(Uart6);
	uart_init(Uart7);
	printf("UART device init\r\n");
	
	uart_receive(Uart3, u3_rx, 1);
	
	while(1) {
		uart_receive(Uart6, u6_rx, 1);
		if(u6_rx[0] == 0x66) {
			printf("Hi u6fff\r\n");
			uart_transmit(Uart6, u6, 2);
		}
		
		uart_receive(Uart7, u7_rx, 1);
		if(u7_rx[0] == 0x66) {
			printf("Hi u7fff\r\n");
			uart_transmit(Uart7, u7, 2);
		}
  }
}

void uart3_rx_callback_handel(struct device *Uart3)
{
	uart_transmit(Uart3, u3_rx, 1);
	uart_receive(Uart3, u3_rx, 1);
}
