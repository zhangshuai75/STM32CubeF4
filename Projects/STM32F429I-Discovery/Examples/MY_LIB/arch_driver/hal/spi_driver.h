/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


struct spi_data {
	struct spi_api *Spi_cs_hal;
};

struct spi_config {
	uint8_t value_tx_timeout;
	uint8_t value_rx_timeout;
	uint8_t value_tx_rx_timeout;
};

#ifdef SPI4_CS1_DEV
struct device* spi4_cs1_device_binding(void);
#endif

#ifdef SPI5_CS1_DEV
struct device* spi5_cs1_device_binding(void);
#endif


#endif
