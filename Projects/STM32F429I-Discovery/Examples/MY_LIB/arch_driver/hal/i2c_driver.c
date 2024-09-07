/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "device.h"
#include "api_define.h"
#include "i2c_driver.h"
#include "api_i2c_common.h"


static int mem_write_data(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	struct i2c_data *D_data = Dev->data;
	const struct i2c_config *D_config = Dev->config;
	struct i2c_api *I2c_hal = D_data->I2c_hal;
	
	return I2c_hal->mem_write(addr, reg, data, length, D_config->value_write_timeout);
}

static int mem_read_data(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	struct i2c_data *D_data = Dev->data;
	const struct i2c_config *D_config = Dev->config;
	struct i2c_api *I2c_hal = D_data->I2c_hal;
	
	return I2c_hal->mem_read(addr, reg, data, length, D_config->value_read_timeout);
}

static const struct i2c_common_api I2c_common_api = {
	.mem_write = mem_write_data,
	.mem_read  = mem_read_data,
};


#ifdef I2C1_DEV
#include "i2c1.h"
static struct i2c_data I2c1_data;

static const struct i2c_config I2c1_config = {
	.value_write_timeout = 1,
	.value_read_timeout  = 1,
};

static int i2c1_device_init(struct device *Dev)
{
	struct i2c_data *D_data = Dev->data;
	
	D_data->I2c_hal = i2c1_binding();
	D_data->I2c_hal->init();
	printf("I2C1 device init\r\n");
	
	return 0;
}

struct device I2c_1 = {
	.api    = &I2c_common_api,
	.data   = &I2c1_data,
	.config = &I2c1_config,
	.init   = i2c1_device_init,
};

struct device* i2c1_device_binding(void)
{
	return &I2c_1;
}
#endif


#ifdef I2C3_DEV
#include "i2c3.h"
static struct i2c_data I2c3_data;

static const struct i2c_config I2c3_config = {
	.value_write_timeout = 1,
	.value_read_timeout  = 1,
};

static int i2c3_device_init(struct device *Dev)
{
	struct i2c_data *D_data = Dev->data;
	
	D_data->I2c_hal = i2c3_binding();
	D_data->I2c_hal->init();
	printf("I2C3 device init\r\n");
	
	return 0;
}

struct device I2c_3 = {
	.api    = &I2c_common_api,
	.data   = &I2c3_data,
	.config = &I2c3_config,
	.init   = i2c3_device_init,
};

struct device* i2c3_device_binding(void)
{
	return &I2c_3;
}
#endif
