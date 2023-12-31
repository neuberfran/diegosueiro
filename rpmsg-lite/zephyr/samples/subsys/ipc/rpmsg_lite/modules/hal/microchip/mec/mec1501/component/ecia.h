/**
 *
 * Copyright (c) 2019 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

/** @file mec1501_ecia.h
 *MEC1501 EC Interrupt Aggregator Subsystem definitions
 */
/** @defgroup MEC1501 Peripherals ECIA
 */

#ifndef _ECIA_H
#define _ECIA_H

#include <stdint.h>
#include <stddef.h>

#include "regaccess.h"

#define MCHP_ECIA_ADDR	0x4000e000u
#define MCHP_FIRST_GIRQ	8u
#define MCHP_LAST_GIRQ	26u

#define MCHP_ECIA_GIRQ_NO_NVIC	 22u

#define MCHP_ECIA_AGGR_BITMAP	(BIT(8) | BIT(9) | BIT(10) | BIT(11) |\
		BIT(12) | BIT(24) | BIT(25) | BIT(26))

#define MCHP_ECIA_DIRECT_BITMAP	(BIT(13) | BIT(14) | BIT(15) | BIT(16) |\
		BIT(17) | BIT(18) | BIT(19) | BIT(20) | BIT(21) | BIT(23))

/*
 * ARM Cortex-M4 NVIC registers
 * External sources are grouped by 32-bit registers.
 * MEC15xx has 173 external sources requiring 6 32-bit registers.
  */
#define MCHP_NUM_NVIC_REGS	6u
#define MCHP_NVIC_SET_EN_BASE	0xe000e100u
#define MCHP_NVIC_CLR_EN_BASE	0xe000e180u
#define MCHP_NVIC_SET_PEND_BASE	0xe000e200u
#define MCHP_NVIC_CLR_PEND_BASE	0xe000e280u
#define MCHP_NVIC_ACTIVE_BASE	0xe000e800u
#define MCHP_NVIC_PRI_BASE	0xe000e400u

/* 0 <= n < MCHP_NUM_NVIC_REGS */
#define MCHP_NVIC_SET_EN(n) \
	REG32(MCHP_NVIC_SET_EN_BASE + ((uintptr_t)(n) * 4u))

#define MCHP_NVIC_CLR_EN(n) \
	REG32(MCHP_NVIC_CLR_EN_BASE + ((uintptr_t)(n) * 4u))

#define MCHP_NVIC_SET_PEND(n) \
	REG32(MCHP_NVIC_SET_PEND_BASE + ((uintptr_t)(n) * 4u))

#define MCHP_NVIC_CLR_PEND(n) \
	REG32(MCHP_NVIC_CLR_PEND_BASE + ((uintptr_t)(n) * 4u))

/*
 * ECIA registers
 * Implements 19 GIRQ's. GIRQ's aggregated interrupts source into one
 * set of registers.
 * For historical reason GIRQ's are numbered starting at 8 in the documentation.
 * This numbering only affects the ECIA BLOCK_EN_SET, BLOCK_EN_CLR, and
 * BLOCK_ACTIVE registers: GIRQ8 is bit[8], ..., GIRQ26 is bit[26].
 *
 * Each GIRQ is composed of 5 32-bit registers.
 * +00h = GIRQ08 Source containing RW/1C status bits
 * +04h = Enable Set write 1 to bit(s) to enable the corresponding source(s)
 * +08h = Read-Only Result = Source AND Enable-Set
 * +0Ch = Enable Clear write 1 to bit(s) to disable the corresponding source(s)
 * +14h = Reserved(unused).
 * +18h = GIRQ09 Source
 * ...
 * There are three other registers at offset 0x200, 0x204, and 0x208
 * 0x200: BLOCK_EN_SET bit == 1 allows bit-wise OR of all GIRQn source
 *	bits to be connected to NVIC GIRQn input.
 *	bit[8]=GIRQ8, bit[9]=GIRQ9, ..., bit[26]=GIRQ26
 * 0x204: BLOCK_EN_CLR bit == 1 disconnects bit-wise OR of GIRQn source
 *	bits from NVIC GIRQn input.
 * 0x208: BLOCK_ACTIVE (read-only)
 *	bit[8]=GIRQ8 has at least one source bit enabled and active.
 *	...
 *	bit[26]=GIRQ26 has at least one source bit enabled and active.
 *
 */

/* zero based logical numbering */
#define MCHP_GIRQ08_ZID		0u
#define MCHP_GIRQ09_ZID		1u
#define MCHP_GIRQ10_ZID		2u
#define MCHP_GIRQ11_ZID		3u
#define MCHP_GIRQ12_ZID		4u
#define MCHP_GIRQ13_ZID		5u
#define MCHP_GIRQ14_ZID		6u
#define MCHP_GIRQ15_ZID		7u
#define MCHP_GIRQ16_ZID		8u
#define MCHP_GIRQ17_ZID		9u
#define MCHP_GIRQ18_ZID		10u
#define MCHP_GIRQ19_ZID		11u
#define MCHP_GIRQ20_ZID		12u /* Nothing in datasheet */
#define MCHP_GIRQ21_ZID		13u

#define MCHP_GIRQ23_ZID		14u /* Adjust per datasheet */
#define MCHP_GIRQ24_ZID		15u
#define MCHP_GIRQ25_ZID		16u
#define MCHP_GIRQ26_ZID		17u
#define MCHP_GIRQ_ZID_MAX	18u

#define MCHP_ECIA_BLK_ENSET_OFS		0x200u
#define MCHP_ECIA_BLK_ENCLR_OFS		0x204u
#define MCHP_ECIA_BLK_ACTIVE_OFS	0x208u

#define MCHP_GIRQ_BLK_ENSET_ADDR \
	(MCHP_ECIA_ADDR + MCHP_ECIA_BLK_ENSET_OFS)

#define MCHP_GIRQ_BLK_ENCLR_ADDR \
	(MCHP_ECIA_ADDR + MCHP_ECIA_BLK_ENCLR_OFS)

