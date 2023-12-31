/*
 * Copyright (c) 2020 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Header with definitions for MCHP eSPI SAF registers
 */

#ifndef ESPI_SAF_H_
#define ESPI_SAF_H_

#include <stdint.h>

#define MCHP_ESPI_SAF_BASE_ADDR 0x40008000
#define MCHP_ESPI_SAF_COMM_BASE_ADDR 0x40071000

#define MCHP_ESPI_SAF_CS_MAX 2

/* Three TAG Map registers */
#define MCHP_ESPI_SAF_TAGMAP_MAX 3
/* 17 protection regions */
#define MCHP_ESPI_SAF_PR_MAX 17

/*
 * SAF SPI Opcoded and indices specifying start QMSPI descriptor for
 * each opcode. There is one register group per flash device.
 * OPA: read status1, resume, suspend, write enable
 * OPB: erase 4KB, erase 32KB, erase 64KB, page program
 * OPC: Fast Read Quad or Dual, N/A, continuous mode byte, read status 2
 * OP_DESCR: contains QMSPI descriptor indices for various opcode fields.
 */
struct mchp_espi_saf_op {
	volatile uint32_t OPA;
	volatile uint32_t OPB;
	volatile uint32_t OPC;
	volatile uint32_t OP_DESCR;
};

/*
 * SAF protection regions contain 4 32-bit registers:
 * Start address in 4KB units.
 * Limit address in 4KB units.
 * Write-erase eSPI Master bit-map.
 * Read access eSPI Master bit-map.
 */
struct mchp_espi_saf_pr {
	volatile uint32_t START;
	volatile uint32_t LIMIT;
	volatile uint32_t WEBM;
	volatile uint32_t RDBM;
};

/*
 * SAF configuration and control registers
 */
struct mchp_espi_saf {
		 uint32_t RSVD1[6];
	volatile uint32_t SAF_ECP_CMD;
	volatile uint32_t SAF_ECP_FLAR;
	volatile uint32_t SAF_ECP_START;
	volatile uint32_t SAF_ECP_BFAR;
	volatile uint32_t SAF_ECP_STATUS;
	volatile uint32_t SAF_ECP_INTEN;
	volatile uint32_t SAF_FL_CFG_SIZE_LIM;
	volatile uint32_t SAF_FL_CFG_THRH;
	volatile uint32_t SAF_FL_CFG_MISC;
	volatile uint32_t SAF_ESPI_MON_STATUS;
	volatile uint32_t SAF_ESPI_MON_INTEN;
	volatile uint32_t SAF_ECP_BUSY;
		 uint32_t RSVD2[1];
	struct mchp_espi_saf_op SAF_CS_OP[MCHP_ESPI_SAF_CS_MAX];
	volatile uint32_t SAF_FL_CFG_GEN_DESCR;
	volatile uint32_t SAF_PROT_LOCK;
	volatile uint32_t SAF_PROT_DIRTY;
	volatile uint32_t SAF_TAG_MAP[MCHP_ESPI_SAF_TAGMAP_MAX];
	struct mchp_espi_saf_pr SAF_PROT_RG[MCHP_ESPI_SAF_PR_MAX];
	volatile uint32_t SAF_POLL_TMOUT;
	volatile uint32_t SAF_POLL_INTRVL;
	volatile uint32_t SAF_SUS_RSM_INTRVL;
	volatile uint32_t SAF_CONSEC_RD_TMOUT;
	volatile uint16_t SAF_CS0_CFG_P2M;
	volatile uint16_t SAF_CS1_CFG_P2M;
	volatile uint32_t SAF_FL_CFG_SPM;
	volatile uint32_t SAF_SUS_CHK_DLY;
	volatile uint16_t SAF_CS0_CM_PRF;
	volatile uint16_t SAF_CS1_CM_PRF;
	volatile uint32_t SAF_DNX_PROT_BYP;
};
typedef struct mchp_espi_saf MCHP_SAF_HW_REGS;

#define MCHP_SAF_FL_CM_PRF_CS0_OFS	0x1b0
#define MCHP_SAF_FL_CM_PRF_CS1_OFS	0x1b2


#define MCHP_ESPI_SAF_BASE	0x40008000
#define MCHP_ESPI_SAF_COMM_BASE	0x40071000
#define MCHP_ESPI_SAF_COMM_MODE_OFS	0x2b8
#define MCHP_ESPI_SAF_COMM_MODE_ADDR	(MCHP_ESPI_SAF_COMM_BASE_ADDR + \
					 MCHP_ESPI_SAF_COMM_MODE_OFS)

