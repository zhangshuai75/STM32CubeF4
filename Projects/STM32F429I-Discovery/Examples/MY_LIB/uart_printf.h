/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_PRINTF_H
#define __UART_PRINTF_H


/* Definition for USARTxPrintf clock resources */
#define USARTxPrintf                           USART1
#define USARTxPrintf_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE()
#define USARTxPrintf_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTxPrintf_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 

#define USARTxPrintf_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTxPrintf_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTxPrintf Pins */
#define USARTxPrintf_TX_PIN                    GPIO_PIN_9
#define USARTxPrintf_TX_GPIO_PORT              GPIOA  
#define USARTxPrintf_TX_AF                     GPIO_AF7_USART1

#define USARTxPrintf_RX_PIN                    GPIO_PIN_10
#define USARTxPrintf_RX_GPIO_PORT              GPIOA 
#define USARTxPrintf_RX_AF                     GPIO_AF7_USART1

void uart_printf_init(void);
//Note: Remember enable the "#define HAL_UART_MODULE_ENABLED" in stm32f4xx_hal_conf.h


#endif