#define MCHP_GIRQ_BLK_ACTIVE_ADDR \
	(MCHP_ECIA_ADDR + MCHP_ECIA_BLK_ACTIVE_OFS)

/* 8 <= n <= 26 */
#define MCHP_GIRQ_TO_AGGR_NVIC(n) (((n) < 23) ? ((n)-8) : ((n)-9))

/* 8 <= n <= 26 */
#define MCHP_GIRQ_SRC_ADDR(n) \
	((MCHP_ECIA_ADDR + 0x00u) + (((uint32_t)(n) - 8u) * 0x14u))

#define MCHP_GIRQ_ENSET_ADDR(n) \
	((MCHP_ECIA_ADDR + 0x04u) + (((uint32_t)(n) - 8u) * 0x14u))

#define MCHP_GIRQ_RESULT_ADDR(n) \
	((MCHP_ECIA_ADDR + 0x08u) + (((uint32_t)(n) - 8u) * 0x14u))

#define MCHP_GIRQ_ENCLR_ADDR(n) \
	((MCHP_ECIA_ADDR + 0x0cu) + (((uint32_t)(n) - 8u) * 0x14u))

#define MCHP_GIRQ08_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(8)
#define MCHP_GIRQ08_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(8)
#define MCHP_GIRQ08_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(8)
#define MCHP_GIRQ08_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(8)

#define MCHP_GIRQ09_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(9)
#define MCHP_GIRQ09_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(9)
#define MCHP_GIRQ09_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(9)
#define MCHP_GIRQ09_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(9)

#define MCHP_GIRQ10_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(10)
#define MCHP_GIRQ10_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(10)
#define MCHP_GIRQ10_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(10)
#define MCHP_GIRQ10_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(10)

#define MCHP_GIRQ11_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(11)
#define MCHP_GIRQ11_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(11)
#define MCHP_GIRQ11_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(11)
#define MCHP_GIRQ11_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(11)

#define MCHP_GIRQ12_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(12)
#define MCHP_GIRQ12_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(12)
#define MCHP_GIRQ12_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(12)
#define MCHP_GIRQ12_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(12)

#define MCHP_GIRQ13_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(13)
#define MCHP_GIRQ13_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(13)
#define MCHP_GIRQ13_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(13)
#define MCHP_GIRQ13_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(13)

#define MCHP_GIRQ14_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(14)
#define MCHP_GIRQ14_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(14)
#define MCHP_GIRQ14_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(14)
#define MCHP_GIRQ14_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(14)

#define MCHP_GIRQ15_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(15)
#define MCHP_GIRQ15_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(15)
#define MCHP_GIRQ15_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(15)
#define MCHP_GIRQ15_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(15)

#define MCHP_GIRQ16_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(16)
#define MCHP_GIRQ16_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(16)
#define MCHP_GIRQ16_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(16)
#define MCHP_GIRQ16_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(16)

#define MCHP_GIRQ17_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(17)
#define MCHP_GIRQ17_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(17)
#define MCHP_GIRQ17_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(17)
#define MCHP_GIRQ17_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(17)

#define MCHP_GIRQ18_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(18)
#define MCHP_GIRQ18_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(18)
#define MCHP_GIRQ18_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(18)
#define MCHP_GIRQ18_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(18)

#define MCHP_GIRQ19_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(19)
#define MCHP_GIRQ19_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(19)
#define MCHP_GIRQ19_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(19)
#define MCHP_GIRQ19_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(19)

#define MCHP_GIRQ20_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(20)
#define MCHP_GIRQ20_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(20)
#define MCHP_GIRQ20_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(20)
#define MCHP_GIRQ20_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(20)

#define MCHP_GIRQ21_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(21)
#define MCHP_GIRQ21_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(21)
#define MCHP_GIRQ21_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(21)
#define MCHP_GIRQ21_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(21)

#define MCHP_GIRQ22_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(22)
#define MCHP_GIRQ22_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(22)
#define MCHP_GIRQ22_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(22)
#define MCHP_GIRQ22_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(22)

#define MCHP_GIRQ23_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(23)
#define MCHP_GIRQ23_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(23)
#define MCHP_GIRQ23_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(23)
#define MCHP_GIRQ23_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(23)

#define MCHP_GIRQ24_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(24)
#define MCHP_GIRQ24_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(24)
#define MCHP_GIRQ24_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(24)
#define MCHP_GIRQ24_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(24)

#define MCHP_GIRQ25_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(25)
#define MCHP_GIRQ25_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(25)
#define MCHP_GIRQ25_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(25)
#define MCHP_GIRQ25_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(25)

#define MCHP_GIRQ26_SRC_ADDR	MCHP_GIRQ_SRC_ADDR(26)
#define MCHP_GIRQ26_ENSET_ADDR	MCHP_GIRQ_ENSET_ADDR(26)
#define MCHP_GIRQ26_RESULT_ADDR	MCHP_GIRQ_RESULT_ADDR(26)
#define MCHP_GIRQ26_ENCLR_ADDR	MCHP_GIRQ_ENCLR_ADDR(26)

/*
 * Register access
 */
#define MCHP_GIRQ_BLK_ENSET() \
	REG32(MCHP_GIRQ_BLK_ENSET_ADDR)

#define MCHP_GIRQ_BLK_ENCLR() \
	REG32(MCHP_GIRQ_BLK_ENCLR_ADDR)

#define MCHP_GIRQ_BLK_ACTIVE() \
	REG32(MCHP_GIRQ_BLK_ACTIVE_ADDR)

/*
 * Set/clear GIRQ Block Enable
 * Check if block is active
 * 8 <= n <= 26 corresponding to GIRQ08, GIRQ09, ..., GIRQ26
 */
#define MCHP_GIRQ_BLK_SETEN(n) \
	REG32(MCHP_GIRQ_BLK_ENSET_ADDR) = BIT(n)