/* SAF Protection region described by 4 32-bit registers. 17 regions */
#define MCHP_ESPI_SAF_PROT_MAX 17

/* SAF register structure pointer */
#define MCHP_SAF_REGS ((MCHP_SAF_HW_REGS *)(MCHP_ESPI_SAF_BASE_ADDR))

/* SAF Communication Mode register */
#define MCHP_SAF_COMM_MODE_REG \
	*(volatile uint32_t *)(MCHP_ESPI_SAF_COMM_MODE_ADDR)

/*
 * Interrupt connections
 * HW bug: SAF interrupts do not have direct NVIC connections.
 */
#define MCHP_SAF_GIRQ 18
#define MCHP_SAF_GIRQ_ECP_DONE_POS 9
#define MCHP_SAF_GIRQ_ERROR_POS 10
#define MCHP_SAF_GIRQ_ECP_DONE_BIT BIT(9)
#define MCHP_SAF_GIRQ_ERROR_BIT BIT(10)


/* Register bit definitions */

/* SAF EC Portal Command register */
#define MCHP_SAF_ECP_CMD_OFS		0x18
#define MCHP_SAF_ECP_CMD_MASK		0xff00ffff
#define MCHP_SAF_ECP_CMD_PUT_POS	0
#define MCHP_SAF_ECP_CMD_PUT_MASK	0xff
#define MCHP_SAF_ECP_CMD_PUT_FLASH_NP	0x0a
#define MCHP_SAF_ECP_CMD_CTYPE_POS	8
#define MCHP_SAF_ECP_CMD_CTYPE_READ0	0x00
#define MCHP_SAF_ECP_CMD_CTYPE_WRITE0	0x01
#define MCHP_SAF_ECP_CMD_CTYPE_ERASE0	0x02
#define MCHP_SAF_ECP_CMD_CTYPE_MAX0	0x03
#define MCHP_SAF_ECP_CMD_CTYPE_MASK	(0xff << MCHP_SAF_ECP_CMD_CTYPE_POS)
#define MCHP_SAF_ECP_CMD_CTYPE_READ	(0x00 << MCHP_SAF_ECP_CMD_CTYPE_POS)
#define MCHP_SAF_ECP_CMD_CTYPE_WRITE	(0x01 << MCHP_SAF_ECP_CMD_CTYPE_POS)
#define MCHP_SAF_ECP_CMD_CTYPE_ERASE	(0x02 << MCHP_SAF_ECP_CMD_CTYPE_POS)
#define MCHP_SAF_ECP_CMD_LEN_POS	24
#define MCHP_SAF_ECP_CMD_LEN_MASK0	0xff
#define MCHP_SAF_ECP_CMD_LEN_MASK	(0xff << MCHP_SAF_ECP_CMD_LEN_POS)
/* Read/Write request size (1 <= reqlen <= 64) bytes */
#define MCHP_SAF_ECP_CMD_RW_LEN_MIN	1
#define MCHP_SAF_ECP_CMD_RW_LEN_MAX	64
/* Only three erase sizes are supported encoded as */
#define MCHP_SAF_ECP_CMD_ERASE_4K (0x00 << MCHP_SAF_ECP_CMD_LEN_POS)
#define MCHP_SAF_ECP_CMD_ERASE_32K (0x01 << MCHP_SAF_ECP_CMD_LEN_POS)
#define MCHP_SAF_ECP_CMD_ERASE_64K (0x02 << MCHP_SAF_ECP_CMD_LEN_POS)

/* SAF EC Portal Flash Address register */
#define MCHP_SAF_ECP_FLAR_OFS	0x1c
#define MCHP_SAF_ECP_FLAR_MASK	0xffffffff

/* SAF EC Portal Start register */
#define MCHP_SAF_ECP_START_OFS	0x20
#define MCHP_SAF_ECP_START_MASK	0x01
#define MCHP_SAF_ECP_START	BIT(0)

/* SAF EC Portal Buffer Address register */
#define MCHP_SAF_ECP_BFAR_OFS	0x24
#define MCHP_SAF_ECP_BFAR_MASK	0xfffffffc

