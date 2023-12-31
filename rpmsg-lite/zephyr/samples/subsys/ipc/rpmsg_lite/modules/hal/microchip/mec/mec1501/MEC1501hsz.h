/**************************************************************************//**
* @file     MEC1501hsz.h
* @brief    CMSIS Cortex-M4 Core Peripheral Access Layer Header File for
*           Device Microchip MEC1501-H-SZ
* @version  V5.00
* @date     03. January 2019
* Copyright (c) 2019 Microchip Technology Inc.
******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 * Copyright (c) 2019 Microchip Technology Incorporated. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MEC1501HSZ_H
#define MEC1501HSZ_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup MCHP
  * @{
  */

/** @addtogroup MEC1501
  * @{
  */

/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn {
	/* =======================================  ARM Cortex-M4 Specific Interrupt Numbers  ======================================== */

	Reset_IRQn = -15,	/*!< -15  Reset Vector, invoked on Power up and warm reset                     */
	NonMaskableInt_IRQn = -14,	/*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
	HardFault_IRQn = -13,	/*!< -13  Hard Fault, all classes of Fault                                     */
	MemoryManagement_IRQn = -12,	/*!< -12  Memory Management, MPU mismatch, including Access Violation
						   and No Match                                                         */
	BusFault_IRQn = -11,	/*!< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
					   related Fault                                                        */
	UsageFault_IRQn = -10,	/*!< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
	SVCall_IRQn = -5,	/*!< -5 System Service Call via SVC instruction                                */
	DebugMonitor_IRQn = -4,	/*!< -4 Debug Monitor                                                          */
	PendSV_IRQn = -2,	/*!< -2 Pendable request for system service                                    */
	SysTick_IRQn = -1,	/*!< -1 System Tick Timer                                                      */

	/* ===========================================  MEC15xx Specific Interrupt Numbers  ========================================= */

	GIRQ08_IRQn = 0,	/*!< GPIO 0140 - 0176 */
	GIRQ09_IRQn = 1,	/*!< GPIO 0100 - 0136 */
	GIRQ10_IRQn = 2,	/*!< GPIO 0040 - 0076 */
	GIRQ11_IRQn = 3,	/*!< GPIO 0000 - 0036 */
	GIRQ12_IRQn = 4,	/*!< GPIO 0200 - 0236 */
	GIRQ13_IRQn = 5,	/*!< SMBus Aggregated */
	GIRQ14_IRQn = 6,	/*!< DMA Aggregated */
	GIRQ15_IRQn = 7,
	GIRQ16_IRQn = 8,
	GIRQ17_IRQn = 9,
	GIRQ18_IRQn = 10,
	GIRQ19_IRQn = 11,
	GIRQ20_IRQn = 12,
	GIRQ21_IRQn = 13,
	/* GIRQ22 is not connected to EC. It's purpose is peripheral clock wake */
	GIRQ23_IRQn = 14,
	GIRQ24_IRQn = 15,
	GIRQ25_IRQn = 16,
	GIRQ26_IRQn = 17,	/*!< GPIO 0240 - 0276 */
	/* Reserved gap, 18-19 */
	/* GIRQ's 8 - 12, 24 - 26 no direct connections */
	SMB0_IRQn = 20,	/* GIRQ13 b[0] */
	SMB1_IRQn = 21,	/* GIRQ13 b[1] */
	SMB2_IRQn = 22,	/* GIRQ13 b[2] */
	SMB3_IRQn = 23,	/* GIRQ13 b[3] */
	DMA0_IRQn = 24,	/* GIRQ14 b[0] */
	DMA1_IRQn = 25,	/* GIRQ14 b[1] */
	DMA2_IRQn = 26,	/* GIRQ14 b[2] */
	DMA3_IRQn = 27,	/* GIRQ14 b[3] */
	DMA4_IRQn = 28,	/* GIRQ14 b[4] */
	DMA5_IRQn = 29,	/* GIRQ14 b[5] */
	DMA6_IRQn = 30,	/* GIRQ14 b[6] */
	DMA7_IRQn = 31,	/* GIRQ14 b[7] */
	DMA8_IRQn = 32,	/* GIRQ14 b[8] */
	DMA9_IRQn = 33,	/* GIRQ14 b[9] */
	DMA10_IRQn = 34,	/* GIRQ14 b[10] */
	DMA11_IRQn = 35,	/* GIRQ14 b[11] */
	/* Reserved gap, 36-37 */
	/* Reserved gap, 38-39 */
	UART0_IRQn = 40,	/* GIRQ15 b[0] */
	UART1_IRQn = 41,	/* GIRQ15 b[1] */
	EMI0_IRQn = 42,	/* GIRQ15 b[2] */
	EMI1_IRQn = 43,	/* GIRQ15 b[3] */
	UART2_IRQn = 44,	/* GIRQ15 b[4] */
	ACPI_EC0_IBF_IRQn = 45,	/* GIRQ15 b[5] */
	ACPI_EC0_OBE_IRQn = 46,	/* GIRQ15 b[6] */
	ACPI_EC1_IBF_IRQn = 47,	/* GIRQ15 b[7] */
	ACPI_EC1_OBE_IRQn = 48,	/* GIRQ15 b[8] */
	ACPI_EC2_IBF_IRQn = 49,	/* GIRQ15 b[9] */
	ACPI_EC2_OBE_IRQn = 50,	/* GIRQ15 b[10] */
	ACPI_EC3_IBF_IRQn = 51,	/* GIRQ15 b[11] */
	ACPI_EC3_OBE_IRQn = 52,	/* GIRQ15 b[12] */
	/* Reserved gap, 53-54 */
	ACPI_PM1_CTL_IRQn = 55,	/* GIRQ15 b[15] */
	ACPI_PM1_EN_IRQn = 56,	/* GIRQ15 b[16] */
	ACPI_PM1_STS_IRQn = 57,	/* GIRQ15 b[17] */
	KBC_OBE_IRQn = 58,	/* GIRQ15 b[18] */
	KBC_IBF_IRQn = 59,	/* GIRQ15 b[19] */
	MBOX_IRQn = 60,	/* GIRQ15 b[20] */
	/* reserved gap 61 */
	P80CAP0_IRQn = 62,	/* GIRQ15 b[22] */
	P80CAP1_IRQn = 63,	/* GIRQ15 b[23] */
	/* reserved gap 64 */
	PKE_ERR_IRQn = 65,	/* GIRQ16 b[0] */
	PKE_DONE_IRQn = 66,	/* GIRQ16 b[1] */
	RNG_IRQn = 67,	/* GIRQ16 b[2] */
	AES_IRQn = 68,	/* GIRQ16 b[3] */
	HASH_IRQn = 69,	/* GIRQ16 b[4] */
	PECI_IRQn = 70,	/* GIRQ17 b[0] */
	TACH0_IRQn = 71,	/* GIRQ17 b[1] */
	TACH1_IRQn = 72,	/* GIRQ17 b[2] */
	TACH2_IRQn = 73,	/* GIRQ17 b[3] */
	/* reserved gap 74-77 */
	ADC_SNGL_IRQn = 78,	/* GIRQ17 b[8] */
	ADC_RPT_IRQn = 79,	/* GIRQ17 b[9] */
	/* reserved gap 80-82 */
	LED0_IRQn = 83,	/* GIRQ17 b[13] */
	LED1_IRQn = 84,	/* GIRQ17 b[14] */
	LED2_IRQn = 85,	/* GIRQ17 b[15] */
	/* reserved gap 86 */
	PHOT_IRQn = 87,	/* GIRQ17 b[17] */
	/* reserved gap 88-89 */
	SPISLV_IRQn = 90,	/* GIRQ18 b[0] */
	QMSPI_IRQn = 91,	/* GIRQ18 b[1] */
	/* reserved gap 92-99 */
	PS2_0_ACT_IRQn = 100,	/* GIRQ18 b[10] */
	PS2_1_ACT_IRQn = 101,	/* GIRQ18 b[11] */
	/* reserved gap 102 */
	ESPI_PC_IRQn = 103,	/* GIRQ19 b[0] */
	ESPI_BM1_IRQn = 104,	/* GIRQ19 b[1] */
	ESPI_BM2_IRQn = 105,	/* GIRQ19 b[2] */
	ESPI_LTR_IRQn = 106,	/* GIRQ19 b[3] */
	ESPI_OOB_UP_IRQn = 107,	/* GIRQ19 b[4] */
	ESPI_OOB_DN_IRQn = 108,	/* GIRQ19 b[5] */
	ESPI_FLASH_IRQn = 109,	/* GIRQ19 b[6] */
	ESPI_RESET_IRQn = 110,	/* GIRQ19 b[7] */
	RTMR_IRQn = 111,	/* GIRQ23 b[10] */
	HTMR0_IRQn = 112,	/* GIRQ23 b[16] */
	HTMR1_IRQn = 113,	/* GIRQ23 b[17] */
	WK_IRQn = 114,	/* GIRQ21 b[3] */
	WKSUB_IRQn = 115,	/* GIRQ21 b[4] */
	WKSEC_IRQn = 116,	/* GIRQ21 b[5] */
	WKSUBSEC_IRQn = 117,	/* GIRQ21 b[6] */
	SYSPWR_IRQn = 118,	/* GIRQ21 b[7] */
	RTC_IRQn = 119,	/* GIRQ21 b[8] */
	RTC_ALARM_IRQn = 120,	/* GIRQ21 b[9] */
	VCI_OVRD_IN_IRQn = 121,	/* GIRQ21 b[10] */
	VCI_IN0_IRQn = 122,	/* GIRQ21 b[11] */
	VCI_IN1_IRQn = 123,	/* GIRQ21 b[12] */
	VCI_IN2_IRQn = 124,	/* GIRQ21 b[13] */
	VCI_IN3_IRQn = 125,	/* GIRQ21 b[14] */
	/* reserved 126 - 128 */
	PS2_0A_WAKE_IRQn = 129,	/* GIRQ21 b[18] */
	PS2_0B_WAKE_IRQn = 130,	/* GIRQ21 b[19] */
	/* reserved gap 131 */
	PS2_1B_WAKE_IRQn = 132,	/* GIRQ21 b[21] */
	/* reserved gap 133 - 134 */
	KEYSCAN_IRQn = 135,	/* GIRQ21 b[25] */
	B16TMR0_IRQn = 136,	/* GIRQ23 b[0] */
	B16TMR1_IRQn = 137,	/* GIRQ23 b[1] */
	/* reserved gap 138 - 139 */
	B32TMR0_IRQn = 140,	/* GIRQ23 b[4] */
	B32TMR1_IRQn = 141,	/* GIRQ23 b[5] */
	/* reserved 142 - 145 */
	CCT_IRQn = 146,	/* GIRQ18 b[20] */
	CCT_CAP0_IRQn = 147,	/* GIRQ18 b[21] */
	CCT_CAP1_IRQn = 148,	/* GIRQ18 b[22] */
	CCT_CAP2_IRQn = 149,	/* GIRQ18 b[23] */
	CCT_CAP3_IRQn = 150,	/* GIRQ18 b[24] */
	CCT_CAP4_IRQn = 151,	/* GIRQ18 b[25] */
	CCT_CAP5_IRQn = 152,	/* GIRQ18 b[26] */
	CCT_CMP0_IRQn = 153,	/* GIRQ18 b[27] */
	CCT_CMP1_IRQn = 154,	/* GIRQ18 b[28] */
	EEPROM_CTRL_IRQn = 155,	/* GIRQ18 b[13] */
	ESPI_VWIRE_IRQn = 156,	/* GIRQ19 b[8] */
	/* reserved gap 157 */
	SMB4_IRQn = 158,	/* GIRQ13 b[4] */
	TACH3_IRQn = 159,	/* GIRQ17 b[4] */
	CEC_IRQn = 160,	/* GIRQ17 b[5] */
	SGPIOCtrl0_IRQn = 161,	/* GIRQ18 b[14] */
	SGPIOCtrl1_IRQn = 162,	/* GIRQ18 b[15] */
	SGPIOCtrl2_IRQn = 163,	/* GIRQ18 b[16] */
	SGPIOCtrl3_IRQn = 164,	/* GIRQ18 b[17] */
	/* reserved gap 165 */
	SAF_DONE_IRQn = 166,	/* GIRQ19 b[9] */
	SAF_ERR_IRQn = 167,	/* GIRQ19 b[10] */
	I2C0_IRQn = 168,	/* GIRQ13 b[5] */
	I2C1_IRQn = 169,	/* GIRQ13 b[6] */
	I2C2_IRQn = 170,	/* GIRQ13 b[7] */
	WDT_IRQn = 171,	/* GIRQ21 b[2] */
	GLUE_IRQn = 172,	/* GIRQ23 b[26] */
	OTP_READY_IRQn = 173,	/* GIRQ20 b[3] */
	MAX_IRQn = 174
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Arm Cortex-M4 Processor and Core Peripherals  =========================== */

#define __CM4_REV                 0x0201	/*!< Core Revision r2p1 */

#define __MPU_PRESENT             1	/*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT            1	/*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS          3	/*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0	/*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0	/*!< Set to 1 if FPU is present */
#define __FPU_DP                  0	/*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT          0	/*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0	/*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT            0	/*!< Set to 1 if DTCM is present */

/** @} *//* End of group Configuration_of_CMSIS */

#include "core_cm4.h"		/*!< Arm Cortex-M4 processor and core peripherals */

/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

/* ======================================================================== */
/* ================   Device Specific Peripheral Section   ================ */
/* ======================================================================== */

/** @addtogroup MEC1501_Peripheral_peripherals
  * @{
  */

/*@}*//* end of group MEC15xx_Peripherals */

/* =========================================  End of section using anonymous unions  ========================================= */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

/* =========================================================================*/
/* ================ Device Specific Peripheral Address Map ================ */
/* =========================================================================*/

/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

/* Peripheral and SRAM base address */
#define CODE_SRAM_BASE          0x000e0000u	/*!< (CODE SRAM ) Base Address */
#define DATA_SRAM_BASE          0x00118000u	/*!< (DATA SRAM ) Base Address */
#define PERIPH_BASE             0x40000000u	/*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define WDT_BASE            (PERIPH_BASE + 0x0400u)	/*!< (WDT0   )  Base Address */
#define B16TMR0_BASE        (PERIPH_BASE + 0x0c00u)	/*!< (B16TMR0 ) Base Address */
#define B16TMR1_BASE        (PERIPH_BASE + 0x0c20u)	/*!< (B16TMR1 ) Base Address */
#define B32TMR0_BASE        (PERIPH_BASE + 0x0c80u)	/*!< (B32TMR0 ) Base Address */
#define B32TMR1_BASE        (PERIPH_BASE + 0x0ca0u)	/*!< (B32TMR1 ) Base Address */
#define CCT_BASE            (PERIPH_BASE + 0x1000u)	/*!< (CCT0 ) Base Address */
#define DMA_BASE            (PERIPH_BASE + 0x2400u)	/*!< (DMA ) Base Address */
#define DMA_CHAN_BASE(n)    (DMA_BASE + (((n)+1)<<6))
#define DMA_CH0_BASE        (DMA_BASE + 0x0040u)	/*!< (DMA Chan 00 ) Base Address */
#define DMA_CH1_BASE        (DMA_BASE + 0x0080u)	/*!< (DMA Chan 01 ) Base Address */
#define DMA_CH2_BASE        (DMA_BASE + 0x00c0u)	/*!< (DMA Chan 02 ) Base Address */
#define DMA_CH3_BASE        (DMA_BASE + 0x0100u)	/*!< (DMA Chan 03 ) Base Address */
#define DMA_CH4_BASE        (DMA_BASE + 0x0140u)	/*!< (DMA Chan 04 ) Base Address */
#define DMA_CH5_BASE        (DMA_BASE + 0x0180u)	/*!< (DMA Chan 05 ) Base Address */
#define DMA_CH6_BASE        (DMA_BASE + 0x01c0u)	/*!< (DMA Chan 06 ) Base Address */
#define DMA_CH7_BASE        (DMA_BASE + 0x0200u)	/*!< (DMA Chan 07 ) Base Address */
#define DMA_CH8_BASE        (DMA_BASE + 0x0240u)	/*!< (DMA Chan 08 ) Base Address */
#define DMA_CH9_BASE        (DMA_BASE + 0x0280u)	/*!< (DMA Chan 09 ) Base Address */
#define DMA_CH10_BASE       (DMA_BASE + 0x02c0u)	/*!< (DMA Chan 10 ) Base Address */
#define DMA_CH11_BASE       (DMA_BASE + 0x0300u)	/*!< (DMA Chan 11 ) Base Address */
#define EEPROM_CTRL_BASE    (PERIPH_BASE + 0x2c00u)	/*!< (EEPROM_CTRL ) Base Address */
#define PROCHOT_BASE        (PERIPH_BASE + 0x3400u)	/*!< (PROCHOT ) Base Address */
#define SMB_BASE(n)         (PERIPH_BASE + 0x4000u + ((n)<<10))
#define SMB0_BASE           (PERIPH_BASE + 0x4000u)	/*!< (SMB0 ) Base Address */
#define SMB1_BASE           (PERIPH_BASE + 0x4400u)	/*!< (SMB1 ) Base Address */
#define SMB2_BASE           (PERIPH_BASE + 0x4800u)	/*!< (SMB2 ) Base Address */
#define SMB3_BASE           (PERIPH_BASE + 0x4c00u)	/*!< (SMB3 ) Base Address */
#define SMB4_BASE           (PERIPH_BASE + 0x5000u)	/*!< (SMB4 ) Base Address */
#define I2C_BASE(n)         (PERIPH_BASE + 0x5100u + ((n)<<8))
#define I2C0_BASE           (PERIPH_BASE + 0x5100u)	/*!< (I2C0 ) Base Address */
#define I2C1_BASE           (PERIPH_BASE + 0x5200u)	/*!< (I2C1 ) Base Address */
#define I2C2_BASE           (PERIPH_BASE + 0x5300u)	/*!< (I2C2 ) Base Address */
#define PWM_BASE(n)         (PERIPH_BASE + 0x5800u + ((n)<<4))
#define PWM0_BASE           (PERIPH_BASE + 0x5800u)	/*!< (PWM0 ) Base Address */
#define PWM1_BASE           (PERIPH_BASE + 0x5810u)	/*!< (PWM1 ) Base Address */
#define PWM2_BASE           (PERIPH_BASE + 0x5820u)	/*!< (PWM2 ) Base Address */
#define PWM3_BASE           (PERIPH_BASE + 0x5830u)	/*!< (PWM3 ) Base Address */
#define PWM4_BASE           (PERIPH_BASE + 0x5840u)	/*!< (PWM4 ) Base Address */
#define PWM5_BASE           (PERIPH_BASE + 0x5850u)	/*!< (PWM5 ) Base Address */
#define PWM6_BASE           (PERIPH_BASE + 0x5860u)	/*!< (PWM6 ) Base Address */
#define PWM7_BASE           (PERIPH_BASE + 0x5870u)	/*!< (PWM7 ) Base Address */
#define PWM8_BASE           (PERIPH_BASE + 0x5880u)	/*!< (PWM8 ) Base Address */
#define TACH_BASE(n)        (PERIPH_BASE + 0x6000u + ((n)<<4))
#define TACH0_BASE          (PERIPH_BASE + 0x6000u)	/*!< (TACH0 ) Base Address */
#define TACH1_BASE          (PERIPH_BASE + 0x6010u)	/*!< (TACH1 ) Base Address */
#define TACH2_BASE          (PERIPH_BASE + 0x6020u)	/*!< (TACH2 ) Base Address */
#define TACH3_BASE          (PERIPH_BASE + 0x6030u)	/*!< (TACH3 ) Base Address */
#define PECI_BASE           (PERIPH_BASE + 0x6400u)	/*!< (PECI ) Base Address */
#define HDMI_CEC_BASE       (PERIPH_BASE + 0x6800u)	/*!< (HDMI_CEC ) Base Address */
#define SPIP_BASE           (PERIPH_BASE + 0x7000u)	/*!< (SPIP ) Base Address */
#define RTMR_BASE           (PERIPH_BASE + 0x7400u)	/*!< (RTMR ) Base Address */
#define ADC_BASE            (PERIPH_BASE + 0x7c00u)	/*!< (ADC ) Base Address */
#define TFDP_BASE           (PERIPH_BASE + 0x8c00u)	/*!< (TFDP ) Base Address */
#define PS2_0_BASE          (PERIPH_BASE + 0x9000u)	/*!< (PS2 0 ) Base Address */
#define PS2_1_BASE          (PERIPH_BASE + 0x9040u)	/*!< (PS2 1 ) Base Address */
#define HTMR0_BASE          (PERIPH_BASE + 0x9800u)	/*!< (HTMR0 ) Base Address */
#define HTMR1_BASE          (PERIPH_BASE + 0x9820u)	/*!< (HTMR1 ) Base Address */
#define KEYSCAN_BASE        (PERIPH_BASE + 0x9c00u)	/*!< (KEYSCAN ) Base Address */
#define VBATR_BASE          (PERIPH_BASE + 0xa400u)	/*!< (VBATR ) Base Address */
#define VBATM_BASE          (PERIPH_BASE + 0xa800u)	/*!< (VBATM ) Base Address */
#define WKTMR_BASE          (PERIPH_BASE + 0xac80u)	/*!< (WKTMR ) Base Address */
#define VCI_BASE            (PERIPH_BASE + 0xae00u)	/*!< (VCI ) Base Address */
#define LED0_BASE           (PERIPH_BASE + 0xb800u)	/*!< (BBLED0 ) Base Address */
#define LED1_BASE           (PERIPH_BASE + 0xb900u)	/*!< (BBLED1 ) Base Address */
#define LED2_BASE           (PERIPH_BASE + 0xba00u)	/*!< (BBLED2 ) Base Address */
#define ECIA_BASE           (PERIPH_BASE + 0xe000u)	/*!< (ECIA ) Base Address */
#define ECS_BASE            (PERIPH_BASE + 0xfc00u)	/*!< (ECS ) Base Address */
#define QMSPI_BASE          (PERIPH_BASE + 0x70000u)	/*!< (QMSPI0 ) Base Address */
#define PCR_BASE            (PERIPH_BASE + 0x80100u)	/*!< (PCR ) Base Address */
#define GPIO_BASE           (PERIPH_BASE + 0x81000u)	/*!< (GPIO ) Base Address */
#define GPIO_CTRL_BASE      (GPIO_BASE)	/*!< (GPIO ) Control Base Address */
#define GPIO_PARIN_BASE     (GPIO_BASE + 0x0300u)	/*!< (GPIO Parallel I/O) Base Address */
#define GPIO_PAROUT_BASE    (GPIO_BASE + 0x0380u)	/*!< (GPIO Parallel I/O) Base Address */
#define GPIO_LOCK_BASE      (GPIO_BASE + 0x03e8u)	/*!< (GPIO Lock) Base Address */
#define GPIO_CTRL2_BASE     (GPIO_BASE + 0x0500u)	/*!< (GPIO ) Control2 Base Address */
#define OTP_BASE            (PERIPH_BASE + 0x82000u)	/*!< (OTP ) Base Address */
#define MBOX_BASE           (PERIPH_BASE + 0xf0000u)	/*!< (MBOX ) Base Address */
#define KBC_BASE            (PERIPH_BASE + 0xf0400u)	/*!< (KBC ) Base Address */
#define ACPI_EC_BASE(n)     (PERIPH_BASE + 0xf0800u + ((n)<<10))
#define ACPI_EC_0_BASE      (PERIPH_BASE + 0xf0800u)	/*!< (ACPI EC0 ) Base Address */
#define ACPI_EC_1_BASE      (PERIPH_BASE + 0xf0c00u)	/*!< (ACPI EC1 ) Base Address */
#define ACPI_EC_2_BASE      (PERIPH_BASE + 0xf1000u)	/*!< (ACPI EC2 ) Base Address */
#define ACPI_EC_3_BASE      (PERIPH_BASE + 0xf1400u)	/*!< (ACPI EC3 ) Base Address */
#define ACPI_PM1_BASE       (PERIPH_BASE + 0xf1c00u)	/*!< (ACPI PM1 ) Base Address */
#define PORT92_BASE         (PERIPH_BASE + 0xf2000u)	/*!< (PORT92 ) Base Address */
#define UART_BASE(n)        (PERIPH_BASE + 0xf2400u + ((n)<<10))
#define UART0_BASE          (PERIPH_BASE + 0xf2400u)	/*!< (UART0 ) Base Address */
#define UART1_BASE          (PERIPH_BASE + 0xf2800u)	/*!< (UART1 ) Base Address */
#define UART2_BASE          (PERIPH_BASE + 0xf2c00u)	/*!< (UART2 ) Base Address */
#define ESPI_IO_BASE        (PERIPH_BASE + 0xf3400u)	/*!< (ESPI IO Component) Base Address */
#define ESPI_IO_PC_BASE     ((ESPI_IO_BASE) + 0x100u)	/*!< (ESPI IO Peripheral Channel) Base Address */
#define ESPI_IO_HOST_BAR_BASE ((ESPI_IO_BASE) + 0x120u)	/*!< (ESPI IO Host IO BAR) Base Address */
#define ESPI_IO_LTR_BASE    ((ESPI_IO_BASE) + 0x220u)	/*!< (ESPI IO LTR) Base Address */
#define ESPI_IO_OOB_BASE    ((ESPI_IO_BASE) + 0x240u)	/*!< (ESPI IO Out-of-Band Channel) Base Address */
#define ESPI_IO_FC_BASE     ((ESPI_IO_BASE) + 0x280u)	/*!< (ESPI IO Flash Channel) Base Address */
#define ESPI_IO_CAP_BASE    ((ESPI_IO_BASE) + 0x2b0u)	/*!< (ESPI IO Capabilities) Base Address */
#define ESPI_IO_EC_BAR_BASE ((ESPI_IO_BASE) + 0x330u)	/*!< (ESPI IO EC IO BAR) Base Address */
#define ESPI_IO_VW_BASE     ((ESPI_IO_BASE) + 0x2b0u)	/*!< (ESPI IO EC IO VW registers) Base Address */
#define ESPI_IO_SIRQ_BASE   ((ESPI_IO_BASE) + 0x3a0u)	/*!< (ESPI IO Seril IRQ registers) Base Address */

#define ESPI_MEM_BASE       (PERIPH_BASE + 0xf3800u)	/*!< (ESPI Memory Component) Base Address */
#define ESPI_MEM_EC_BAR_BASE ((ESPI_MEM_BASE) + 0x0130u)	/*!< (ESPI Logical Device Memory BAR EC */
#define ESPI_MEM_HOST_BAR_BASE ((ESPI_MEM_BASE) + 0x0330u)	/*!< (ESPI Logical Device Memory BAR Host */
#define ESPI_MEM_SRAM_EC_BAR_BASE ((ESPI_MEM_BASE) + 0x01a0u)	/*!< (ESPI Memory SRAM BAR EC */
#define ESPI_MEM_SRAM_HOST_BAR_BASE ((ESPI_MEM_BASE) + 0x03a0u)	/*!< (ESPI Memory SRAM BAR Host */
#define ESPI_MEM_BM_BASE    ((ESPI_MEM_BASE) + 0x0200u)	/*!< (ESPI Memory Component Bus Master) Base Address */

#define EMI0_BASE           (PERIPH_BASE + 0xf4000u)	/*!< (EMI0 ) Base Address */
#define EMI1_BASE           (PERIPH_BASE + 0xf4400u)	/*!< (EMI1 ) Base Address */

#define RTC_BASE            (PERIPH_BASE + 0xf5000u)	/*!< (RTC ) Base Address */

#define P80CAP0_BASE        (PERIPH_BASE + 0xf8000u)	/*!< (P80CAP0 ) Base Address */
#define P80CAP1_BASE        (PERIPH_BASE + 0xf8400u)	/*!< (P80CAP1 ) Base Address */

#define ESPI_VW_BASE        (PERIPH_BASE + 0xf9c00u)	/*!< (ESPI VW Component) Base Address */
#define ESPI_SMVW_BASE      (ESPI_VW_BASE + 0x200u)	/*!< (ESPI VW Component Slave-to-Master) Base Address */

#define GCFG_BASE           (PERIPH_BASE + 0xfff00u)	/*!< (GCFG ) Base Address */

#define DELAY_US_BASE (0x10000000u) /*!< (1 us Delay register) Base Address */

/** @} *//* End of group Device_Peripheral_peripheralAddr */

#define MCHP_ACMP_INSTANCES 1
#define MCHP_ACPI_EC_INSTANCES 4
#define MCHP_ACPI_PM1_INSTANCES 1
#define MCHP_ADC_INSTANCES 1
#define MCHP_BTMR16_INSTANCES 2
#define MCHP_BTMR32_INSTANCES 2
#define MCHP_CCT_INSTANCES 1
#define MCHP_CTMR_INSTANCES 0
#define MCHP_DMA_INSTANCES 1
#define MCHP_ECIA_INSTANCES 1
#define MCHP_EMI_INSTANCES 2
#define MCHP_HDMI_CEC_INSTANCES 1
#define MCHP_HTMR_INSTANCES 2
#define MCHP_I2C_INSTANCES 3
#define MCHP_I2C_SMB_INSTANCES 5
#define MCHP_LED_INSTANCES 3
#define MCHP_MBOX_INSTANCES 1
#define MCHP_OTP_INSTANCES 1
#define MCHP_P80CAP_INSTANCES 2
#define MCHP_PECI_INSTANCES 1
#define MCHP_PROCHOT_INSTANCES 1
#define MCHP_PS2_INSTANCES 2
#define MCHP_PWM_INSTANCES 9
#define MCHP_QMSPI_INSTANCES 1
#define MCHP_RCID_INSTANCES 3
#define MCHP_RPMFAN_INSTANCES 0
#define MCHP_RTC_INSTANCES 1
#define MCHP_RTMR_INSTANCES 1
#define MCHP_SPIP_INSTANCES 1
#define MCHP_TACH_INSTANCES 4
#define MCHP_TFDP_INSTANCES 1
#define MCHP_UART_INSTANCES 3
#define MCHP_WDT_INSTANCES 1
#define MCHP_WKTMR_INSTANCES 1

#define MCHP_ACMP_CHANNELS 2
#define MCHP_ADC_CHANNELS 8
#define MCHP_BGPO_GPIO_PINS 3
#define MCHP_DMA_CHANNELS 12
#define MCHP_GIRQS 19
#define MCHP_GPIO_PINS 128
#define MCHP_GPIO_PORTS 6
#define MCHP_GPTP_PORTS 3
#define MCHP_I2C_SMB_PORTS 15
#define MCHP_I2C_PORTMAP 0xffffu;
#define MCHP_QMSPI_PORTS 3
#define MCHP_PS2_PORTS 2
#define MCHP_VCI_IN_PINS 4
#define MCHP_VCI_OUT_PINS 1
#define MCHP_VCI_OVRD_IN_PINS 0

#include "component/acpi_ec.h"
#include "component/adc.h"
#include "component/dma.h"
#include "component/ecia.h"
#include "component/ecs.h"
#include "component/gpio.h"
#include "component/emi.h"
#include "component/espi_io.h"
#include "component/espi_mem.h"
#include "component/espi_saf.h"
#include "component/espi_vw.h"
#include "component/global_cfg.h"
#include "component/hdmi_cec.h"
#include "component/i2c.h"
#include "component/kbc.h"
#include "component/keyscan.h"
#include "component/led.h"
#include "component/mailbox.h"
#include "component/pcr.h"
#include "component/peci.h"
#include "component/port80cap.h"
#include "component/port92.h"
#include "component/prochot.h"
#include "component/ps2_ctrl.h"
#include "component/pwm.h"
#include "component/qmspi.h"
#include "component/rtc.h"
#include "component/smb.h"
#include "component/spi_periph.h"
#include "component/tach.h"
#include "component/tfdp.h"
#include "component/timer.h"
#include "component/uart.h"
#include "component/vbat.h"
#include "component/wdt.h"

/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define WDT_REGS        ((WDT_Type *) WDT_BASE)
#define B16TMR0_REGS    ((BTMR_Type *) B16TMR0_BASE)
#define B16TMR1_REGS    ((BTMR_Type *) B16TMR1_BASE)
#define B32TMR0_REGS    ((BTMR_Type *) B32TMR0_BASE)
#define B32TMR1_REGS	((BTMR_Type *) B32TMR1_BASE)
#define CCT_REGS	((CCT_Type *) (CCT_BASE))

#define DMAM_REGS       ((DMAM_Type *) DMA_BASE)
/* Individual DMA channels */
#define DMA0_REGS       ((DMA_CHAN_ALU_Type *)(DMA_CHAN_BASE(0)))
#define DMA1_REGS       ((DMA_CHAN_ALU_Type *)(DMA_CHAN_BASE(1)))
#define DMA2_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(2)))
#define DMA3_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(3)))
#define DMA4_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(4)))
#define DMA5_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(5)))
#define DMA6_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(6)))
#define DMA7_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(7)))
#define DMA8_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(8)))
#define DMA9_REGS       ((DMA_CHAN_Type *)(DMA_CHAN_BASE(9)))
#define DMA10_REGS      ((DMA_CHAN_Type *)(DMA_CHAN_BASE(10)))
#define DMA11_REGS      ((DMA_CHAN_Type *)(DMA_CHAN_BASE(11)))

#define PROCHOT_REGS	((PROCHOT_Type *) PROCHOT_BASE)

#define SMB0_REGS       ((I2C_SMB_Type *) SMB0_BASE)
#define SMB1_REGS       ((I2C_SMB_Type *) SMB1_BASE)
#define SMB2_REGS       ((I2C_SMB_Type *) SMB2_BASE)
#define SMB3_REGS       ((I2C_SMB_Type *) SMB3_BASE)
#define SMB4_REGS       ((I2C_SMB_Type *) SMB4_BASE)

#define PWM0_REGS	((PWM_Type *) PWM0_BASE)
#define PWM1_REGS	((PWM_Type *) PWM1_BASE)
#define PWM2_REGS	((PWM_Type *) PWM2_BASE)
#define PWM3_REGS	((PWM_Type *) PWM3_BASE)
#define PWM4_REGS	((PWM_Type *) PWM4_BASE)
#define PWM5_REGS	((PWM_Type *) PWM5_BASE)
#define PWM6_REGS	((PWM_Type *) PWM6_BASE)
#define PWM7_REGS	((PWM_Type *) PWM7_BASE)
#define PWM8_REGS	((PWM_Type *) PWM8_BASE)

#define TACH0_REGS	((TACH_Type *) TACH0_BASE)
#define TACH1_REGS	((TACH_Type *) TACH1_BASE)
#define TACH2_REGS	((TACH_Type *) TACH2_BASE)
#define TACH3_REGS	((TACH_Type *) TACH3_BASE)

#define PECI_REGS	((PECI_Type *) PECI_BASE)

#define HDMI_CEC_REGS	((HDMI_CEC_Type *) HDMI_CEC_BASE)

#define SPIP_REGS	((SPIP_Type *) SPIP_BASE)

#define RTMR_REGS       ((RTMR_Type *) RTMR_BASE)

#define ADC_REGS	((ADC_Type *) ADC_BASE)

#define TFDP_REGS	((TFDP_Type *) TFDP_BASE)

#define PS2_0_REGS	((PS2_Type *) PS2_0_BASE)
#define PS2_1_REGS	((PS2_Type *) PS2_1_BASE)

#define HTMR0_REGS      ((HTMR_Type *) HTMR0_BASE)
#define HTMR1_REGS      ((HTMR_Type *) HTMR1_BASE)

#define KSCAN_REGS      ((KSCAN_Type *)(KEYSCAN_BASE))

#define VBATR_REGS      ((VBATR_Type *) VBATR_BASE)
#define VBATM_REGS      ((VBATM_Type *) VBATM_BASE)
#define WKTMR_REGS      ((WKTMR_Type *) WKTMR_BASE)

#define VCI_REGS	((VCI_Type *) VCI_BASE)

#define LED0_REGS       ((LED_Type *) LED0_BASE)
#define LED1_REGS       ((LED_Type *) LED1_BASE)
#define LED2_REGS       ((LED_Type *) LED2_BASE)

#define ECIA_REGS       ((ECIA_Type *) ECIA_BASE)
#define GIRQ08_REGS     ((GIRQ_Type *) ECIA_BASE)
#define GIRQ09_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x14))
#define GIRQ10_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x28))
#define GIRQ11_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x3C))
#define GIRQ12_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x50))
#define GIRQ13_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x64))
#define GIRQ14_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x78))
#define GIRQ15_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x8C))
#define GIRQ16_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0xA0))
#define GIRQ17_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0xB4))
#define GIRQ18_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0xC8))
#define GIRQ19_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0xDC))
#define GIRQ20_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0xF0))
#define GIRQ21_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x104))
#define GIRQ22_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x118))
#define GIRQ23_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x12C))
#define GIRQ24_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x140))
#define GIRQ25_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x154))
#define GIRQ26_REGS     ((GIRQ_Type *) ((ECIA_BASE) + 0x168))

#define ECS_REGS        ((ECS_Type *) ECS_BASE)

#define QMSPI_REGS      ((QMSPI_Type *) QMSPI_BASE)

#define PCR_REGS        ((PCR_Type *) PCR_BASE)

#define GPIO_CTRL_REGS      ((GPIO_CTRL_Type *)(GPIO_CTRL_BASE))
#define GPIO_CTRL2_REGS     ((GPIO_CTRL2_Type *)(GPIO_CTRL2_BASE))
#define GPIO_PARIN_REGS     ((GPIO_PARIN_Type *)(GPIO_PARIN_BASE))
#define GPIO_PAROUT_REGS    ((GPIO_PAROUT_Type *)(GPIO_PAROUT_BASE))
#define GPIO_LOCK_REGS      ((GPIO_LOCK_Type *)(GPIO_LOCK_BASE))

#define MBOX_REGS       ((MBOX_Type *)(MBOX_BASE))

#define KBC_REGS        ((KBC_Type *)(KBC_BASE))

#define ACPI_EC_0_REGS  ((ACPI_EC_Type *)(ACPI_EC_0_BASE))
#define ACPI_EC_1_REGS  ((ACPI_EC_Type *)(ACPI_EC_1_BASE))
#define ACPI_EC_2_REGS  ((ACPI_EC_Type *)(ACPI_EC_2_BASE))
#define ACPI_EC_3_REGS  ((ACPI_EC_Type *)(ACPI_EC_3_BASE))

#define ACPI_PM1_REGS	((ACPI_PM1_Type *) ACPI_PM1_BASE)

#define PORT92_REGS     ((PORT92_Type *)(PORT92_BASE))

#define UART0_REGS      ((UART_Type *) UART0_BASE)
#define UART1_REGS      ((UART_Type *) UART1_BASE)
#define UART2_REGS      ((UART_Type *) UART2_BASE)

#define ESPI_PC_REGS        ((ESPI_IO_PC_Type *)(ESPI_IO_PC_BASE))
#define ESPI_HIO_BAR_REGS   ((ESPI_IO_BAR_HOST_Type *)(ESPI_IO_HOST_BAR_BASE))
#define ESPI_LTR_REGS       ((ESPI_IO_LTR_Type *)(ESPI_IO_LTR_BASE))
#define ESPI_OOB_REGS       ((ESPI_IO_OOB_Type *)(ESPI_IO_OOB_BASE))
#define ESPI_FC_REGS        ((ESPI_IO_FC_Type *)(ESPI_IO_FC_BASE))
#define ESPI_CAP_REGS       ((ESPI_IO_CAP_Type *)(ESPI_IO_CAP_BASE))
#define ESPI_EIO_BAR_REGS   ((ESPI_IO_BAR_EC_Type *)(ESPI_IO_EC_BAR_BASE))
#define ESPI_SIRQ_REGS      ((ESPI_IO_SIRQ_Type *)(ESPI_IO_SIRQ_BASE))

#define ESPI_MEM_EBAR_REGS  ((ESPI_MEM_BAR_EC_Type *)(ESPI_MEM_EC_BAR_BASE))
#define ESPI_MEM_HBAR_REGS  ((ESPI_MEM_BAR_HOST_Type *)(ESPI_MEM_HOST_BAR_BASE))

#define ESPI_MEM_SRAM_EBAR_REGS \
	((ESPI_MEM_SRAM_BAR_EC_Type *)(ESPI_MEM_SRAM_EC_BAR_BASE))
#define ESPI_MEM_SRAM_HBAR_REGS \
	((ESPI_MEM_SRAM_BAR_HOST_Type *)(ESPI_MEM_SRAM_HOST_BAR_BASE))

#define ESPI_MEM_BM_REGS  ((ESPI_MEM_BM_Type *)(ESPI_MEM_BM_BASE))

/* eSPI Virtual Wire registers in IO component */
#define ESPI_IO_VW_REGS      ((ESPI_IO_VW_Type *) (ESPI_IO_VW_BASE))
/* eSPI Virtual Wire registers for each group of 4 VWires */
#define ESPI_M2S_VW_REGS    ((ESPI_M2S_VW_Type *) (ESPI_VW_BASE))
#define ESPI_S2M_VW_REGS    ((ESPI_S2M_VW_Type *) (ESPI_SMVW_BASE))

#define EMI0_REGS       ((EMI_Type *)(EMI0_BASE))
#define EMI1_REGS       ((EMI_Type *)(EMI0_BASE))

#define RTC_REGS	((RTC_Type *) RTC_BASE)

#define PORT80_CAP0_REGS	((PORT80_CAP_Type *)(P80CAP0_BASE))
#define PORT80_CAP1_REGS	((PORT80_CAP_Type *)(P80CAP1_BASE))

#define GLOBAL_CFG_REGS		((GLOBAL_CFG_Type *) GCFG_BASE)

/** @} *//* End of group MEC1501 */

/** @} *//* End of group MCHP */

#ifdef __cplusplus
}
#endif
#endif				/* MEC1501HSZ_H */
