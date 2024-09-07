/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "gpio_driver.h"
#include "api_gpio_common.h"
#include "led_driver.h"
#include "api_led_common.h"


static int light_on_off(struct device *Dev, enum led_state e_state)
{
	struct led_data *D_data = Dev->data;
	
	gpio_write(D_data->Gpio, e_state);
	return 0;
}

static const struct led_common_api Led_common_api = {
	.normal_light = light_on_off,
};

static struct led_data Led_data;

static int led_device_init(struct device *Dev)
{
	struct led_data *D_data = Dev->data;
	
	D_data->Gpio = gpio_g13_device_binding();
	gpio_init(D_data->Gpio);
	printf("LED device init\r\n");
	
	return 0;
}

struct device Led = {
	.api  = &Led_common_api,
	.data = &Led_data,
	.init = led_device_init,
};

struct device* led_device_binding(void)
{
	return &Led;
}