/* SAF EC Portal Status register */
#define MCHP_SAF_ECP_STS_OFS		0x28
#define MCHP_SAF_ECP_STS_MASK		0x1ff
#define MCHP_SAF_ECP_STS_ERR_MASK	0x1fc
#define MCHP_SAF_ECP_STS_DONE		BIT(0)
#define MCHP_SAF_ECP_STS_DONE_TST	BIT(1)
#define MCHP_SAF_ECP_STS_TMOUT		BIT(2)
#define MCHP_SAF_ECP_STS_OOR		BIT(3)
#define MCHP_SAF_ECP_STS_AV		BIT(4)
#define MCHP_SAF_ECP_STS_BND_4K		BIT(5)
#define MCHP_SAF_ECP_STS_ERSZ		BIT(6)
#define MCHP_SAF_ECP_STS_ST_OVFL	BIT(6)
#define MCHP_SAF_ECP_STS_BAD_REQ	BIT(8)

/* SAF EC Portal Interrupt Enable register */
#define MCHP_SAF_ECP_INTEN_OFS	0x2c
#define MCHP_SAF_ECP_INTEN_MASK	0x01
#define MCHP_SAF_ECP_INTEN_DONE	BIT(0)

/* SAF Flash Configuratin Size Limit register */
#define MCHP_SAF_FL_CFG_SIZE_LIM_OFS	0x30
#define MCHP_SAF_FL_CFG_SIZE_LIM_MASK	0xffffffff

/* SAF Flash Configuration Threshold register */
#define MCHP_SAF_FL_CFG_THRH_OFS	0x34
#define MCHP_SAF_FL_CFG_THRH_MASK	0xffffffff

/* SAF Flash Configuration Miscellaneous register */
#define MCHP_SAF_FL_CFG_MISC_OFS	0x38
#define MCHP_SAF_FL_CFG_MISC_MASK	0x000030f3
#define MCHP_SAF_FL_CFG_MISC_PFOE_MASK	0x03
#define MCHP_SAF_FL_CFG_MISC_PFOE_DFLT	0x00
#define MCHP_SAF_FL_CFG_MISC_PFOE_EXP	0x03
#define MCHP_SAF_FL_CFG_MISC_CS0_4BM	BIT(4)
#define MCHP_SAF_FL_CFG_MISC_CS1_4BM	BIT(5)
#define MCHP_SAF_FL_CFG_MISC_CS0_CPE	BIT(6)
#define MCHP_SAF_FL_CFG_MISC_CS1_CPE	BIT(7)
#define MCHP_SAF_FL_CFG_MISC_SAF_EN	BIT(12)
#define MCHP_SAF_FL_CFG_MISC_SAF_LOCK	BIT(13)

/* SAF eSPI Monitor Status register */
#define MCHP_SAF_ESPI_MON_STATUS_OFS	0x3c
#define MCHP_SAF_ESPI_MON_STATUS_MASK	0x1f
#define MCHP_SAF_ESPI_MON_STS_TMOUT	BIT(0)
#define MCHP_SAF_ESPI_MON_STS_OOR	BIT(1)
#define MCHP_SAF_ESPI_MON_STS_AV	BIT(2)
#define MCHP_SAF_ESPI_MON_STS_BND_4K	BIT(3)
#define MCHP_SAF_ESPI_MON_STS_ERSZ	BIT(4)

/* SAF eSPI Monitor Interrupt Enable register */
#define MCHP_SAF_ESPI_MON_INTEN_OFS	0x40
#define MCHP_SAF_ESPI_MON_INTEN_MASK	0x1f
#define MCHP_SAF_ESPI_MON_INTEN_TMOUT	BIT(0)
#define MCHP_SAF_ESPI_MON_INTEN_OOR	BIT(1)
#define MCHP_SAF_ESPI_MON_INTEN_AV	BIT(2)
#define MCHP_SAF_ESPI_MON_INTEN_BND_4K	BIT(3)
#define MCHP_SAF_ESPI_MON_INTEN_ERSZ	BIT(4)

/* SAF EC Portal Busy register */
#define MCHP_SAF_ECP_BUSY_OFS		0x44
#define MCHP_SAF_ECP_BUSY_MASK		0x01
#define MCHP_SAF_ECP_BUSY		BIT(0)

