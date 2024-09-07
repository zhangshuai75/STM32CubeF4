/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "standard_driver.h"
#include "api_standard_common.h"
#include "template_driver.h"
#include "api_template_common.h"


static int send_data(struct device *Dev, uint8_t *tx_data, uint16_t length)
{
	struct template_data *D_data = Dev->data;
	const struct template_config *D_config = Dev->config;
	struct device *Binding_device_1 = D_data->Binding_device_1;
	struct device *Binding_device_2 = D_data->Binding_device_2;
	
	binding_1_app(Binding_device_1, D_data->value_data1, D_config->value_this_config_1);
	binding_2_app(Binding_device_2, D_data->value_data1, D_config->value_this_config_1);
	
	return 0;
}

static int get_data(struct device *Dev, uint8_t *rx_data, uint16_t length)
{
	struct template_data *D_data = Dev->data;
	const struct template_config *D_config = Dev->config;
	struct device *Binding_device_1 = D_data->Binding_device_1;
	struct device *Binding_device_2 = D_data->Binding_device_2;
	
	binding_1_app(Binding_device_1, D_data->value_data2, D_config->value_this_config_2);
	binding_2_app(Binding_device_2, D_data->value_data2, D_config->value_this_config_2);
	
	return 0;
}

static const struct template_common_api Template_common_api = {
	.send = send_data,
	.get  = get_data,
};

static struct template_data Template_data;

static const struct template_config Template_config = {
	.value_this_config_1 = 100,
	.value_this_config_2 = 100,
};

static int template_device_init(struct device *Dev)
{
	struct template_data *D_data = Dev->data;
	
	D_data->Binding_device_1 = standard_device_1_binding();
	D_data->Binding_device_1->init();
	
	D_data->Binding_device_2 = standard_device_2_binding();
	D_data->Binding_device_2->init();
	
	printf("TEMPLATE device init\r\n");
	
	return 0;
}

struct device Template = {
	.api    = &Template_common_api,
	.data   = &Template_data,
	.config = &Template_config,
	.init   = template_device_init,
};

struct device* template_device_binding(void)
{
	return &Template;
}
