/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __UART_STRING_RECEIVE_PARSER_H
#define __UART_STRING_RECEIVE_PARSER_H


typedef struct {
	char value_start[6]; //GPABCD
	char value_o1[1];    //,
	char value_data1[1]; //T
	char value_o2[1];    //,
	char value_data2[2]; //QW
	char value_o3[1];    //,
	char value_data3[3]; //Y22
	char value_o4[1];    //,
	char value_data4[4]; //56tr
	char value_o5[1];    //,
	char value_data5[5]; //S23_E
	char value_o6[1];    //,
	char value_data6[6]; //KK2341
	char value_o7[1];    //,
	char value_end[3];   //Off
	char value_o8[1];    //,
}gps_data_t;
//GPABCD,T,QW,Y22,56tr,S23_E,KK2341,Off

typedef struct {
	char value_start[1];  //0x0A
	char value_cmd[1];    //0x41
	char value_ver1[4];   //R001
	char value_id[16];    //a1b2c3d4e5f6g7h8
	char value_ver2[3];   //A01
	char value_region[5]; //5D1F7
	char value_end[2];    //0x0D 0x0A
}version_data_t;
//0A 41 52 30 30 31 61 31 62 32 63 33 64 34 65 35 66 36 67 37 68 38 41 30 31 35 44 31 46 37 0D 0A
//->.AR001a1b2c3d4e5f6g7h8A015D1F7.

uint16_t head_checkout(struct uart_api *Huart, char *name, uint8_t *buffer, uint16_t length);
gps_data_t* a_parser(uint8_t *buffer);
version_data_t* version_parser(uint8_t *buffer);


#endif