#define MCHP_GIRQ_BLK_CLREN(n) \
	REG32(MCHP_GIRQ_BLK_ENCLR_ADDR) = BIT(n)

#define MCHP_GIRQ_BLK_IS_ACTIVE(n) \
	((REG32(MCHP_GIRQ_BLK_ACTIVE_ADDR) & BIT(n)) != 0u)

/* 8 <= n <= 26 corresponding to GIRQ08, GIRQ09, ..., GIRQ26 */
#define MCHP_GIRQ_SRC(n) REG32(MCHP_GIRQ_SRC_ADDR(n))

#define MCHP_GIRQ_ENSET(n) REG32(MCHP_GIRQ_ENSET_ADDR(n))

#define MCHP_GIRQ_RESULT(n) REG32(MCHP_GIRQ_RESULT_ADDR(n))
#define MCHP_GIRQ_ENCLR(n)  REG32(MCHP_GIRQ_ENCLR_ADDR(n))

/*
 * 8 <= n <= 26 corresponding to GIRQ08, GIRQ09, ..., GIRQ26
 * 0 <= pos <= 31 the bit position of the peripheral interrupt source.
 */
#define MCHP_GIRQ_SRC_CLR(n, pos) \
	REG32(MCHP_GIRQ_SRC_ADDR(n)) = BIT(pos)

#define MCHP_GIRQ_SET_EN(n, pos) \
	REG32(MCHP_GIRQ_ENSET_ADDR(n)) = BIT(pos)

#define MCHP_GIRQ_CLR_EN(n, pos) \
	REG32(MCHP_GIRQ_ENCLR_ADDR(n)) = BIT(pos)

#define MCHP_GIRQ_IS_RESULT(n, pos) \
	((REG32(MCHP_GIRQ_RESULT_ADDR(n)) & BIT(pos)) != 0u)

/* =========================================================================*/
/* ================	       ECIA			   ================ */
/* =========================================================================*/

enum MCHP_GIRQ_IDS {
	MCHP_GIRQ08_ID = 8,
	MCHP_GIRQ09_ID,
	MCHP_GIRQ10_ID,
	MCHP_GIRQ11_ID,
	MCHP_GIRQ12_ID,
	MCHP_GIRQ13_ID,
	MCHP_GIRQ14_ID,
	MCHP_GIRQ15_ID,
	MCHP_GIRQ16_ID,
	MCHP_GIRQ17_ID,
	MCHP_GIRQ18_ID,
	MCHP_GIRQ19_ID,
	MCHP_GIRQ20_ID,
	MCHP_GIRQ21_ID,
	MCHP_GIRQ22_ID,
	MCHP_GIRQ23_ID,
	MCHP_GIRQ24_ID,
	MCHP_GIRQ25_ID,
	MCHP_GIRQ26_ID,
	MCHP_GIRQ_ID_MAX,
};

/*
 * Legacy names: Port 80h capture peripherals.
 * GIRQ Source, Enable_Set/Clr, Result registers bit positions
 */
#define MCHP_PORT80_DEBUG0_GIRQ_VAL	BIT(22)
#define MCHP_PORT80_DEBUG1_GIRQ_VAL	BIT(23)

