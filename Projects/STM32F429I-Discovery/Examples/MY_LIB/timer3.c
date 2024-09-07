/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "timer3.h"
#include "api_define.h"


TIM_HandleTypeDef TimHandle3;

static void _TIMER3_MspInit(void)
{
	TIM3_CLK_ENABLE();
	
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

static void timer3_init(void)
{
	_TIMER3_MspInit();
	printf("TIMER3 HAL init\r\n");
}

static int timer3_start_it(uint32_t period_cycles, uint32_t prescaler)
{
	TimHandle3.Instance           = TIM3;
	TimHandle3.Init.Prescaler     = prescaler;
	TimHandle3.Init.CounterMode   = TIM_COUNTERMODE_UP;
	TimHandle3.Init.Period        = period_cycles;
	TimHandle3.Init.ClockDivision = 0;
	HAL_TIM_Base_Init(&TimHandle3);
	
	return HAL_TIM_Base_Start_IT(&TimHandle3);
}

static int timer3_stop_it(void)
{
	return HAL_TIM_Base_Stop_IT(&TimHandle3);
}

static struct timer_api Timer3_api = {
	.init           = timer3_init,
	.timer_start_it = timer3_start_it,
	.timer_stop_it  = timer3_stop_it,
};

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle3);
}

struct timer_api* timer3_binding(void)
{
	return &Timer3_api;
}
