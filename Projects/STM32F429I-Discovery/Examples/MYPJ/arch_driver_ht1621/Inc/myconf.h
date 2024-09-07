/* Copyright (C) 2018 Rayling <https://github.com/Rayling35>
 * SPDX-License-Identifier: MIT
 */
#ifndef __MYCONF_H
#define __MYCONF_H

#include "gpio_a5.h"
#include "gpio_g2.h"
#include "gpio_g3.h"


#define HT1621_CS_OUTPUT_LOW        A5_OUTPUT_LOW()
#define HT1621_CS_OUTPUT_HIGH       A5_OUTPUT_HIGH()
#define HT1621_WR_OUTPUT_LOW        G3_OUTPUT_LOW()
#define HT1621_WR_OUTPUT_HIGH       G3_OUTPUT_HIGH()
#define HT1621_DATA_OUTPUT_LOW      G2_OUTPUT_LOW()
#define HT1621_DATA_OUTPUT_HIGH     G2_OUTPUT_HIGH()


#endif
