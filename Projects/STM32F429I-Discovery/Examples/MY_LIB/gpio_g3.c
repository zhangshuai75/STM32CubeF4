/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "gpio_g3.h"
#include "api_define.h"


#ifdef G3_OUTPUT
static void gpio_g3_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PG3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG3_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G3_INPUT
static void gpio_g3_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG3_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G3_EXTI
static void gpio_g3_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG3_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG3_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PG3_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PG3_PIN);
}
#endif

static void gpio_g3_init(void)
{
	#ifdef G3_OUTPUT
	gpio_g3_output_init();
	#endif
	#ifdef G3_INPUT
	gpio_g3_input_init();
	#endif
	#ifdef G3_EXTI
	gpio_g3_exti_init();
	#endif
	printf("GPIO_G3 HAL init\r\n");
}

static int gpio_g3_read(void)
{
	return HAL_GPIO_ReadPin(PG3_PORT, PG3_PIN);
}

static void gpio_g3_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PG3_PORT, PG3_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PG3_PORT, PG3_PIN, GPIO_PIN_SET);
	}
}

static void gpio_g3_toggle_write(void)
{
	HAL_GPIO_TogglePin(PG3_PORT, PG3_PIN);
}

static int gpio_g3_lock(void)
{
	return HAL_GPIO_LockPin(PG3_PORT, PG3_PIN);
}

static struct gpio_api Gpio_g3_api = {
	.init         = gpio_g3_init,
	.read         = gpio_g3_read,
	.write        = gpio_g3_write,
	.toggle_write = gpio_g3_toggle_write,
	.lock         = gpio_g3_lock,
};

struct gpio_api* gpio_g3_binding(void)
{
	return &Gpio_g3_api;
}