/* SAF CS0/CS1 Opcode A registers */
#define MCHP_SAF_CS0_OPA_OFS	0x4c
#define MCHP_SAF_CS1_OPA_OFS	0x5c
#define MCHP_SAF_CS_OPA_MASK	0xffffffff
#define MCHP_SAF_CS_OPA_WE_POS	0
#define MCHP_SAF_CS_OPA_WE_MASK	0xff
#define MCHP_SAF_CS_OPA_SUS_POS	8
#define MCHP_SAF_CS_OPA_SUS_MASK	(0xff << MCHP_SAF_CS_OPA_SUS_POS)
#define MCHP_SAF_CS_OPA_RSM_POS	16
#define MCHP_SAF_CS_OPA_RSM_MASK	(0xff << MCHP_SAF_CS_OPA_RSM_POS)
#define MCHP_SAF_CS_OPA_POLL1_POS	24
#define MCHP_SAF_CS_OPA_POLL1_MASK	(0xff << MCHP_SAF_CS_OPA_POLL1_POS)

/* SAF CS0/CS1 Opcode B registers */
#define MCHP_SAF_CS0_OPB_OFS	0x50
#define MCHP_SAF_CS1_OPB_OFS	0x60
#define MCHP_SAF_CS_OPB_OFS	0xffffffff
#define MCHP_SAF_CS_OPB_ER0_POS	0
#define MCHP_SAF_CS_OPB_ER0_MASK	0xff
#define MCHP_SAF_CS_OPB_ER1_POS	8
#define MCHP_SAF_CS_OPB_ER1_MASK	(0xff << MCHP_SAF_CS_OPB_ER1_POS)
#define MCHP_SAF_CS_OPB_ER2_POS	16
#define MCHP_SAF_CS_OPB_ER2_MASK	(0xff << MCHP_SAF_CS_OPB_ER2_POS)
#define MCHP_SAF_CS_OPB_PGM_POS	24
#define MCHP_SAF_CS_OPB_PGM_MASK	(0xff << MCHP_SAF_CS_OPB_PGM_POS)

/* SAF CS0/CS1 Opcode C registers */
#define MCHP_SAF_CS0_OPC_OFS	0x54
#define MCHP_SAF_CS1_OPC_OFS	0x64
#define MCHP_SAF_CS_OPC_MASK	0xffffffff
#define MCHP_SAF_CS_OPC_RD_POS		0
#define MCHP_SAF_CS_OPC_RD_MASK	0xff
#define MCHP_SAF_CS_OPC_MNC_POS		8
#define MCHP_SAF_CS_OPC_MNC_MASK	(0xff << MCHP_SAF_CS_OPC_MN_POS)
#define MCHP_SAF_CS_OPC_MC_POS		16
#define MCHP_SAF_CS_OPC_MC_MASK	(0xff << MCHP_SAF_CS_OPC_MC_POS)
#define MCHP_SAF_CS_OPC_POLL2_POS	24
#define MCHP_SAF_CS_OPC_POLL2_MASK	(0xff << MCHP_SAF_CS_OPC_POLL2_POS)

/* SAF CS0/CS1 registers */
#define MCHP_SAF_CS0_DESCR_OFS	0x58
#define MCHP_SAF_CS1_DESCR_OFS	0x68
#define MCHP_SAF_CS_DESCR_MASK	0x0000ff0f
#define MCHP_SAF_CS_DESCR_ENTC_POS	0
#define MCHP_SAF_CS_DESCR_ENTC_MASK	0x0f
#define MCHP_SAF_CS_DESCR_RDC_POS	8
#define MCHP_SAF_CS_DESCR_RDC_MASK	(0x0f << MCHP_SAF_CS_DESCR_RDC_POS)
#define MCHP_SAF_CS_DESCR_SZC_POS	12
#define MCHP_SAF_CS_DESCR_SZC_MASK	(0x0f << MCHP_SAF_CS_DESCR_SZC_POS)

/* SAF Flash Configuration General Descriptors register */
#define MCHP_SAF_FL_CFG_GEN_DESCR_OFS	0x6c
#define MCHP_SAF_FL_CFG_GEN_DESCR_MASK	0x0000ff0f
/* value for standard 16 descriptor programming */
#define MCHP_SAF_FL_CFG_GEN_DESCR_STD	0x0000ee0c
#define MCHP_SAF_FL_CFG_GEN_DESCR_EXC_POS	0
#define MCHP_SAF_FL_CFG_GEN_DESCR_EXC_MASK	0x0f
#define MCHP_SAF_FL_CFG_GEN_DESCR_POLL1_POS	8
#define MCHP_SAF_FL_CFG_GEN_DESCR_POLL1_MASK \
	(0x0f << MCHP_SAF_FL_CFG_GEN_DESCR_POLL1_POS)
