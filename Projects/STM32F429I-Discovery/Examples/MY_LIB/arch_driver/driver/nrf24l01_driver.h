/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __NRF24L01_DRIVER_H
#define __NRF24L01_DRIVER_H


struct nrf24l01_data {
	struct device *Spi;
	struct device *Gpio;
	uint8_t value_rx_data[5];
};

struct nrf24l01_config {
	uint8_t value_tx_config[5];
};

//commands
#define NRF24L01_READ_REG          0x00     //read register
#define NRF24L01_WRITE_REG         0x20     //write register
#define NRF24L01_RD_RX_PLOAD       0x61     //RX payload
#define NRF24L01_WR_TX_PLOAD       0xA0     //TX payload
#define NRF24L01_FLUSH_TX          0xE1     //flush TX
#define NRF24L01_FLUSH_RX          0xE2     //flush RX
#define NRF24L01_REUSE_TX_PL       0xE3     //reuse TX payload
#define NRF24L01_NOP               0xFF     //No Operation, might be used to read status register

//registers(addresses)
#define NRF24L01_CONFIG            0x00     //'Config'
#define NRF24L01_EN_AA             0x01     //'Enable Auto Acknowledgment'
#define NRF24L01_EN_RXADDR         0x02     //'Enabled RX addresses'
#define NRF24L01_SETUP_AW          0x03     //'Setup address width'
#define NRF24L01_SETUP_RETR        0x04     //'Setup Auto. Retrans'
#define NRF24L01_RF_CH             0x05     //'RF channel'
#define NRF24L01_RF_SETUP          0x06     //'RF setup'
#define NRF24L01_STATUS            0x07     //'Status'
#define NRF24L01_OBSERVE_TX        0x08     //'Observe TX'
#define NRF24L01_CD                0x09     //'Carrier Detect'
#define NRF24L01_RX_ADDR_P0        0x0A     //'RX address pipe0'
#define NRF24L01_RX_ADDR_P1        0x0B     //'RX address pipe1'
#define NRF24L01_RX_ADDR_P2        0x0C     //'RX address pipe2'
#define NRF24L01_RX_ADDR_P3        0x0D     //'RX address pipe3'
#define NRF24L01_RX_ADDR_P4        0x0E     //'RX address pipe4'
#define NRF24L01_RX_ADDR_P5        0x0F     //'RX address pipe5'
#define NRF24L01_TX_ADDR           0x10     //'TX address'
#define NRF24L01_RX_PW_P0          0x11     //'RX payload width, pipe0'
#define NRF24L01_RX_PW_P1          0x12     //'RX payload width, pipe1'
#define NRF24L01_RX_PW_P2          0x13     //'RX payload width, pipe2'
#define NRF24L01_RX_PW_P3          0x14     //'RX payload width, pipe3'
#define NRF24L01_RX_PW_P4          0x15     //'RX payload width, pipe4'
#define NRF24L01_RX_PW_P5          0x16     //'RX payload width, pipe5'
#define NRF24L01_FIFO_STATUS       0x17     //'FIFO Status Register'

struct device* nrf24l01_device_binding(void);


#endif
