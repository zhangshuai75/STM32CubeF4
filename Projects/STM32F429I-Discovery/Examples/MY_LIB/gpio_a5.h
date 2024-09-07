/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_A5_H
#define __GPIO_A5_H


#define PA5_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA5_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA5_PIN                   GPIO_PIN_5
#define PA5_PORT                  GPIOA

#ifdef A5_OUTPUT
#define A5_OUTPUT_LOW()       HAL_GPIO_WritePin(PA5_PORT, PA5_PIN, GPIO_PIN_RESET)
#define A5_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA5_PORT, PA5_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_a5_binding(void);


#endif
