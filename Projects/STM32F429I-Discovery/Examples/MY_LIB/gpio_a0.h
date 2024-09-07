/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_A0_H
#define __GPIO_A0_H


#define PA0_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
#define PA0_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define PA0_PIN                   GPIO_PIN_0
#define PA0_PORT                  GPIOA

#ifdef A0_OUTPUT
#define A0_OUTPUT_LOW()       HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_RESET)
#define A0_OUTPUT_HIGH()      HAL_GPIO_WritePin(PA0_PORT, PA0_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_a0_binding(void);


#endif
