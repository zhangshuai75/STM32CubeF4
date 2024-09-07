/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "pwm3_1.h"
#include "api_define.h"


TIM_HandleTypeDef TimHandle3_1;

static void _PWM3_1_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	TIM3_CHANNEL1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = TIM3_CHANNEL1_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = TIM3_CHANNEL1_AF;
	HAL_GPIO_Init(TIM3_CHANNEL1_PORT, &GPIO_InitStruct);
	
	TIM3_CLK_ENABLE();
}

static void pwm3_1_init(void)
{
	_PWM3_1_MspInit();
	printf("PWM3_1 HAL init\r\n");
}

static int pwm3_1_pin_set(uint32_t period_cycles, uint32_t pulse_cycles, uint32_t prescaler)
{
	TIM_OC_InitTypeDef sConfig;
	
	TimHandle3_1.Instance               = TIM3;
	TimHandle3_1.Init.Prescaler         = prescaler;
	TimHandle3_1.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle3_1.Init.Period            = period_cycles;
	TimHandle3_1.Init.ClockDivision     = 0;
	TimHandle3_1.Init.RepetitionCounter = 0;
	HAL_TIM_PWM_Init(&TimHandle3_1);
	
	sConfig.OCMode       = TIM_OCMODE_PWM1;
	sConfig.Pulse        = pulse_cycles;
	sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(&TimHandle3_1, &sConfig, TIM3_CHANNEL1);
	
	return HAL_TIM_PWM_Start(&TimHandle3_1, TIM3_CHANNEL1);
}

static struct pwm_api Pwm3_1_api = {
	.init    = pwm3_1_init,
	.pin_set = pwm3_1_pin_set,
};

struct pwm_api* pwm3_1_binding(void)
{
	return &Pwm3_1_api;
}
