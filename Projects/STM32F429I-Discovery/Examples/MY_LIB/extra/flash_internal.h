/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __FLASH_INTERNAL_H
#define __FLASH_INTERNAL_H


enum flash_type {
	PROGRAM_BYTE       = 0x00000000U,
	PROGRAM_HALFWORD   = 0x00000001U,
	PROGRAM_WORD       = 0x00000002U,
	PROGRAM_DOUBLEWORD = 0x00000003U,
};

enum flash_sector {
	SECTOR_0_16KB_8000000   = 0x08000000, //Bank 1
	SECTOR_1_16KB_8004000   = 0x08004000, /* Start @ of user Flash area */
	SECTOR_2_16KB_8008000   = 0x08008000,
	SECTOR_3_16KB_800C000   = 0x0800C000,
	SECTOR_4_64KB_8010000   = 0x08010000,
	SECTOR_5_128KB_8020000  = 0x08020000,
	SECTOR_6_128KB_8040000  = 0x08040000,
	SECTOR_7_128KB_8060000  = 0x08060000,
	SECTOR_8_128KB_8080000  = 0x08080000,
	SECTOR_9_128KB_80A0000  = 0x080A0000,
	SECTOR_10_128KB_80C0000 = 0x080C0000,
	SECTOR_11_128KB_80E0000 = 0x080E0000,
	
	SECTOR_12_16KB_8100000  = 0x08100000, //Bank 2
	SECTOR_13_16KB_8104000  = 0x08104000,
	SECTOR_14_16KB_8108000  = 0x08108000,
	SECTOR_15_16KB_810C000  = 0x0810C000,
	SECTOR_16_64KB_8110000  = 0x08110000,
	SECTOR_17_128KB_8120000 = 0x08120000,
	SECTOR_18_128KB_8140000 = 0x08140000,
	SECTOR_19_128KB_8160000 = 0x08160000,
	SECTOR_20_128KB_8180000 = 0x08180000,
	SECTOR_21_128KB_81A0000 = 0x081A0000,
	SECTOR_22_128KB_81C0000 = 0x081C0000,
	SECTOR_23_128KB_81E0000 = 0x081E0000, /* End @ of user Flash area */
};

int flash_internal_erase(enum flash_sector e_sector);
int flash_internal_write(enum flash_type e_type, enum flash_sector e_sector, uint32_t offset, uint64_t data);
uint8_t flash_internal_read_byte(enum flash_sector e_sector, uint32_t offset);
uint16_t flash_internal_read_halfword(enum flash_sector e_sector, uint32_t offset);
uint32_t flash_internal_read_word(enum flash_sector e_sector, uint32_t offset);
uint64_t flash_internal_read_doubleword(enum flash_sector e_sector, uint32_t offset);
int flash_data_write(enum flash_sector e_sector, uint32_t offset, uint8_t *data, uint16_t length);
int flash_data_read(enum flash_sector e_sector, uint32_t offset, uint8_t *data, uint16_t length);


#endif