/* GIRQ08 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0140_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0141_GIRQ_BIT		BIT(1)
#define MCHP_GPIO_0142_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0143_GIRQ_BIT		BIT(3)
#define MCHP_GPIO_0144_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0145_GIRQ_BIT		BIT(5)
#define MCHP_GPIO_0146_GIRQ_BIT		BIT(6)
#define MCHP_GPIO_0147_GIRQ_BIT		BIT(7)
#define MCHP_GPIO_0150_GIRQ_BIT		BIT(8)
#define MCHP_GPIO_0151_GIRQ_BIT		BIT(9)
#define MCHP_GPIO_0152_GIRQ_BIT		BIT(10)
#define MCHP_GPIO_0153_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0154_GIRQ_BIT		BIT(12)
#define MCHP_GPIO_0155_GIRQ_BIT		BIT(13)
#define MCHP_GPIO_0156_GIRQ_BIT		BIT(14)
#define MCHP_GPIO_0157_GIRQ_BIT		BIT(15)
#define MCHP_GPIO_0161_GIRQ_BIT		BIT(17)
#define MCHP_GPIO_0162_GIRQ_BIT		BIT(18)
#define MCHP_GPIO_0163_GIRQ_BIT		BIT(19)
#define MCHP_GPIO_0165_GIRQ_BIT		BIT(21)
#define MCHP_GPIO_0170_GIRQ_BIT		BIT(24)
#define MCHP_GPIO_0171_GIRQ_BIT		BIT(25)
#define MCHP_GPIO_0172_GIRQ_BIT		BIT(26)
#define MCHP_GPIO_0175_GIRQ_BIT		BIT(29)
#define MCHP_GPIO_0140_0176_GIRQ_MASK	0x272effffu

/* GIRQ09 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0100_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0101_GIRQ_BIT		BIT(1)
#define MCHP_GPIO_0102_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0104_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0105_GIRQ_BIT		BIT(5)
#define MCHP_GPIO_0106_GIRQ_BIT		BIT(6)
#define MCHP_GPIO_0107_GIRQ_BIT		BIT(7)
#define MCHP_GPIO_0112_GIRQ_BIT		BIT(10)
#define MCHP_GPIO_0113_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0114_GIRQ_BIT		BIT(12)
#define MCHP_GPIO_0115_GIRQ_BIT		BIT(13)
#define MCHP_GPIO_0116_GIRQ_BIT		BIT(14)
#define MCHP_GPIO_0117_GIRQ_BIT		BIT(15)
#define MCHP_GPIO_0120_GIRQ_BIT		BIT(16)
#define MCHP_GPIO_0121_GIRQ_BIT		BIT(17)
#define MCHP_GPIO_0122_GIRQ_BIT		BIT(18)
#define MCHP_GPIO_0123_GIRQ_BIT		BIT(19)
#define MCHP_GPIO_0124_GIRQ_BIT		BIT(20)
#define MCHP_GPIO_0125_GIRQ_BIT		BIT(21)
#define MCHP_GPIO_0126_GIRQ_BIT		BIT(22)
#define MCHP_GPIO_0127_GIRQ_BIT		BIT(23)
#define MCHP_GPIO_0130_GIRQ_BIT		BIT(24)
#define MCHP_GPIO_0131_GIRQ_BIT		BIT(25)
#define MCHP_GPIO_0132_GIRQ_BIT		BIT(26)
#define MCHP_GPIO_0100_0136_GIRQ_MASK	0x07fffcf7u

/* GIRQ10 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0040_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0042_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0043_GIRQ_BIT		BIT(3)
#define MCHP_GPIO_0044_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0045_GIRQ_BIT		BIT(5)
#define MCHP_GPIO_0046_GIRQ_BIT		BIT(6)
#define MCHP_GPIO_0047_GIRQ_BIT		BIT(7)
#define MCHP_GPIO_0050_GIRQ_BIT		BIT(8)
#define MCHP_GPIO_0051_GIRQ_BIT		BIT(9)
#define MCHP_GPIO_0052_GIRQ_BIT		BIT(10)
#define MCHP_GPIO_0053_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0054_GIRQ_BIT		BIT(12)
#define MCHP_GPIO_0055_GIRQ_BIT		BIT(13)
#define MCHP_GPIO_0056_GIRQ_BIT		BIT(14)
#define MCHP_GPIO_0057_GIRQ_BIT		BIT(15)
#define MCHP_GPIO_0060_GIRQ_BIT		BIT(16)
#define MCHP_GPIO_0061_GIRQ_BIT		BIT(17)
#define MCHP_GPIO_0062_GIRQ_BIT		BIT(18)
#define MCHP_GPIO_0063_GIRQ_BIT		BIT(19)
#define MCHP_GPIO_0064_GIRQ_BIT		BIT(20)
#define MCHP_GPIO_0065_GIRQ_BIT		BIT(21)
#define MCHP_GPIO_0066_GIRQ_BIT		BIT(22)
#define MCHP_GPIO_0067_GIRQ_BIT		BIT(23)
#define MCHP_GPIO_0070_GIRQ_BIT		BIT(24)
#define MCHP_GPIO_0071_GIRQ_BIT		BIT(25)
#define MCHP_GPIO_0072_GIRQ_BIT		BIT(26)
#define MCHP_GPIO_0073_GIRQ_BIT		BIT(27)
#define MCHP_GPIO_0074_GIRQ_BIT		BIT(28)
#define MCHP_GPIO_0075_GIRQ_BIT		BIT(29)
#define MCHP_GPIO_0040_0076_GIRQ_MASK	0x3ffffffdu

/* GIRQ11 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0000_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0002_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0003_GIRQ_BIT		BIT(3)
#define MCHP_GPIO_0004_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0007_GIRQ_BIT		BIT(7)
#define MCHP_GPIO_0010_GIRQ_BIT		BIT(8)
#define MCHP_GPIO_0011_GIRQ_BIT		BIT(9)
#define MCHP_GPIO_0012_GIRQ_BIT		BIT(10)
#define MCHP_GPIO_0013_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0014_GIRQ_BIT		BIT(12)
#define MCHP_GPIO_0015_GIRQ_BIT		BIT(13)
#define MCHP_GPIO_0016_GIRQ_BIT		BIT(14)
#define MCHP_GPIO_0017_GIRQ_BIT		BIT(15)
#define MCHP_GPIO_0020_GIRQ_BIT		BIT(16)
#define MCHP_GPIO_0021_GIRQ_BIT		BIT(17)
#define MCHP_GPIO_0022_GIRQ_BIT		BIT(18)
#define MCHP_GPIO_0023_GIRQ_BIT		BIT(19)
#define MCHP_GPIO_0024_GIRQ_BIT		BIT(20)
#define MCHP_GPIO_0025_GIRQ_BIT		BIT(21)
#define MCHP_GPIO_0026_GIRQ_BIT		BIT(22)
#define MCHP_GPIO_0027_GIRQ_BIT		BIT(23)
#define MCHP_GPIO_0030_GIRQ_BIT		BIT(24)
#define MCHP_GPIO_0031_GIRQ_BIT		BIT(25)
#define MCHP_GPIO_0032_GIRQ_BIT		BIT(26)
#define MCHP_GPIO_0033_GIRQ_BIT		BIT(27)
#define MCHP_GPIO_0034_GIRQ_BIT		BIT(28)
#define MCHP_GPIO_0035_GIRQ_BIT		BIT(29)
#define MCHP_GPIO_0036_GIRQ_BIT		BIT(30)
#define MCHP_GPIO_0000_0036_GIRQ_MASK	0x7fffff9du

/* GIRQ12 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0200_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0201_GIRQ_BIT		BIT(1)
#define MCHP_GPIO_0202_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0203_GIRQ_BIT		BIT(3)
#define MCHP_GPIO_0204_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0205_GIRQ_BIT		BIT(5)
#define MCHP_GPIO_0206_GIRQ_BIT		BIT(6)
#define MCHP_GPIO_0207_GIRQ_BIT		BIT(7)
#define MCHP_GPIO_0211_GIRQ_BIT		BIT(9)
#define MCHP_GPIO_0212_GIRQ_BIT		BIT(10)
#define MCHP_GPIO_0213_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0221_GIRQ_BIT		BIT(17)
#define MCHP_GPIO_0222_GIRQ_BIT		BIT(18)
#define MCHP_GPIO_0223_GIRQ_BIT		BIT(19)
#define MCHP_GPIO_0224_GIRQ_BIT		BIT(20)
#define MCHP_GPIO_0226_GIRQ_BIT		BIT(22)
#define MCHP_GPIO_0227_GIRQ_BIT		BIT(23)
#define MCHP_GPIO_0200_0236_GIRQ_MASK	0x00de0effu

/* GIRQ13 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_I2C_SMB_0_GIRQ_BIT		BIT(0)
#define MCHP_I2C_SMB_1_GIRQ_BIT		BIT(1)
#define MCHP_I2C_SMB_2_GIRQ_BIT		BIT(2)
#define MCHP_I2C_SMB_3_GIRQ_BIT		BIT(3)
#define MCHP_I2C_SMB_4_GIRQ_BIT		BIT(4)
#define MCHP_I2C_0_GIRQ_BIT		BIT(5)
#define MCHP_I2C_1_GIRQ_BIT		BIT(6)
#define MCHP_I2C_2_GIRQ_BIT		BIT(7)
/* Masks for blocks with multiple instances or sources */
#define MCHP_SMB_I2C_GIRQ_MASK		0x1fu
#define MCHP_I2C_GIRQ_MASK		0xe0u

