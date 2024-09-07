/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART6_H
#define __UART6_H


#define USART6_CLK_ENABLE()              __HAL_RCC_USART6_CLK_ENABLE()
#define USART6_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define USART6_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define USART6_FORCE_RESET()             __HAL_RCC_USART6_FORCE_RESET()
#define USART6_RELEASE_RESET()           __HAL_RCC_USART6_RELEASE_RESET()

#define USART6_BAUDRATE                  115200

#define USART6_TX_PIN                    GPIO_PIN_6
#define USART6_TX_GPIO_PORT              GPIOC
#define USART6_TX_AF                     GPIO_AF8_USART6

#define USART6_RX_PIN                    GPIO_PIN_7
#define USART6_RX_GPIO_PORT              GPIOC
#define USART6_RX_AF                     GPIO_AF8_USART6

#ifdef UART6_IT
void USART6_IRQHandler(void);

#ifdef UART6_DMA
#define DMA_UART6_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()

#define DMA_UART6_TX_STREAM             DMA2_Stream6
#define DMA_UART6_RX_STREAM             DMA2_Stream1
#define DMA_UART6_TX_CHANNEL            DMA_CHANNEL_5
#define DMA_UART6_RX_CHANNEL            DMA_CHANNEL_5

#define DMA_UART6_TX_IRQn               DMA2_Stream6_IRQn
#define DMA_UART6_RX_IRQn               DMA2_Stream1_IRQn
#define DMA_UART6_TX_IRQHandler         DMA2_Stream6_IRQHandler
#define DMA_UART6_RX_IRQHandler         DMA2_Stream1_IRQHandler

void DMA_UART6_TX_IRQHandler(void);
void DMA_UART6_RX_IRQHandler(void);
#endif
#endif

struct uart_api* uart6_binding(void);


#endif
