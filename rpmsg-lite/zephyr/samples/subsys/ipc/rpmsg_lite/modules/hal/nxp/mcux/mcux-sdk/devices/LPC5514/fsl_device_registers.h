/*
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_LPC5514JBD100) || defined(CPU_LPC5514JBD64) || defined(CPU_LPC5514JEV59))

#define LPC5514_SERIES

/* CMSIS-style register definitions */
#include "LPC5514.h"
/* CPU specific feature definitions */
#include "LPC5514_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