#define MCHP_SAF_FL_CFG_GEN_DESCR_POLL2_POS	12
#define MCHP_SAF_FL_CFG_GEN_DESCR_POLL2_MASK \
	(0x0f << MCHP_SAF_FL_CFG_GEN_DESCR_POLL2_POS)

/* SAF Protection Lock register */
#define MCHP_SAF_PROT_LOCK_OFS		0x70
#define MCHP_SAF_PROT_LOCK_MASK	0x1ffff
#define MCHP_SAF_PROT_LOCK0	BIT(0)
#define MCHP_SAF_PROT_LOCK1	BIT(1)
#define MCHP_SAF_PROT_LOCK2	BIT(2)
#define MCHP_SAF_PROT_LOCK3	BIT(3)
#define MCHP_SAF_PROT_LOCK4	BIT(4)
#define MCHP_SAF_PROT_LOCK5	BIT(5)
#define MCHP_SAF_PROT_LOCK6	BIT(6)
#define MCHP_SAF_PROT_LOCK7	BIT(7)
#define MCHP_SAF_PROT_LOCK8	BIT(8)
#define MCHP_SAF_PROT_LOCK9	BIT(9)
#define MCHP_SAF_PROT_LOCK10	BIT(10)
#define MCHP_SAF_PROT_LOCK11	BIT(11)
#define MCHP_SAF_PROT_LOCK12	BIT(12)
#define MCHP_SAF_PROT_LOCK13	BIT(13)
#define MCHP_SAF_PROT_LOCK14	BIT(14)
#define MCHP_SAF_PROT_LOCK15	BIT(15)
#define MCHP_SAF_PROT_LOCK16	BIT(16)

/* SAF Protection Dirty register */
#define MCHP_SAF_PROT_DIRTY_OFS	0x74
#define MCHP_SAF_PROT_DIRTY_MASK	0x00fff
#define MCHP_SAF_PROT_DIRTY0	BIT(0)
#define MCHP_SAF_PROT_DIRTY1	BIT(1)
#define MCHP_SAF_PROT_DIRTY2	BIT(2)
#define MCHP_SAF_PROT_DIRTY3	BIT(3)
#define MCHP_SAF_PROT_DIRTY4	BIT(4)
#define MCHP_SAF_PROT_DIRTY5	BIT(5)
#define MCHP_SAF_PROT_DIRTY6	BIT(6)
#define MCHP_SAF_PROT_DIRTY7	BIT(7)
#define MCHP_SAF_PROT_DIRTY8	BIT(8)
#define MCHP_SAF_PROT_DIRTY9	BIT(9)
#define MCHP_SAF_PROT_DIRTY10	BIT(10)
#define MCHP_SAF_PROT_DIRTY11	BIT(11)

/* SAF Tag Map 0 register */
#define MCHP_SAF_TAG_MAP0_OFS		0x78
#define MCHP_SAF_TAG_MAP0_MASK		0x77777777
#define MCHP_SAF_TAG_MAP0_DFLT		0x23221100
#define MCHP_SAF_TAG_MAP0_STM0_POS	0
#define MCHP_SAF_TAG_MAP0_STM0_MASK	0x07
#define MCHP_SAF_TAG_MAP0_STM1_POS	4
#define MCHP_SAF_TAG_MAP0_STM1_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM1_POS)
#define MCHP_SAF_TAG_MAP0_STM2_POS	8
#define MCHP_SAF_TAG_MAP0_STM2_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM2_POS)
#define MCHP_SAF_TAG_MAP0_STM3_POS	12
#define MCHP_SAF_TAG_MAP0_STM3_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM3_POS)
#define MCHP_SAF_TAG_MAP0_STM4_POS	16
#define MCHP_SAF_TAG_MAP0_STM4_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM4_POS)
#define MCHP_SAF_TAG_MAP0_STM5_POS	20
#define MCHP_SAF_TAG_MAP0_STM5_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM5_POS)
#define MCHP_SAF_TAG_MAP0_STM6_POS	24
#define MCHP_SAF_TAG_MAP0_STM6_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM6_POS)
#define MCHP_SAF_TAG_MAP0_STM7_POS	28
#define MCHP_SAF_TAG_MAP0_STM7_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM7_POS)

