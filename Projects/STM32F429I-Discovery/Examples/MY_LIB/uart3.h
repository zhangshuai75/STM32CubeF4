/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART3_H
#define __UART3_H


#define USART3_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE()
#define USART3_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USART3_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USART3_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USART3_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

#define USART3_BAUDRATE                  115200

#define USART3_TX_PIN                    GPIO_PIN_8
#define USART3_TX_GPIO_PORT              GPIOD
#define USART3_TX_AF                     GPIO_AF7_USART3

#define USART3_RX_PIN                    GPIO_PIN_9
#define USART3_RX_GPIO_PORT              GPIOD
#define USART3_RX_AF                     GPIO_AF7_USART3

#ifdef UART3_IT
void USART3_IRQHandler(void);

#ifdef UART3_DMA
#define DMA_UART3_CLK_ENABLE()          __HAL_RCC_DMA1_CLK_ENABLE()

#define DMA_UART3_TX_STREAM             DMA1_Stream3
#define DMA_UART3_RX_STREAM             DMA1_Stream1
#define DMA_UART3_TX_CHANNEL            DMA_CHANNEL_4
#define DMA_UART3_RX_CHANNEL            DMA_CHANNEL_4

#define DMA_UART3_TX_IRQn               DMA1_Stream3_IRQn
#define DMA_UART3_RX_IRQn               DMA1_Stream1_IRQn
#define DMA_UART3_TX_IRQHandler         DMA1_Stream3_IRQHandler
#define DMA_UART3_RX_IRQHandler         DMA1_Stream1_IRQHandler

void DMA_UART3_TX_IRQHandler(void);
void DMA_UART3_RX_IRQHandler(void);
#endif
#endif

struct uart_api* uart3_binding(void);


#endif