/* GIRQ14 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_DMA_CH00_GIRQ_BIT		BIT(0)
#define MCHP_DMA_CH01_GIRQ_BIT		BIT(1)
#define MCHP_DMA_CH02_GIRQ_BIT		BIT(2)
#define MCHP_DMA_CH03_GIRQ_BIT		BIT(3)
#define MCHP_DMA_CH04_GIRQ_BIT		BIT(4)
#define MCHP_DMA_CH05_GIRQ_BIT		BIT(5)
#define MCHP_DMA_CH06_GIRQ_BIT		BIT(6)
#define MCHP_DMA_CH07_GIRQ_BIT		BIT(7)
#define MCHP_DMA_CH08_GIRQ_BIT		BIT(8)
#define MCHP_DMA_CH09_GIRQ_BIT		BIT(9)
#define MCHP_DMA_CH10_GIRQ_BIT		BIT(10)
#define MCHP_DMA_CH11_GIRQ_BIT		BIT(11)
#define MCHP_DMA_GIRQ_MASK		0x0fffu

/* GIRQ15 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_UART_0_GIRQ_BIT		BIT(0)
#define MCHP_UART_1_GIRQ_BIT		BIT(1)
#define MCHP_EMI_0_GIRQ_BIT		BIT(2)
#define MCHP_EMI_1_GIRQ_BIT		BIT(3)
#define MCHP_UART_2_GIRQ_BIT		BIT(4)
#define MCHP_ACPI_EC_0_IBF_GIRQ_BIT	BIT(5)
#define MCHP_ACPI_EC_0_OBE_GIRQ_BIT	BIT(6)
#define MCHP_ACPI_EC_1_IBF_GIRQ_BIT	BIT(7)
#define MCHP_ACPI_EC_1_OBE_GIRQ_BIT	BIT(8)
#define MCHP_ACPI_EC_2_IBF_GIRQ_BIT	BIT(9)
#define MCHP_ACPI_EC_2_OBE_GIRQ_BIT	BIT(10)
#define MCHP_ACPI_EC_3_IBF_GIRQ_BIT	BIT(11)
#define MCHP_ACPI_EC_3_OBE_GIRQ_BIT	BIT(12)
#define MCHP_ACPI_PM1_CTL_GIRQ_BIT	BIT(15)
#define MCHP_ACPI_PM1_EN_GIRQ_BIT	BIT(16)
#define MCHP_ACPI_PM1_STS_GIRQ_BIT	BIT(17)
#define MCHP_KBC_OBE_GIRQ_BIT		BIT(18)
#define MCHP_KBC_IBF_GIRQ_BIT		BIT(19)
#define MCHP_MBOX_0_GIRQ_BIT		BIT(20)
#define MCHP_P80BD_0_GIRQ_BIT		BIT(22)
#define MCHP_P80BD_1_GIRQ_BIT		BIT(23)
/* Masks for blocks with multiple instances or sources */
#define MCHP_UART_GIRQ_MASK		0x13u
#define MCHP_UART_EMI_GIRQ_MASK		0x0cu
#define MCHP_ACPI_EC_GIRQ_MASK		0x01fe0u
#define MCHP_ACPI_PM1_GIRQ_MASK		0x38000u
#define MCHP_KBC_GIRQ_MASK		0xc0000u
#define MCHP_BDP_MASK			0xc00000u
#define MCHP_HOST_PERIPH_GIRQ_MASK	0xdf9fffu

/* GIRQ16 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_PK_ERR_GIRQ_BIT		BIT(0)
#define MCHP_PK_END_GIRQ_BIT		BIT(1)
#define MCHP_RNG_GIRQ_BIT		BIT(2)
#define MCHP_AES_GIRQ_BIT		BIT(3)
#define MCHP_HASH_GIRQ_BIT		BIT(4)
#define MCHP_CRYPTO_GIRQ_MASK		0x1fu

/* GIRQ17 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_PECI_GIRQ_BIT		BIT(0)
#define MCHP_TACH_0_GIRQ_BIT		BIT(1)
#define MCHP_TACH_1_GIRQ_BIT		BIT(2)
#define MCHP_TACH_2_GIRQ_BIT		BIT(3)
#define MCHP_TACH_3_GIRQ_BIT		BIT(4)
#define MCHP_HDMI_CEC_0_GIRQ_BIT	BIT(5)
#define MCHP_ADC_0_SGL_GIRQ_BIT		BIT(8)
#define MCHP_ADC_0_RPT_GIRQ_BIT		BIT(9)
#define MCHP_LED_0_GIRQ_BIT		BIT(13)
#define MCHP_LED_1_GIRQ_BIT		BIT(14)
#define MCHP_LED_2_GIRQ_BIT		BIT(15)
#define MCHP_PHOT_0_GIRQ_BIT		BIT(17)
/* Masks for blocks with multiple instances or sources */
#define MCHP_TACH_GIRQ_MASK		0x1eu
#define MCHP_ADC_GIRQ_MASK		0x300u
#define MCHP_LED_GIRQ_MASK		0xe000u
#define MCHP_PERIPH_GROUP_1_MASK	0x2e33fu