/* SAF Tag Map 1 register */
#define MCHP_SAF_TAG_MAP1_OFS		0x7c
#define MCHP_SAF_TAG_MAP1_MASK		0x77777777
#define MCHP_SAF_TAG_MAP1_DFLT		0x77677767
#define MCHP_SAF_TAG_MAP1_STM8_POS	0
#define MCHP_SAF_TAG_MAP1_STM8_MASK	0x07
#define MCHP_SAF_TAG_MAP1_STM9_POS	4
#define MCHP_SAF_TAG_MAP1_STM9_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STM9_POS)
#define MCHP_SAF_TAG_MAP1_STMA_POS	8
#define MCHP_SAF_TAG_MAP1_STMA_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STMA_POS)
#define MCHP_SAF_TAG_MAP1_STMB_POS	12
#define MCHP_SAF_TAG_MAP1_STMB_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STMB_POS)
#define MCHP_SAF_TAG_MAP1_STMC_POS	16
#define MCHP_SAF_TAG_MAP1_STMC_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STMC_POS)
#define MCHP_SAF_TAG_MAP1_STMD_POS	20
#define MCHP_SAF_TAG_MAP1_STMD_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STMD_POS)
#define MCHP_SAF_TAG_MAP1_STME_POS	24
#define MCHP_SAF_TAG_MAP1_STME_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STME_POS)
#define MCHP_SAF_TAG_MAP1_STMF_POS	28
#define MCHP_SAF_TAG_MAP1_STMF_MASK	(0x07 << MCHP_SAF_TAG_MAP1_STMF_POS)

/* SAF Tag Map 2 register */
#define MCHP_SAF_TAG_MAP2_OFS		0x80
#define MCHP_SAF_TAG_MAP2_MASK		0x80000007
#define MCHP_SAF_TAG_MAP2_DFLT		0x00000005
#define MCHP_SAF_TAG_MAP2_SM_EC_POS	0
#define MCHP_SAF_TAG_MAP2_SM_EC_MASK	0x07
#define MCHP_SAF_TAG_MAP2_LOCK_POS	31
#define MCHP_SAF_TAG_MAP2_LOCK		BIT(31)

/* SAF Protection Region Start registers */
#define MCHP_SAF_PROT_RG0_START_OFS	0x84
#define MCHP_SAF_PROT_RG1_START_OFS	0x94
#define MCHP_SAF_PROT_RG2_START_OFS	0xa4
#define MCHP_SAF_PROT_RG3_START_OFS	0xb4
#define MCHP_SAF_PROT_RG4_START_OFS	0xc4
#define MCHP_SAF_PROT_RG5_START_OFS	0xd4
#define MCHP_SAF_PROT_RG6_START_OFS	0xe4
#define MCHP_SAF_PROT_RG7_START_OFS	0xf4
#define MCHP_SAF_PROT_RG8_START_OFS	0x104
#define MCHP_SAF_PROT_RG9_START_OFS	0x114
#define MCHP_SAF_PROT_RG10_START_OFS	0x124
#define MCHP_SAF_PROT_RG11_START_OFS	0x134
#define MCHP_SAF_PROT_RG12_START_OFS	0x144
#define MCHP_SAF_PROT_RG13_START_OFS	0x154
#define MCHP_SAF_PROT_RG14_START_OFS	0x164
#define MCHP_SAF_PROT_RG15_START_OFS	0x174
#define MCHP_SAF_PROT_RG16_START_OFS	0x184
#define MCHP_SAF_PROT_RG_START_MASK	0xfffff
#define MCHP_SAF_PROT_RG_START_DFLT	0x07fff

/* SAF Protection Region Limit registers */
#define MCHP_SAF_PROT_RG0_LIMIT_OFS	0x88
#define MCHP_SAF_PROT_RG1_LIMIT_OFS	0x98
#define MCHP_SAF_PROT_RG2_LIMIT_OFS	0xa8
#define MCHP_SAF_PROT_RG3_LIMIT_OFS	0xb8
#define MCHP_SAF_PROT_RG4_LIMIT_OFS	0xc8
#define MCHP_SAF_PROT_RG5_LIMIT_OFS	0xd8
#define MCHP_SAF_PROT_RG6_LIMIT_OFS	0xe8
#define MCHP_SAF_PROT_RG7_LIMIT_OFS	0xf8
#define MCHP_SAF_PROT_RG8_LIMIT_OFS	0x108
#define MCHP_SAF_PROT_RG9_LIMIT_OFS	0x118
#define MCHP_SAF_PROT_RG10_LIMIT_OFS	0x128
#define MCHP_SAF_PROT_RG11_LIMIT_OFS	0x138
#define MCHP_SAF_PROT_RG12_LIMIT_OFS	0x148
#define MCHP_SAF_PROT_RG13_LIMIT_OFS	0x158
#define MCHP_SAF_PROT_RG14_LIMIT_OFS	0x168
#define MCHP_SAF_PROT_RG15_LIMIT_OFS	0x178
#define MCHP_SAF_PROT_RG16_LIMIT_OFS	0x188
#define MCHP_SAF_PROT_RG_LIMIT_MASK	0xfffff
#define MCHP_SAF_PROT_RG_LIMIT_DFLT	0

