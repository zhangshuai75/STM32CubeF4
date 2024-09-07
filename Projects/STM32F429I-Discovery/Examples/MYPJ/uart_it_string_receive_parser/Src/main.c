/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "api_define.h"
#include "uart3.h"
#include "uart6.h"
#include "uart7.h"
#include "uart_it_callback_parser.h"
#include "main.h"


uint8_t buffer3[10] = "Hi buf 3\r\n";
uint8_t buffer6[10] = "Hi buf 6\r\n";
uint8_t buffer7[10] = "Hi buf 7\r\n";

static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void HAL_GPIO_EXTI_Callback(uint16_t gpio_Pin)
{
	if(gpio_Pin == GPIO_PIN_0) {
		#ifdef UART3_IT
		struct uart_api *Uart3 = (struct uart_api *)uart3_binding();
		Uart3->transmit_it(buffer3, 10);
		#endif
		#ifdef UART6_IT
		struct uart_api *Uart6 = (struct uart_api *)uart6_binding();
		Uart6->transmit_it(buffer6, 10);
		#endif
		#ifdef UART7_IT
		struct uart_api *Uart7 = (struct uart_api *)uart7_binding();
		Uart7->transmit_it(buffer7, 10);
		#endif
  }
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

int main(void)
{
	system_initialization();
	uart_printf_init();
	EXTILine0_Config();
	
	#ifdef UART3_IT
	struct uart_api *Uart3 = (struct uart_api *)uart3_binding();
	Uart3->init();
	Uart3->receive_it(&uart_it_1_callback_string_byte, 1);
	uint8_t *uart3_string_checkout;	
	#endif
	#ifdef UART6_IT
	struct uart_api *Uart6 = (struct uart_api *)uart6_binding();
	Uart6->init();
	Uart6->receive_it(&uart_it_2_callback_string_byte, 1);
	uint8_t *uart6_string_checkout;	
	#endif
	#ifdef UART7_IT
	struct uart_api *Uart7 = (struct uart_api *)uart7_binding();
	Uart7->init();
	Uart7->receive_it(&uart_it_3_callback_string_byte, 1);
	uint8_t *uart7_string_checkout;	
	#endif
	
	while(1) {
		#ifdef UART3_IT
		uart3_string_checkout = uart_it_1_callback_string_out();
		if(uart3_string_checkout != NULL) {
			printf("U3:%s", uart3_string_checkout);
		}
		#endif
		#ifdef UART6_IT
		uart6_string_checkout = uart_it_2_callback_string_out();
		if(uart6_string_checkout != NULL) {
			printf("U6:%s", uart6_string_checkout);
		}
		#endif
		#ifdef UART7_IT
		uart7_string_checkout = uart_it_3_callback_string_out();
		if(uart7_string_checkout != NULL) {
			printf("U7:%s", uart7_string_checkout);
		}
		#endif
	}
}
