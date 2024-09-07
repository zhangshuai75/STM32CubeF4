/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "i2c1.h"
#include "api_define.h"


I2C_HandleTypeDef I2cHandle1;

static void _I2C1_MspInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	#ifdef I2C1_DMA
	static DMA_HandleTypeDef DmaHandle_i2c1_tx;
	static DMA_HandleTypeDef DmaHandle_i2c1_rx;
	
	I2C_HandleTypeDef *pI2cHandle1;
	pI2cHandle1 = &I2cHandle1;
	#endif
	
	I2C1_SCL_GPIO_CLK_ENABLE();
	I2C1_SDA_GPIO_CLK_ENABLE();
	
	GPIO_InitStruct.Pin       = I2C1_SCL_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = I2C1_SCL_AF;
	HAL_GPIO_Init(I2C1_SCL_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin       = I2C1_SDA_PIN;
	GPIO_InitStruct.Alternate = I2C1_SDA_AF;
	HAL_GPIO_Init(I2C1_SDA_GPIO_PORT, &GPIO_InitStruct);
	
	I2C1_CLK_ENABLE();
	I2C1_FORCE_RESET();
	I2C1_RELEASE_RESET();
	
	#ifdef I2C1_IT
	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	
	HAL_NVIC_SetPriority(I2C1_ER_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
	
	#ifdef I2C1_DMA
	DMA_I2C1_CLK_ENABLE();
	
	DmaHandle_i2c1_tx.Instance                 = DMA_I2C1_TX_STREAM;
	DmaHandle_i2c1_tx.Init.Channel             = DMA_I2C1_TX_CHANNEL;
	DmaHandle_i2c1_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
	DmaHandle_i2c1_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_i2c1_tx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_i2c1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_i2c1_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_i2c1_tx.Init.Mode                = DMA_NORMAL;
	DmaHandle_i2c1_tx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
	DmaHandle_i2c1_tx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
	DmaHandle_i2c1_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_i2c1_tx.Init.MemBurst            = DMA_MBURST_SINGLE;
	DmaHandle_i2c1_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;
	
	__HAL_LINKDMA(pI2cHandle1, hdmatx, DmaHandle_i2c1_tx);
	HAL_DMA_Init(&DmaHandle_i2c1_tx);
	
	DmaHandle_i2c1_rx.Instance                 = DMA_I2C1_RX_STREAM;
	DmaHandle_i2c1_rx.Init.Channel             = DMA_I2C1_RX_CHANNEL;
	DmaHandle_i2c1_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
	DmaHandle_i2c1_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
	DmaHandle_i2c1_rx.Init.MemInc              = DMA_MINC_ENABLE;
	DmaHandle_i2c1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DmaHandle_i2c1_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
	DmaHandle_i2c1_rx.Init.Mode                = DMA_NORMAL;
	DmaHandle_i2c1_rx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
	DmaHandle_i2c1_rx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
	DmaHandle_i2c1_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
	DmaHandle_i2c1_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
	DmaHandle_i2c1_rx.Init.PeriphBurst         = DMA_PBURST_SINGLE;
	
	__HAL_LINKDMA(pI2cHandle1, hdmarx, DmaHandle_i2c1_rx);
	HAL_DMA_Init(&DmaHandle_i2c1_rx);
	
	HAL_NVIC_SetPriority(DMA_I2C1_TX_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(DMA_I2C1_TX_IRQn);
	
	HAL_NVIC_SetPriority(DMA_I2C1_RX_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(DMA_I2C1_RX_IRQn);
	#endif
	#endif
}

static void i2c1_init(void)
{
	if(HAL_I2C_GetState(&I2cHandle1) == HAL_I2C_STATE_RESET)
	{
		I2cHandle1.Instance             = I2C1;
		I2cHandle1.Init.ClockSpeed      = I2C1_CLOCKSPEED;
		I2cHandle1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
		I2cHandle1.Init.OwnAddress1     = 0;
		I2cHandle1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
		I2cHandle1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		I2cHandle1.Init.OwnAddress2     = 0;
		I2cHandle1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		I2cHandle1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
		
		_I2C1_MspInit();
		HAL_I2C_Init(&I2cHandle1);
		printf("I2C1 HAL init\r\n");
	}
}

static void _I2C1_MspDeInit(void)
{
	HAL_GPIO_DeInit(I2C1_SCL_GPIO_PORT, I2C1_SCL_PIN);
	HAL_GPIO_DeInit(I2C1_SDA_GPIO_PORT, I2C1_SDA_PIN);
	
	HAL_I2C_DeInit(&I2cHandle1);
	
	#ifdef I2C1_IT
	HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
	HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
	
	#ifdef I2C1_DMA
	HAL_DMA_DeInit(I2cHandle1.hdmatx);
	HAL_DMA_DeInit(I2cHandle1.hdmarx);
	
	HAL_NVIC_DisableIRQ(DMA_I2C1_TX_IRQn);
	HAL_NVIC_DisableIRQ(DMA_I2C1_RX_IRQn);
	#endif
	#endif
}

static void i2c1_error(void)
{
	_I2C1_MspDeInit();
	i2c1_init();
}

static int i2c1_master_transmit(uint16_t addr, uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Master_Transmit(&I2cHandle1, (uint16_t)addr<<1 & 0xFFFE, data, length, timeout);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

static int i2c1_master_receive(uint16_t addr, uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Master_Receive(&I2cHandle1, (uint16_t)addr<<1 | 0x0001, data, length, timeout);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

static int i2c1_mem_write(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Write(&I2cHandle1, (uint16_t)addr<<1 & 0xFFFE, reg, I2C1_REG_BIT, data, length, timeout);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

static int i2c1_mem_read(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length, uint32_t timeout)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Read(&I2cHandle1, (uint16_t)addr<<1 | 0x0001, reg, I2C1_REG_BIT, data, length, timeout);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

#ifdef I2C1_IT
static int i2c1_mem_write_it(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Write_IT(&I2cHandle1, (uint16_t)addr<<1 & 0xFFFE, reg, I2C1_REG_BIT, data, length);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

static int i2c1_mem_read_it(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Read_IT(&I2cHandle1, (uint16_t)addr<<1 | 0x0001, reg, I2C1_REG_BIT, data, length);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

#ifdef I2C1_DMA
static int i2c1_mem_write_dma(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Write_DMA(&I2cHandle1, (uint16_t)addr<<1 & 0xFFFE, reg, I2C1_REG_BIT, data, length);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}

static int i2c1_mem_read_dma(uint16_t addr, uint16_t reg, uint8_t *data, uint16_t length)
{
	HAL_StatusTypeDef e_status = HAL_OK;
	e_status = HAL_I2C_Mem_Read_DMA(&I2cHandle1, (uint16_t)addr<<1 | 0x0001, reg, I2C1_REG_BIT, data, length);
	if(e_status != HAL_OK) {
		i2c1_error();
	}
	return e_status;
}
#endif
#endif

static struct i2c_api I2c1_api = {
	.init            = i2c1_init,
	.master_transmit = i2c1_master_transmit,
	.master_receive  = i2c1_master_receive,
	.mem_write       = i2c1_mem_write,
	.mem_read        = i2c1_mem_read,
	#ifdef I2C1_IT
	.mem_write_it    = i2c1_mem_write_it,
	.mem_read_it     = i2c1_mem_read_it,
	#ifdef I2C1_DMA
	.mem_write_dma   = i2c1_mem_write_dma,
	.mem_read_dma    = i2c1_mem_read_dma,
	#endif
	#endif
};

#ifdef I2C1_IT
void I2C1_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&I2cHandle1);
}

void I2C1_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&I2cHandle1);
}

#ifdef I2C1_DMA
void DMA_I2C1_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(I2cHandle1.hdmatx);
}

void DMA_I2C1_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(I2cHandle1.hdmarx);
}
#endif
#endif

struct i2c_api* i2c1_binding(void)
{
	return &I2c1_api; //¶Ç»¼¦ì¸m
}