/* SAF Protection Region Write Bitmap registers */
#define MCHP_SAF_PROT_RG0_WBM_OFS	0x8c
#define MCHP_SAF_PROT_RG1_WBM_OFS	0x9c
#define MCHP_SAF_PROT_RG2_WBM_OFS	0xac
#define MCHP_SAF_PROT_RG3_WBM_OFS	0xbc
#define MCHP_SAF_PROT_RG4_WBM_OFS	0xcc
#define MCHP_SAF_PROT_RG5_WBM_OFS	0xdc
#define MCHP_SAF_PROT_RG6_WBM_OFS	0xec
#define MCHP_SAF_PROT_RG7_WBM_OFS	0xfc
#define MCHP_SAF_PROT_RG8_WBM_OFS	0x10c
#define MCHP_SAF_PROT_RG9_WBM_OFS	0x11c
#define MCHP_SAF_PROT_RG10_WBM_OFS	0x12c
#define MCHP_SAF_PROT_RG11_WBM_OFS	0x13c
#define MCHP_SAF_PROT_RG12_WBM_OFS	0x14c
#define MCHP_SAF_PROT_RG13_WBM_OFS	0x15c
#define MCHP_SAF_PROT_RG14_WBM_OFS	0x16c
#define MCHP_SAF_PROT_RG15_WBM_OFS	0x17c
#define MCHP_SAF_PROT_RG16_WBM_OFS	0x18c
#define MCHP_SAF_PROT_RG_WBM_MASK	0xff
#define MCHP_SAF_PROT_RG_WBM0		BIT(0)
#define MCHP_SAF_PROT_RG_WBM1		BIT(1)
#define MCHP_SAF_PROT_RG_WBM2		BIT(2)
#define MCHP_SAF_PROT_RG_WBM3		BIT(3)
#define MCHP_SAF_PROT_RG_WBM4		BIT(4)
#define MCHP_SAF_PROT_RG_WBM5		BIT(5)
#define MCHP_SAF_PROT_RG_WBM6		BIT(6)
#define MCHP_SAF_PROT_RG_WBM7		BIT(7)

/* SAF Protection Region Read Bitmap registers */
#define MCHP_SAF_PROT_RG0_RBM_OFS	0x90
#define MCHP_SAF_PROT_RG1_RBM_OFS	0xa0
#define MCHP_SAF_PROT_RG2_RBM_OFS	0xb0
#define MCHP_SAF_PROT_RG3_RBM_OFS	0xc0
#define MCHP_SAF_PROT_RG4_RBM_OFS	0xd0
#define MCHP_SAF_PROT_RG5_RBM_OFS	0xe0
#define MCHP_SAF_PROT_RG6_RBM_OFS	0xf0
#define MCHP_SAF_PROT_RG7_RBM_OFS	0x100
#define MCHP_SAF_PROT_RG8_RBM_OFS	0x110
#define MCHP_SAF_PROT_RG9_RBM_OFS	0x120
#define MCHP_SAF_PROT_RG10_RBM_OFS	0x130
#define MCHP_SAF_PROT_RG11_RBM_OFS	0x140
#define MCHP_SAF_PROT_RG12_RBM_OFS	0x150
#define MCHP_SAF_PROT_RG13_RBM_OFS	0x160
#define MCHP_SAF_PROT_RG14_RBM_OFS	0x170
#define MCHP_SAF_PROT_RG15_RBM_OFS	0x180
#define MCHP_SAF_PROT_RG16_RBM_OFS	0x190
#define MCHP_SAF_PROT_RG_RBM_MASK	0xff
#define MCHP_SAF_PROT_RG_RBM0		BIT(0)
#define MCHP_SAF_PROT_RG_RBM1		BIT(1)
#define MCHP_SAF_PROT_RG_RBM2		BIT(2)
#define MCHP_SAF_PROT_RG_RBM3		BIT(3)
#define MCHP_SAF_PROT_RG_RBM4		BIT(4)
#define MCHP_SAF_PROT_RG_RBM5		BIT(5)
#define MCHP_SAF_PROT_RG_RBM6		BIT(6)
#define MCHP_SAF_PROT_RG_RBM7		BIT(7)