/* GIRQ18 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_SPIEP_0_GIRQ_BIT		BIT(0)
#define MCHP_QMSPI_0_GIRQ_BIT		BIT(1)
#define MCHP_PS2_0_ACT_GIRQ_BIT		BIT(10)
#define MCHP_PS2_1_ACT_GIRQ_BIT		BIT(11)
#define MCHP_EERPROMC_0_GIRQ_BIT	BIT(13)
#define MCHP_CCT_0_CNT_GIRQ_BIT		BIT(20)
#define MCHP_CCT_0_CAP0_GIRQ_BIT	BIT(21)
#define MCHP_CCT_0_CAP1_GIRQ_BIT	BIT(22)
#define MCHP_CCT_0_CAP2_GIRQ_BIT	BIT(23)
#define MCHP_CCT_0_CAP3_GIRQ_BIT	BIT(24)
#define MCHP_CCT_0_CAP4_GIRQ_BIT	BIT(25)
#define MCHP_CCT_0_CAP5_GIRQ_BIT	BIT(26)
#define MCHP_CCT_0_CMP0_GIRQ_BIT	BIT(27)
#define MCHP_CCT_0_CMP1_GIRQ_BIT	BIT(28)
/* Masks for blocks with multiple instances or sources */
#define MCHP_PS2_GIRQ_MASK		0xc00u
#define MCHP_CCT_0_GIRQ_MASK		0x1ff00000u
#define MCHP_PERIPH_GROUP_2_MASK	0x1ff02c03u

/* GIRQ19 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_ESPI_PC_GIRQ_BIT		BIT(0)
#define MCHP_ESPI_BM1_GIRQ_BIT		BIT(1)
#define MCHP_ESPI_BM2_GIRQ_BIT		BIT(2)
#define MCHP_ESPI_LTR_GIRQ_BIT		BIT(3)
#define MCHP_ESPI_OOB_UP_GIRQ_BIT	BIT(4)
#define MCHP_ESPI_OOB_DN_GIRQ_BIT	BIT(5)
#define MCHP_ESPI_FC_GIRQ_BIT		BIT(6)
#define MCHP_ESPI_RESET_GIRQ_BIT	BIT(7)
#define MCHP_ESPI_VWEN_GIRQ_BIT		BIT(8)
#define MCHP_ESPI_SAF_DONE_GIRQ_BIT	BIT(9)
#define MCHP_ESPI_SAF_ERR_GIRQ_BIT	BIT(10)
/* Masks for blocks with multiple instances or sources */
#define MCHP_ESPI_BM_GIRQ_MASK		0x006u
#define MCHP_ESPI_OOB_GIRQ_MASK		0x030u
#define MCHP_ESPI_SAF_GIRQ_MASK		0x600u
#define MCHP_ESPI_GIRQ_MASK		0xfffu

/* GIRQ20 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_STAP_OBF_GIRQ_BIT		BIT(0)
#define MCHP_STAP_IBF_GIRQ_BIT		BIT(1)
#define MCHP_STAP_WAKE_GIRQ_BIT		BIT(2)
#define MCHP_OTP_READY_GIRQ_BIT		BIT(3)
/* Masks for blocks with multiple instances or sources */
#define MCHP_STAP_GIRQ_MASK		0x007u
#define MCHP_PERIPH_GROUP_3_MASK	0x00fu

/* GIRQ21 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_WDT_GIRQ_BIT		BIT(2)
#define MCHP_WTMR_ALARM_GIRQ_BIT	BIT(3)
#define MCHP_WTMR_SUBWK_GIRQ_BIT	BIT(4)
#define MCHP_WTMR_ONESEC_GIRQ_BIT	BIT(5)
#define MCHP_WTMR_SUBSEC_GIRQ_BIT	BIT(6)
#define MCHP_WTMR_SPP_GIRQ_BIT		BIT(7)
#define MCHP_RTC_GIRQ_BIT		BIT(8)
#define MCHP_RTC_ALARM_GIRQ_BIT		BIT(9)
#define MCHP_VCI_OVRD_IN_GIRQ_BIT	BIT(10)
#define MCHP_VCI_IN0_GIRQ_BIT		BIT(11)
#define MCHP_VCI_IN1_GIRQ_BIT		BIT(12)
#define MCHP_VCI_IN2_GIRQ_BIT		BIT(13)
#define MCHP_VCI_IN3_GIRQ_BIT		BIT(14)
#define MCHP_PS2_0_PORT0A_WK_GIRQ_BIT	BIT(18)
#define MCHP_PS2_0_PORT0B_WK_GIRQ_BIT	BIT(19)
#define MCHP_PS2_0_PORT1B_WK_GIRQ_BIT	BIT(21)
#define MCHP_KEYSCAN_GIRQ_BIT		BIT(25)
#define MCHP_GLUE_GIRQ_BIT		BIT(26)
/* Masks for blocks with multiple instances or sources */
#define MCHP_WTMR_GIRQ_MASK		0xf8u
#define MCHP_RTC_GIRQ_MASK		0x300u
#define MCHP_VCI_GIRQ_MASK		0x7c00u
#define MCHP_PS2_PORT_WK_GIRQ_MASK	0x2c0000u
#define MCHP_PERIPH_GROUP_4_MASK	0x62c7ffcu

/*
 * GIRQ22 Source, Enable_Set/Clr, Result registers bit positions
 * NOTE: These wake sources allow the peripheral to turn back on clocks
 * long enough to facilite the data transfer. No interrupt to the EC occurs
 * unless the peripheral was configured to generate an EC interrupt for
 * the specific data transfer.
 */
