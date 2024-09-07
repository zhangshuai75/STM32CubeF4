/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI5_H
#define __SPI5_H


#define SPI5_CLK_ENABLE()               __HAL_RCC_SPI5_CLK_ENABLE()
#define SPI5_SCK_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI5_MISO_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI5_MOSI_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI5_MISO_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOF_CLK_DISABLE()
#define SPI5_MOSI_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOF_CLK_DISABLE()

#define SPI5_FORCE_RESET()              __HAL_RCC_SPI5_FORCE_RESET()
#define SPI5_RELEASE_RESET()            __HAL_RCC_SPI5_RELEASE_RESET()

#define SPI5_CLKPOLARITY                SPI_POLARITY_LOW
#define SPI5_CLKPHASE                   SPI_PHASE_1EDGE
#define SPI5_BAUDRATEPRESCALER          SPI_BAUDRATEPRESCALER_32

#define SPI5_SCK_PIN                    GPIO_PIN_7
#define SPI5_SCK_GPIO_PORT              GPIOF
#define SPI5_SCK_AF                     GPIO_AF5_SPI5

#define SPI5_MISO_PIN                   GPIO_PIN_8
#define SPI5_MISO_GPIO_PORT             GPIOF
#define SPI5_MISO_AF                    GPIO_AF5_SPI5

#define SPI5_MOSI_PIN                   GPIO_PIN_9
#define SPI5_MOSI_GPIO_PORT             GPIOF
#define SPI5_MOSI_AF                    GPIO_AF5_SPI5

#ifdef SPI5_IT
void SPI5_IRQHandler(void);

#ifdef SPI5_DMA
#define DMA_SPI5_CLK_ENABLE()          __HAL_RCC_DMA2_CLK_ENABLE()

#define DMA_SPI5_TX_STREAM             DMA2_Stream4
#define DMA_SPI5_RX_STREAM             DMA2_Stream3
#define DMA_SPI5_TX_CHANNEL            DMA_CHANNEL_2
#define DMA_SPI5_RX_CHANNEL            DMA_CHANNEL_2

#define DMA_SPI5_TX_IRQn               DMA2_Stream4_IRQn
#define DMA_SPI5_RX_IRQn               DMA2_Stream3_IRQn
#define DMA_SPI5_TX_IRQHandler         DMA2_Stream4_IRQHandler
#define DMA_SPI5_RX_IRQHandler         DMA2_Stream3_IRQHandler

void DMA_SPI5_TX_IRQHandler(void);
void DMA_SPI5_RX_IRQHandler(void);
#endif
#endif

void spi5_init(void);
void _SPI5_MspDeInit(void);


#endif
