/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "i2c_driver.h"
#include "api_i2c_common.h"
#include "main.h"


#define BME280_ADDRESS           0x76
#define BME280_CHIPID            0xD0

#define STMPE811_ADDRESS         0x41
#define STMPE811_REG_CHP_ID_LSB  0x00
#define STMPE811_REG_CHP_ID_MSB  0x01

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *I2c1 = i2c1_device_binding();
	struct device *I2c3 = i2c3_device_binding();
	i2c_init(I2c1);
	i2c_init(I2c3);
	printf("I2C device init\r\n");
	
	int status;
	uint8_t value_bme280 = 0;
	uint8_t value_lsb = 0;
	uint8_t value_msb = 0;
	
	while(1) {
		status = i2c_mem_read(I2c3, BME280_ADDRESS, BME280_CHIPID, &value_bme280, 1);
		if(status != HAL_OK) {
			printf("BME280 mem_read fail! %d\r\n", status);
		}
		printf("BME280_0x60 == %X\r\n", value_bme280);
		
		
		status = i2c_mem_read(I2c3, STMPE811_ADDRESS, STMPE811_REG_CHP_ID_LSB, &value_lsb, 1);
		if(status != HAL_OK) {
			printf("STMPE811_LSB mem_read fail! %d\r\n", status);
		}
		
		status = i2c_mem_read(I2c3, STMPE811_ADDRESS, STMPE811_REG_CHP_ID_MSB, &value_msb, 1);
		if(status != HAL_OK) {
			printf("STMPE811_MSB mem_read fail! %d\r\n", status);
		}
		printf("STMPE811_0x0811 == %X\r\n", (value_lsb << 8) | value_msb);
		
		
		printf("\r\n");
		HAL_Delay(2000);
	}
}
