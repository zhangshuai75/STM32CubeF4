/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "uart_callback.h"


#ifdef UART3_IT
__IO FlagStatus e_uart3_rx_callbake_flag = RESET;
	#ifdef UART3_DMA
		#ifdef U3_DMA_CALLBACK_PARSER
		#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U3_IT_CALLBACK_PARSER
	#include "uart_it_callback_parser.h"
	#endif
#endif

#ifdef UART6_IT
__IO FlagStatus e_uart6_rx_callbake_flag = RESET;
	#ifdef UART6_DMA
		#ifdef U6_DMA_CALLBACK_PARSER
		#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U6_IT_CALLBACK_PARSER
	#include "uart_it_callback_parser.h"
	#endif
#endif

#ifdef UART7_IT
__IO FlagStatus e_uart7_rx_callbake_flag = RESET;
	#ifdef UART7_DMA
		#ifdef U7_DMA_CALLBACK_PARSER
		#include "uart_dma_callback_parser.h"
		#endif
	#endif
	
	#ifdef U7_IT_CALLBACK_PARSER
	#include "uart_it_callback_parser.h"
	#endif
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
	}
	#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
		e_uart3_rx_callbake_flag = RESET;
		#ifdef U3_IT_CALLBACK_PARSER
		SEL_UART3_IT_CALLBACK_PARSER(UartHandle);
		#endif
		#ifdef U3_DMA_CALLBACK_PARSER
		SEL_UART3_DMA_CALLBACK_PARSER(UartHandle);
		#endif
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
		e_uart6_rx_callbake_flag = RESET;
		#ifdef U6_IT_CALLBACK_PARSER
		SEL_UART6_IT_CALLBACK_PARSER(UartHandle);
		#endif
		#ifdef U6_DMA_CALLBACK_PARSER
		SEL_UART6_DMA_CALLBACK_PARSER(UartHandle);
		#endif
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
		e_uart7_rx_callbake_flag = RESET;
		#ifdef U7_IT_CALLBACK_PARSER
		SEL_UART7_IT_CALLBACK_PARSER(UartHandle);
		#endif
		#ifdef U7_DMA_CALLBACK_PARSER
		SEL_UART7_DMA_CALLBACK_PARSER(UartHandle);
		#endif
	}
	#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	#ifdef UART3_IT
	if(UartHandle->Instance == USART3) {
	}
	#endif
	
	#ifdef UART6_IT
	if(UartHandle->Instance == USART6) {
	}
	#endif
	
	#ifdef UART7_IT
	if(UartHandle->Instance == UART7) {
	}
	#endif
}
