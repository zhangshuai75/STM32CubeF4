/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "gpio_g2.h"
#include "api_define.h"


#ifdef G2_OUTPUT
static void gpio_g2_output_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	PG2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG2_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G2_INPUT
static void gpio_g2_input_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
	HAL_GPIO_Init(PG2_PORT, &GPIO_InitStruct);
}
#endif

#ifdef G2_EXTI
static void gpio_g2_exti_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	PG2_CLK_ENABLE();
	
	GPIO_InitStruct.Pin   = PG2_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull  = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	
	HAL_GPIO_Init(PG2_PORT, &GPIO_InitStruct);
	
	HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
}

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(PG2_PIN);
}
#endif

static void gpio_g2_init(void)
{
	#ifdef G2_OUTPUT
	gpio_g2_output_init();
	#endif
	#ifdef G2_INPUT
	gpio_g2_input_init();
	#endif
	#ifdef G2_EXTI
	gpio_g2_exti_init();
	#endif
	printf("GPIO_G2 HAL init\r\n");
}

static int gpio_g2_read(void)
{
	return HAL_GPIO_ReadPin(PG2_PORT, PG2_PIN);
}

static void gpio_g2_write(uint8_t state)
{
	if(state == 0) {
		HAL_GPIO_WritePin(PG2_PORT, PG2_PIN, GPIO_PIN_RESET);
	}
	if(state == 1) {
		HAL_GPIO_WritePin(PG2_PORT, PG2_PIN, GPIO_PIN_SET);
	}
}

static void gpio_g2_toggle_write(void)
{
	HAL_GPIO_TogglePin(PG2_PORT, PG2_PIN);
}

static int gpio_g2_lock(void)
{
	return HAL_GPIO_LockPin(PG2_PORT, PG2_PIN);
}

static struct gpio_api Gpio_g2_api = {
	.init         = gpio_g2_init,
	.read         = gpio_g2_read,
	.write        = gpio_g2_write,
	.toggle_write = gpio_g2_toggle_write,
	.lock         = gpio_g2_lock,
};

struct gpio_api* gpio_g2_binding(void)
{
	return &Gpio_g2_api;
}
