/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "system_initialization.h"
#include "uart_printf.h"
#include "stm32f4xx_hal.h"
#include "device.h"
#include "spi_driver.h"
#include "api_spi_common.h"
#include "main.h"


int sample_register_write(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t tx_data[length+1];
	uint8_t dummy;
	uint16_t i;
	
	tx_data[0] = reg;
	for(i = 1; i <= length; i++) {
		tx_data[i] = *data;
		data++;
	}
	return spi_transmit_receive(Spi, tx_data, &dummy, length+1);
}

int sample_register_read(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	int status;
	uint8_t rx_data[length+1];
	uint16_t i;
	
	status = spi_transmit_receive(Spi, &reg, rx_data, length+1);
	for(i = 0; i < length; i++) {
		data[i] = rx_data[i+1];
	}
	return status;
}

int max31855_register_read(struct device *Spi, uint32_t *data, uint16_t length)
{
	return spi_receive32(Spi, data, length);
}

int adxl362_register_write(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	//uint8_t write = 0x0A;
	return 0;
}

int adxl362_register_read(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	uint8_t tx_data[2] = {0x0B, reg};
	int status;
	uint8_t rx_data[length+2];
	uint16_t i;
	
	status = spi_transmit_receive(Spi, tx_data, rx_data, length+2);
	for(i = 0; i < length; i++) {
		data[i] = rx_data[i+2];
	}
	return status;
}

int adxl362_register_read_fifo(struct device *Spi, uint8_t reg, uint8_t *data, uint16_t length)
{
	//uint8_t read_fifo = 0x0D;
	return 0;
}

#define BME280 //SPI_POLARITY_LOW,SPI_PHASE_1EDGE
#define BME280_REG_ID               0xD0

#define L3GD20 //SPI_POLARITY_LOW,SPI_PHASE_1EDGE
#define L3GD20_R                    0x80
#define L3GD20_W                    0x00
#define L3GD20_MS                   0x00
#define L3GD20_WHO_AM_I_ADDR        0x0F
#define L3GD20_CTRL_REG1            0x20

//#define NRF24L01 //SPI_POLARITY_LOW,SPI_PHASE_1EDGE
#define NRF24L01_R                  0x00
#define NRF24L01_W                  0x20
#define NRF24L01_TX_ADDR            0x10

//#define MAX31855 //SPI_POLARITY_LOW,SPI_PHASE_1EDGE

//#define ADXL362 //SPI_POLARITY_LOW,SPI_PHASE_1EDGE
#define ADXL362_DEVID_AD            0x00
#define ADXL362_DEVID_MST           0x01
#define ADXL362_PARTID              0x02

#define RN8209G //SPI_POLARITY_LOW,SPI_PHASE_2EDGE
#define RN8209G_R                   0x00
#define RN8209G_W                   0x80
#define RN8209G_DEVICEID            0x7F

int main(void)
{
	system_initialization();
	uart_printf_init();
	
	struct device *Spi4_cs1 = spi4_cs1_device_binding();
	struct device *Spi5_cs1 = spi5_cs1_device_binding();
	spi_init(Spi4_cs1);
	spi_init(Spi5_cs1);
	printf("SPI device init\r\n");
	
	#ifdef BME280
	uint8_t bme280_rx;
	#endif
	#ifdef L3GD20
	uint8_t l3gd20_tx = 0x09;
	uint8_t l3gd20_rx;
	#endif
	#ifdef NRF24L01
	uint8_t nrf24l01_tx[5] = {0xA5,0xA5,0xA5,0xA5,0xA5};
	uint8_t nrf24l01_tx1[5] = {0xE8,0xE8,0xE8,0xE8,0xE8};
	uint8_t nrf24l01_rx[5];
	#endif
	#ifdef MAX31855
	uint32_t max31855_rx;
	#endif
	#ifdef ADXL362
	uint8_t adxl362_rx;
	#endif
	#ifdef RN8209G
	uint8_t rn8209g_rx[3];
	#endif
	
	while(1) {
		#ifdef BME280
		sample_register_read(Spi4_cs1, BME280_REG_ID, &bme280_rx, 1);
		printf("BME280_0x60 = %X\r\n", bme280_rx);
		#endif
		
		#ifdef L3GD20
		sample_register_read(Spi5_cs1, L3GD20_WHO_AM_I_ADDR | L3GD20_R | L3GD20_MS, &l3gd20_rx, 1);
		printf("L3GD20_0xD4 = %X\r\n", l3gd20_rx);
		
		sample_register_write(Spi5_cs1, L3GD20_CTRL_REG1 | L3GD20_W | L3GD20_MS, &l3gd20_tx, 1);
		sample_register_read(Spi5_cs1, L3GD20_CTRL_REG1 | L3GD20_R | L3GD20_MS, &l3gd20_rx, 1);
		printf("CTRL_REG1 = %X\r\n", l3gd20_rx);
		#endif
		
		#ifdef NRF24L01
		sample_register_read(Spi4_cs1, NRF24L01_TX_ADDR | NRF24L01_R, nrf24l01_rx, 5);
		printf("NRF24L01 = %X %X %X %X %X\r\n", nrf24l01_rx[0],nrf24l01_rx[1],nrf24l01_rx[2],
		                                                       nrf24l01_rx[3],nrf24l01_rx[4]);
		sample_register_write(Spi4_cs1, NRF24L01_TX_ADDR | NRF24L01_W, nrf24l01_tx, 5);
		
		sample_register_read(Spi4_cs1, NRF24L01_TX_ADDR | NRF24L01_R, nrf24l01_rx, 5);
		printf("NRF24L01 = %X %X %X %X %X\r\n", nrf24l01_rx[0],nrf24l01_rx[1],nrf24l01_rx[2],
		                                                       nrf24l01_rx[3],nrf24l01_rx[4]);
		sample_register_write(Spi4_cs1, NRF24L01_TX_ADDR | NRF24L01_W, nrf24l01_tx1, 5);
		#endif
		
		#ifdef MAX31855
		max31855_register_read(Spi4_cs1, &max31855_rx, 1);
		printf("MAX31855 = %X\r\n", max31855_rx);
		#endif
		
		#ifdef ADXL362
		adxl362_register_read(Spi4_cs1, ADXL362_DEVID_AD, &adxl362_rx, 1);
		printf("ADXL362_0xAD = %X\r\n", adxl362_rx);
		adxl362_register_read(Spi4_cs1, ADXL362_DEVID_MST, &adxl362_rx, 1);
		printf("ADXL362_0x1D = %X\r\n", adxl362_rx);
		adxl362_register_read(Spi4_cs1, ADXL362_PARTID, &adxl362_rx, 1);
		printf("ADXL362_0xF2 = %X\r\n", adxl362_rx);
		#endif
		
		#ifdef RN8209G
		sample_register_read(Spi4_cs1, RN8209G_DEVICEID | RN8209G_R, rn8209g_rx, 3);
		printf("RN8209G_0x820900 = %02X%02X%02X\r\n", rn8209g_rx[0],rn8209g_rx[1],rn8209g_rx[2]);
		#endif
		
		
		printf("\r\n");
		HAL_Delay(2000);
	}
}
