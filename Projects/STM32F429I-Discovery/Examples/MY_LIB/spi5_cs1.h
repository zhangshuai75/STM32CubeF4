/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI5_CS1_H
#define __SPI5_CS1_H


#define SPI5C1_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOC_CLK_ENABLE()
#define SPI5C1_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOC_CLK_DISABLE()

#define SPI5C1_OUTPUT_PIN                 GPIO_PIN_1
#define SPI5C1_OUTPUT_PORT                GPIOC

struct spi_api* spi5_cs1_binding(void);


#endif