#define MCHP_SPIEP_WK_CLK_GIRQ_BIT	BIT(0)
#define MCHP_I2C_SMB_0_WK_CLK_GIRQ_BIT	BIT(1)
#define MCHP_I2C_SMB_1_WK_CLK_GIRQ_BIT	BIT(2)
#define MCHP_I2C_SMB_2_WK_CLK_GIRQ_BIT	BIT(3)
#define MCHP_I2C_SMB_3_WK_CLK_GIRQ_BIT	BIT(4)
#define MCHP_I2C_SMB_4_WK_CLK_GIRQ_BIT	BIT(5)
#define MCHP_I2C_0_WK_CLK_GIRQ_BIT	BIT(6)
#define MCHP_I2C_1_WK_CLK_GIRQ_BIT	BIT(7)
#define MCHP_I2C_2_WK_CLK_GIRQ_BIT	BIT(8)
#define MCHP_ESPI_WK_CLK_GIRQ_BIT	BIT(9)
/* Masks for blocks with multiple instances or sources */
#define MCHP_I2C_SMB_WK_CLK_GIRQ_MASK	0x3eu
#define MCHP_I2C_WK_CLK_GIRQ_MASK	0x1c0u
#define MCHP_CLK_WK_CLK_GIRQ_MASK	0x3ffu

/* GIRQ23 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_BTMR16_0_GIRQ_BIT		BIT(0)
#define MCHP_BTMR16_1_GIRQ_BIT		BIT(1)
#define MCHP_BTMR32_0_GIRQ_BIT		BIT(4)
#define MCHP_BTMR32_1_GIRQ_BIT		BIT(5)
#define MCHP_RTMR_0_GIRQ_BIT		BIT(10)
#define MCHP_RTMR_0_SWI0_GIRQ_BIT	BIT(11)
#define MCHP_RTMR_0_SWI1_GIRQ_BIT	BIT(12)
#define MCHP_RTMR_0_SWI2_GIRQ_BIT	BIT(13)
#define MCHP_RTMR_0_SWI3_GIRQ_BIT	BIT(14)
#define MCHP_HTMR_0_GIRQ_BIT		BIT(16)
#define MCHP_HTMR_1_GIRQ_BIT		BIT(17)
/* Masks for blocks with multiple instances or sources */
#define MCHP_BTMR16_GIRQ_MASK		0x03u
#define MCHP_BTMR32_GIRQ_MASK		0x30u
#define MCHP_RMTR_GIRQ_MASK		0x7c00u
#define MCHP_HTMR_GIRQ_MASK		0x30000u
#define MCHP_PERIPH_GROUP_5_GIRQ_MASK	0x37c33u

/* GIRQ24 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_MSVW00_SRC0_GIRQ_BIT	BIT(0)
#define MCHP_MSVW00_SRC1_GIRQ_BIT	BIT(1)
#define MCHP_MSVW00_SRC2_GIRQ_BIT	BIT(2)
#define MCHP_MSVW00_SRC3_GIRQ_BIT	BIT(3)
#define MCHP_MSVW01_SRC0_GIRQ_BIT	BIT(4)
#define MCHP_MSVW01_SRC1_GIRQ_BIT	BIT(5)
#define MCHP_MSVW01_SRC2_GIRQ_BIT	BIT(6)
#define MCHP_MSVW01_SRC3_GIRQ_BIT	BIT(7)
#define MCHP_MSVW02_SRC0_GIRQ_BIT	BIT(8)
#define MCHP_MSVW02_SRC1_GIRQ_BIT	BIT(9)
#define MCHP_MSVW02_SRC2_GIRQ_BIT	BIT(10)
#define MCHP_MSVW02_SRC3_GIRQ_BIT	BIT(11)
#define MCHP_MSVW03_SRC0_GIRQ_BIT	BIT(12)
#define MCHP_MSVW03_SRC1_GIRQ_BIT	BIT(13)
#define MCHP_MSVW03_SRC2_GIRQ_BIT	BIT(14)
#define MCHP_MSVW03_SRC3_GIRQ_BIT	BIT(15)
#define MCHP_MSVW04_SRC0_GIRQ_BIT	BIT(16)
#define MCHP_MSVW04_SRC1_GIRQ_BIT	BIT(17)
#define MCHP_MSVW04_SRC2_GIRQ_BIT	BIT(18)
#define MCHP_MSVW04_SRC3_GIRQ_BIT	BIT(19)
#define MCHP_MSVW05_SRC0_GIRQ_BIT	BIT(20)
#define MCHP_MSVW05_SRC1_GIRQ_BIT	BIT(21)
#define MCHP_MSVW05_SRC2_GIRQ_BIT	BIT(22)
#define MCHP_MSVW05_SRC3_GIRQ_BIT	BIT(23)
#define MCHP_MSVW06_SRC0_GIRQ_BIT	BIT(24)
#define MCHP_MSVW06_SRC1_GIRQ_BIT	BIT(25)
#define MCHP_MSVW06_SRC2_GIRQ_BIT	BIT(26)
#define MCHP_MSVW06_SRC3_GIRQ_BIT	BIT(27)
/* Masks for blocks with multiple instances or sources */
#define MCHP_MSVW00_GIRQ_MASK		0xfu
#define MCHP_MSVW01_GIRQ_MASK		0xf0u
#define MCHP_MSVW02_GIRQ_MASK		0xf00u
#define MCHP_MSVW03_GIRQ_MASK		0xf000u
#define MCHP_MSVW04_GIRQ_MASK		0xf0000u
#define MCHP_MSVW05_GIRQ_MASK		0xf00000u
#define MCHP_MSVW06_GIRQ_MASK		0xf000000u
#define MCHP_MSVW00_06_GIRQ_MASK	0x0fffffffu

