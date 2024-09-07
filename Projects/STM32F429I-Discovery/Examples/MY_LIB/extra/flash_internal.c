/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#include "stm32f4xx_hal.h"
#include "flash_internal.h"


static uint32_t get_sector(enum flash_sector e_address)
{
	uint32_t sector = 0;
	
	if(e_address == SECTOR_0_16KB_8000000) {
		sector = FLASH_SECTOR_0;
	}else if(e_address == SECTOR_1_16KB_8004000) {
		sector = FLASH_SECTOR_1;
	}else if(e_address == SECTOR_2_16KB_8008000) {
		sector = FLASH_SECTOR_2;
	}else if(e_address == SECTOR_3_16KB_800C000) {
		sector = FLASH_SECTOR_3;
	}else if(e_address == SECTOR_4_64KB_8010000) {
		sector = FLASH_SECTOR_4;
	}else if(e_address == SECTOR_5_128KB_8020000) {
		sector = FLASH_SECTOR_5;
	}else if(e_address == SECTOR_6_128KB_8040000) {
		sector = FLASH_SECTOR_6;
	}else if(e_address == SECTOR_7_128KB_8060000) {
		sector = FLASH_SECTOR_7;
	}else if(e_address == SECTOR_8_128KB_8080000) {
		sector = FLASH_SECTOR_8;
	}else if(e_address == SECTOR_9_128KB_80A0000) {
		sector = FLASH_SECTOR_9;
	}else if(e_address == SECTOR_10_128KB_80C0000) {
		sector = FLASH_SECTOR_10;
	}else if(e_address == SECTOR_11_128KB_80E0000) {
		sector = FLASH_SECTOR_11;
	}else if(e_address == SECTOR_12_16KB_8100000) {
		sector = FLASH_SECTOR_12;
	}else if(e_address == SECTOR_13_16KB_8104000) {
		sector = FLASH_SECTOR_13;
	}else if(e_address == SECTOR_14_16KB_8108000) {
		sector = FLASH_SECTOR_14;
	}else if(e_address == SECTOR_15_16KB_810C000) {
		sector = FLASH_SECTOR_15;
	}else if(e_address == SECTOR_16_64KB_8110000) {
		sector = FLASH_SECTOR_16;
	}else if(e_address == SECTOR_17_128KB_8120000) {
		sector = FLASH_SECTOR_17;
	}else if(e_address == SECTOR_18_128KB_8140000) {
		sector = FLASH_SECTOR_18;
	}else if(e_address == SECTOR_19_128KB_8160000) {
		sector = FLASH_SECTOR_19;
	}else if(e_address == SECTOR_20_128KB_8180000) {
		sector = FLASH_SECTOR_20;
	}else if(e_address == SECTOR_21_128KB_81A0000) {
		sector = FLASH_SECTOR_21;
	}else if(e_address == SECTOR_22_128KB_81C0000) {
		sector = FLASH_SECTOR_22;
	}else {
		sector = FLASH_SECTOR_23;
	}
	
	return sector;
}

int flash_internal_erase(enum flash_sector e_sector)
{
	FLASH_EraseInitTypeDef Erase;
	uint32_t first_sector = get_sector(e_sector);
	uint32_t Nb_of_sectors = get_sector(e_sector);
	uint32_t sector_error = 0;
	uint16_t count;
	HAL_StatusTypeDef e_status;
	
	Erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
	Erase.Banks        = 0;
	Erase.Sector       = first_sector;
	Erase.NbSectors    = Nb_of_sectors - first_sector + 1;
	Erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	
	HAL_FLASH_Unlock();
	for(count = 0; count < 10; count++) {
		e_status = HAL_FLASHEx_Erase(&Erase, &sector_error);
		if(e_status == HAL_OK) {
			break;
		}
	}
	HAL_FLASH_Lock();
	
	if(count >= 10) {
		printf("Flash erase fail!!\r\n");
		return 1;
	}else if(count >= 1) {
		printf("Flash erase %d times to success\r\n", count+1);
	}
	
	return 0;
}

int flash_internal_write(enum flash_type e_type, enum flash_sector e_sector, uint32_t offset, uint64_t data)
{
	uint32_t address = e_sector + offset;
	
	HAL_FLASH_Unlock();
	if(HAL_FLASH_Program(e_type, address, data) != HAL_OK) {
		return 1;
	}
	HAL_FLASH_Lock();
	
	return 0;
}

uint8_t flash_internal_read_byte(enum flash_sector e_sector, uint32_t offset)
{
	uint32_t address = e_sector + offset;
	__IO uint8_t data = *(__IO uint8_t *)address;
	
	return data;
}

uint16_t flash_internal_read_halfword(enum flash_sector e_sector, uint32_t offset)
{
	uint32_t address = e_sector + offset;
	__IO uint16_t data = *(__IO uint16_t *)address;
	
	return data;
}

uint32_t flash_internal_read_word(enum flash_sector e_sector, uint32_t offset)
{
	uint32_t address = e_sector + offset;
	__IO uint32_t data = *(__IO uint32_t *)address;
	
	return data;
}

uint64_t flash_internal_read_doubleword(enum flash_sector e_sector, uint32_t offset)
{
	uint32_t address = e_sector + offset;
	__IO uint64_t data = *(__IO uint64_t *)address;
	
	return data;
}

int flash_data_write(enum flash_sector e_sector, uint32_t offset, uint8_t *data, uint16_t length)
{
	uint16_t i;
	
	for(i = 0; i < length; i++) {
		flash_internal_write(PROGRAM_BYTE, e_sector, offset + i, data[i]);
	}
	
	return 0;
}

int flash_data_read(enum flash_sector e_sector, uint32_t offset, uint8_t *data, uint16_t length)
{
	uint16_t i;
	
	for(i = 0; i < length; i++) {
		data[i] = flash_internal_read_byte(e_sector, offset + i);
	}
	
	return 0;
}
