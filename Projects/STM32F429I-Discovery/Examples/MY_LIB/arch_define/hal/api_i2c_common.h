/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __API_I2C_COMMON_H
#define __API_I2C_COMMON_H


               /*-----------API--------------*/
typedef int (*i2c_api_1)(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);
typedef int (*i2c_api_2)(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length);

struct i2c_common_api {
	i2c_api_1 mem_write;
	i2c_api_2 mem_read;
};


               /*-----------APP--------------*/
static inline int i2c_init(struct device *Dev)
{
	return Dev->init(Dev);
}

static inline int i2c_mem_write(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	const struct i2c_common_api *D_api = Dev->api;
	return D_api->mem_write(Dev, addr, reg, data, length);
}

static inline int i2c_mem_read(struct device *Dev, uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	const struct i2c_common_api *D_api = Dev->api;
	return D_api->mem_read(Dev, addr, reg, data, length);
}


#endif
