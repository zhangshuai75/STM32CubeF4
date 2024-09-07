/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __GPIO_G2_H
#define __GPIO_G2_H


#define PG2_CLK_ENABLE()          __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG2_CLK_DISABLE()         __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG2_PIN                   GPIO_PIN_2
#define PG2_PORT                  GPIOG

#ifdef G2_OUTPUT
#define G2_OUTPUT_LOW()       HAL_GPIO_WritePin(PG2_PORT, PG2_PIN, GPIO_PIN_RESET)
#define G2_OUTPUT_HIGH()      HAL_GPIO_WritePin(PG2_PORT, PG2_PIN, GPIO_PIN_SET)
#endif

struct gpio_api* gpio_g2_binding(void);


#endif