/* SAF Poll Timeout register */
#define MCHP_SAF_POLL_TMOUT_OFS	0x194
#define MCHP_SAF_POLL_TMOUT_MASK	0x3ffff
#define MCHP_SAF_POLL_TMOUT_5S		0x28000

/* SAF Poll Interval register */
#define MCHP_SAF_POLL_INTRVL_OFS	0x198
#define MCHP_SAF_POLL_INTRVL_MASK	0xffff

/* SAF Suspend Resume Interval register */
#define MCHP_SAF_SUS_RSM_INTRVL_OFS	0x19c
#define MCHP_SAF_SUS_RSM_INTRVL_MASK	0xffff

/* SAF Consecutive Read Timeout register */
#define MCHP_SAF_CRD_TMOUT_OFS	0x1a0
#define MCHP_SAF_CRD_TMOUT_MASK	0xfffff

/* SAF Flash CS0/CS1 Configuration Poll2 Mask registers */
#define MCHP_SAF_FL0_CFG_P2M_OFS	0x1a4
#define MCHP_SAF_FL1_CFG_P2M_OFS	0x1a6
#define MCHP_SAF_FL_CFG_P2M_MASK	0xffff

/* SAF Flash Configuration Special Mode register */
#define MCHP_SAF_FL_CFG_SPM_OFS	0x1a8
#define MCHP_SAF_FL_CFG_SPM_MASK	0x01
#define MCHP_SAF_FL_CFG_SPM_DIS_SUSP	BIT(0)

/* SAF Suspend Check Delay register */
#define MCHP_SAF_SUS_CHK_DLY_OFS	0x1ac
#define MCHP_SAF_SUS_CHK_DLY_MASK	0xfffff

/* SAF Flash 0/1 Continuous Mode Prefix registers */
#define MCHP_SAF_FL_CM_PRF_OFS	0x1b0
#define MCHP_SAF_FL_CM_PRF_MASK	0xffff
#define MCHP_SAF_FL_CM_PRF_CS_OP_POS	0
#define MCHP_SAF_FL_CM_PRF_CS_OP_MASK	0xff
#define MCHP_SAF_FL_CM_PRF_CS_DAT_POS	8
#define MCHP_SAF_FL_CM_PRF_CS_DAT_MASK	\
	(0xff << MCHP_SAF_FL_CM_PRF_CS_DAT_POS)

/* SAF DnX Protection Bypass register */
#define MCHP_SAF_DNX_PROT_BYP_OFS	0x1b4
#define MCHP_SAF_DNX_PROT_BYP_MASK	0xffffffff

/* SAF Communication Mode */
#define MCHP_SAF_COMM_MODE_MASK	0x01
/* Allow pre-fetch from flash devices */
#define MCHP_SAF_COMM_MODE_PF_EN	BIT(0)

/* SAF TAG numbers[0:0xf] */
#define MCHP_SAF_TAG_M0T0	0
#define MCHP_SAF_TAG_M0T1	1
#define MCHP_SAF_TAG_M1T0	2
#define MCHP_SAF_TAG_M1T1	3
#define MCHP_SAF_TAG_M2T0	4
#define MCHP_SAF_TAG_M2T1	5
#define MCHP_SAF_TAG_M3T0	6
#define MCHP_SAF_TAG_M2T2	7
#define MCHP_SAF_TAG_M6T0	9
#define MCHP_SAF_TAG_M6T1	0xd
#define MCHP_SAF_TAG_MAX	0x10

/* SAF Master numbers */
#define MCHP_SAF_MSTR_CS_INIT	0
#define MCHP_SAF_MSTR_CPU	1
#define MCHP_SAF_MSTR_CS_ME	2
#define MCHP_SAF_MSTR_CS_LAN	3
#define MCHP_SAF_MSTR_UNUSED4	4
#define MCHP_SAF_MSTR_EC_FW	5
#define MCHP_SAF_MSTR_CS_IE	6
#define MCHP_SAF_MSTR_UNUSED7	7
#define MCHP_SAF_MSTR_MAX	8
#define MCHP_SAF_MSTR_ALL	0xff


#endif /* ESPI_SAF_H_ */