/* GIRQ25 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_MSVW07_SRC0_GIRQ_BIT	BIT(0)
#define MCHP_MSVW07_SRC1_GIRQ_BIT	BIT(1)
#define MCHP_MSVW07_SRC2_GIRQ_BIT	BIT(2)
#define MCHP_MSVW07_SRC3_GIRQ_BIT	BIT(3)
#define MCHP_MSVW08_SRC0_GIRQ_BIT	BIT(4)
#define MCHP_MSVW08_SRC1_GIRQ_BIT	BIT(5)
#define MCHP_MSVW08_SRC2_GIRQ_BIT	BIT(6)
#define MCHP_MSVW08_SRC3_GIRQ_BIT	BIT(7)
#define MCHP_MSVW09_SRC0_GIRQ_BIT	BIT(8)
#define MCHP_MSVW09_SRC1_GIRQ_BIT	BIT(9)
#define MCHP_MSVW09_SRC2_GIRQ_BIT	BIT(10)
#define MCHP_MSVW09_SRC3_GIRQ_BIT	BIT(11)
#define MCHP_MSVW10_SRC0_GIRQ_BIT	BIT(12)
#define MCHP_MSVW10_SRC1_GIRQ_BIT	BIT(13)
#define MCHP_MSVW10_SRC2_GIRQ_BIT	BIT(14)
#define MCHP_MSVW10_SRC3_GIRQ_BIT	BIT(15)
/* Masks for blocks with multiple instances or sources */
#define MCHP_MSVW07_GIRQ_MASK		0xfu
#define MCHP_MSVW08_GIRQ_MASK		0xf0u
#define MCHP_MSVW09_GIRQ_MASK		0xf00u
#define MCHP_MSVW10_GIRQ_MASK		0xf000u
#define MCHP_MSVW07_10_GIRQ_MASK	0xffffu

/* GIRQ26 Source, Enable_Set/Clr, Result registers bit positions */
#define MCHP_GPIO_0240_GIRQ_BIT		BIT(0)
#define MCHP_GPIO_0241_GIRQ_BIT		BIT(1)
#define MCHP_GPIO_0242_GIRQ_BIT		BIT(2)
#define MCHP_GPIO_0243_GIRQ_BIT		BIT(3)
#define MCHP_GPIO_0244_GIRQ_BIT		BIT(4)
#define MCHP_GPIO_0245_GIRQ_BIT		BIT(5)
#define MCHP_GPIO_0246_GIRQ_BIT		BIT(6)
#define MCHP_GPIO_0250_GIRQ_BIT		BIT(8)
#define MCHP_GPIO_0253_GIRQ_BIT		BIT(11)
#define MCHP_GPIO_0254_GIRQ_BIT		BIT(12)
#define MCHP_GPIO_0255_GIRQ_BIT		BIT(13)
/* Masks for blocks with multiple instances or sources */
#define MCHP_GPIO_0240_0276_GIRQ_MASK	0x397fu

#define MCHP_GIRQ_START_NUM	8u
#define MCHP_GIRQ_LAST_NUM	26u
#define MCHP_GIRQ_IDX(girq)	((uint32_t)(girq) - 8u)
#define MCHP_GIRQ_IDX_FIRST	0u
#define MCHP_GIRQ_IDX_MAX	19u
#define MCHP_MAX_NVIC_IDX	6u

/** @brief ECIA GIRQn register block. Size = 0x14(20) bytes */
typedef struct girq_regs
{
	__IOM uint32_t SRC;	/* R/W1C source status bits */
	__IOM uint32_t EN_SET;	/* R/W1S Write 1 to set enable(s) */
	__IOM uint32_t RESULT;	/* R/O equals SRC AND EN_SET */
	__IOM uint32_t EN_CLR;	/* R/W1S Write 1 to clear enable(s) */
	uint8_t RSVD1[4];
} GIRQ_Type;

/** @brief EC Interrupt Aggregator (ECIA) */
typedef struct ecia_regs
{		/*!< (@ 0x4000e000) ECIA Structure   */
	union {
		struct {
			GIRQ_Type GIRQ08;	/*!< (@ 0x0000) GIRQ08 registers */
			GIRQ_Type GIRQ09;	/*!< (@ 0x0014) GIRQ09 registers */
			GIRQ_Type GIRQ10;	/*!< (@ 0x0028) GIRQ10 registers */
			GIRQ_Type GIRQ11;	/*!< (@ 0x003c) GIRQ11 registers */
			GIRQ_Type GIRQ12;	/*!< (@ 0x0050) GIRQ12 registers */
			GIRQ_Type GIRQ13;	/*!< (@ 0x0064) GIRQ13 registers */
			GIRQ_Type GIRQ14;	/*!< (@ 0x0078) GIRQ14 registers */
			GIRQ_Type GIRQ15;	/*!< (@ 0x008c) GIRQ15 registers */
			GIRQ_Type GIRQ16;	/*!< (@ 0x00a0) GIRQ16 registers */
			GIRQ_Type GIRQ17;	/*!< (@ 0x00b4) GIRQ17 registers */
			GIRQ_Type GIRQ18;	/*!< (@ 0x00c8) GIRQ18 registers */
			GIRQ_Type GIRQ19;	/*!< (@ 0x00dc) GIRQ19 registers */
			GIRQ_Type GIRQ20;	/*!< (@ 0x00f0) GIRQ20 registers */
			GIRQ_Type GIRQ21;	/*!< (@ 0x0104) GIRQ21 registers */
			GIRQ_Type GIRQ22;	/*!< (@ 0x0118) GIRQ22 registers */
			GIRQ_Type GIRQ23;	/*!< (@ 0x012c) GIRQ23 registers */
			GIRQ_Type GIRQ24;	/*!< (@ 0x0140) GIRQ24 registers */
			GIRQ_Type GIRQ25;	/*!< (@ 0x0154) GIRQ25 registers */
			GIRQ_Type GIRQ26;	/*!< (@ 0x0168) GIRQ26 registers */
		};
		GIRQ_Type GIRQ[19];
	};
	uint8_t RSVD2[(0x0200u - 0x017cu)];	/* offsets 0x017c - 0x1ff */
	__IOM uint32_t BLK_EN_SET;	/*! (@ 0x00000200) Aggregated GIRQ output Enable Set */
	__IOM uint32_t BLK_EN_CLR;	/*! (@ 0x00000204) Aggregated GIRQ output Enable Clear */
	__IM uint32_t BLK_ACTIVE;	/*! (@ 0x00000204) GIRQ Active bitmap (RO) */
} ECIA_Type;

#endif	/* #ifndef _ECIA_H */
/* end ecia.h */
/**   @}
 */
