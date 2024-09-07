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
#include "uart_callback.h"
#include "main.h"


uint8_t buffer3[10];
uint8_t buffer6[10];
uint8_t buffer7[10];

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
		#ifdef UART3_DMA
		struct uart_api *Uart3 = (struct uart_api *)uart3_binding();
		Uart3->transmit_dma(buffer3, 10);
		#endif
		
		#ifdef UART6_DMA
		struct uart_api *Uart6 = (struct uart_api *)uart6_binding();
		Uart6->transmit_dma(buffer6, 10);
		#endif
		
		#ifdef UART7_DMA
		struct uart_api *Uart7 = (struct uart_api *)uart7_binding();
		Uart7->transmit_dma(buffer7, 10);
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
	
	#ifdef UART3_DMA
	uint8_t rx_data3;
	struct uart_api *Uart3 = (struct uart_api *)uart3_binding();
	Uart3->init();
	Uart3->receive_dma(&rx_data3, 1);
	e_uart3_rx_callbake_flag = SET;
	uint16_t u3 = 0;
	#endif
	
	#ifdef UART6_DMA
	uint8_t rx_data6;
	struct uart_api *Uart6 = (struct uart_api *)uart6_binding();
	Uart6->init();
	Uart6->receive_dma(&rx_data6, 1);
	e_uart6_rx_callbake_flag = SET;
	uint16_t u6 = 0;
	#endif
	
	#ifdef UART7_DMA
	uint8_t rx_data7;
	struct uart_api *Uart7 = (struct uart_api *)uart7_binding();
	Uart7->init();
	Uart7->receive_dma(&rx_data7, 1);
	e_uart7_rx_callbake_flag = SET;
	uint16_t u7 = 0;
	#endif
	
	
	while(1) {
		#ifdef UART3_DMA
		if(e_uart3_rx_callbake_flag == RESET) {
			buffer3[u3] = rx_data3;
			u3++;
			if(u3 >= 10) {
				u3 = 0;
			}
			Uart3->receive_dma(&rx_data3, 1);
			e_uart3_rx_callbake_flag = SET;
		}
		#endif
		
		#ifdef UART6_DMA
		if(e_uart6_rx_callbake_flag == RESET) {
			buffer6[u6] = rx_data6;
			u6++;
			if(u6 >= 10) {
				u6 = 0;
			}
			Uart6->receive_dma(&rx_data6, 1);
			e_uart6_rx_callbake_flag = SET;
		}
		#endif
		
		#ifdef UART7_DMA
		if(e_uart7_rx_callbake_flag == RESET) {
			buffer7[u7] = rx_data7;
			u7++;
			if(u7 >= 10) {
				u7 = 0;
			}
			Uart7->receive_dma(&rx_data7, 1);
			e_uart7_rx_callbake_flag = SET;
		}
		#endif
	}
}
