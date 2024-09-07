/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __PWM3_1_H
#define __PWM3_1_H


#define TIM3_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()
#define TIM3_CHANNEL1_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()

#define TIM3_CHANNEL1_PIN              GPIO_PIN_4
#define TIM3_CHANNEL1_PORT             GPIOB
#define TIM3_CHANNEL1_AF               GPIO_AF2_TIM3

#define TIM3_CHANNEL1                  TIM_CHANNEL_1

struct pwm_api* pwm3_1_binding(void);


#endif
