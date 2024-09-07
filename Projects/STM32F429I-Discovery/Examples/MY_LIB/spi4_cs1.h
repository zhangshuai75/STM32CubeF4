/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI4_CS1_H
#define __SPI4_CS1_H


#define SPI4C1_OUTPUT_CLK_ENABLE()        __HAL_RCC_GPIOG_CLK_ENABLE()
#define SPI4C1_OUTPUT_CLK_DISABLE()       __HAL_RCC_GPIOG_CLK_DISABLE()

#define SPI4C1_OUTPUT_PIN                 GPIO_PIN_2
#define SPI4C1_OUTPUT_PORT                GPIOG

struct spi_api* spi4_cs1_binding(void);


#endif
