/*
 * SPDX-FileCopyrightText: 2020-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>

#include "soc/soc_caps.h"
#include "soc/dport_access.h"
#include "soc/system_reg.h"
#include "esp_bit_defs.h"
#include "soc/assist_debug_reg.h"
#include "esp_attr.h"
#include "riscv/csr.h"

/*performance counter*/
#define CSR_PCER_MACHINE    0x7e0
#define CSR_PCMR_MACHINE    0x7e1
#define CSR_PCCR_MACHINE    0x7e2

/*fast gpio*/
#define CSR_GPIO_OEN_USER   0x803
#define CSR_GPIO_IN_USER    0x804
#define CSR_GPIO_OUT_USER   0x805

#ifdef __cplusplus
extern "C" {
#endif

static inline int IRAM_ATTR cpu_ll_get_core_id(void)
{
#if SOC_CPU_CORES_NUM == 1
    return 0; // No need to check core ID on single core hardware
#else
    int cpuid;
    cpuid = RV_READ_CSR(mhartid);
    return cpuid;
#endif
}

static inline void cpu_ll_enable_cycle_count(void)
{
    RV_WRITE_CSR(CSR_PCER_MACHINE,1);
    RV_WRITE_CSR(CSR_PCMR_MACHINE,1);
    return;
}

static inline uint32_t IRAM_ATTR cpu_ll_get_cycle_count(void)
{
    uint32_t result;
    result = RV_READ_CSR(CSR_PCCR_MACHINE);
    return result;
}

static inline void IRAM_ATTR cpu_ll_set_cycle_count(uint32_t val)
{
    RV_WRITE_CSR(CSR_PCCR_MACHINE, val);
}

static inline void* cpu_ll_get_sp(void)
{
    void *sp;
    __asm__ volatile ("mv %0, sp;" : "=r" (sp));
    return sp;
}

static inline void cpu_ll_init_hwloop(void)
{
    // Nothing needed here for ESP32-C3
}

static inline void cpu_ll_set_breakpoint(int id, uint32_t pc)
{
    RV_WRITE_CSR(tselect,id);
    RV_SET_CSR(CSR_TCONTROL,TCONTROL_MTE);
    RV_SET_CSR(CSR_TDATA1, TDATA1_USER|TDATA1_MACHINE|TDATA1_EXECUTE);
    RV_WRITE_CSR(tdata2,pc);
    return;
}

static inline void cpu_ll_clear_breakpoint(int id)
{
    RV_WRITE_CSR(tselect,id);
    RV_CLEAR_CSR(CSR_TCONTROL,TCONTROL_MTE);
    RV_CLEAR_CSR(CSR_TDATA1, TDATA1_USER|TDATA1_MACHINE|TDATA1_EXECUTE);
    return;
}

static inline uint32_t cpu_ll_ptr_to_pc(const void* addr)
{
    return ((uint32_t) addr);
}

static inline void* cpu_ll_pc_to_ptr(uint32_t pc)
{
    return (void*) ((pc & 0x3fffffff) | 0x40000000);
}

static inline void cpu_ll_set_watchpoint(int id,
                                        const void* addr,
                                        size_t size,
                                        bool on_read,
                                        bool on_write)
{
    uint32_t addr_napot;
    RV_WRITE_CSR(tselect,id);
    RV_SET_CSR(CSR_TCONTROL, TCONTROL_MPTE | TCONTROL_MTE);
    RV_SET_CSR(CSR_TDATA1, TDATA1_USER|TDATA1_MACHINE);
    RV_SET_CSR_FIELD(CSR_TDATA1, TDATA1_MATCH, 1);
    // add 0 in napot encoding
    addr_napot = ((uint32_t) addr) | ((size >> 1) - 1);
    if (on_read) {
        RV_SET_CSR(CSR_TDATA1, TDATA1_LOAD);
    }
    if (on_write) {
        RV_SET_CSR(CSR_TDATA1, TDATA1_STORE);
    }
    RV_WRITE_CSR(tdata2,addr_napot);
   return;
}

static inline void cpu_ll_clear_watchpoint(int id)
{
    RV_WRITE_CSR(tselect,id);
    RV_CLEAR_CSR(CSR_TCONTROL,TCONTROL_MTE);
    RV_CLEAR_CSR(CSR_TDATA1, TDATA1_USER|TDATA1_MACHINE);
    RV_CLEAR_CSR_FIELD(CSR_TDATA1,TDATA1_MATCH);
    RV_CLEAR_CSR(CSR_TDATA1, TDATA1_MACHINE);
    RV_CLEAR_CSR(CSR_TDATA1, TDATA1_LOAD|TDATA1_STORE|TDATA1_EXECUTE);
    return;
}

FORCE_INLINE_ATTR bool cpu_ll_is_debugger_attached(void)
{
    return REG_GET_BIT(ASSIST_DEBUG_CORE_0_DEBUG_MODE_REG, ASSIST_DEBUG_CORE_0_DEBUG_MODULE_ACTIVE);
}

static inline void cpu_ll_break(void)
{
    __asm__ volatile("ebreak\n");
    return;
}

static inline int cpu_ll_syscall(int sys_nr, int arg1, int arg2, int arg3, int arg4, int* ret_errno)
{
    int host_ret, host_errno;

    __asm__ volatile ( \
        ".option push\n" \
        ".option norvc\n" \
        "mv a0, %[sys_nr]\n" \
        "mv a1, %[arg1]\n" \
        "mv a2, %[arg2]\n" \
        "mv a3, %[arg3]\n" \
        "mv a4, %[arg4]\n" \
        "slli    zero,zero,0x1f\n" \
        "ebreak\n" \
        "srai    zero,zero,0x7\n" \
        "mv %[host_ret], a0\n" \
        "mv %[host_errno], a1\n" \
        ".option pop\n" \
        :[host_ret]"=r"(host_ret),[host_errno]"=r"(host_errno)
        :[sys_nr]"r"(sys_nr),[arg1]"r"(arg1),[arg2]"r"(arg2),[arg3]"r"(arg3),[arg4]"r"(arg4)
        :"a0","a1","a2","a3","a4");

    if (ret_errno) {
        *ret_errno = host_errno;
    }
    return host_ret;
}

static inline void cpu_ll_set_vecbase(const void* vecbase)
{
    uintptr_t vecbase_int = (uintptr_t)vecbase;
    vecbase_int |= 1; // Set MODE field to treat MTVEC as a vector base address
    RV_WRITE_CSR(mtvec, vecbase_int);
}

static inline void cpu_ll_waiti(void)
{
    if (cpu_ll_is_debugger_attached() && DPORT_REG_GET_BIT(SYSTEM_CPU_PER_CONF_REG, SYSTEM_CPU_WAIT_MODE_FORCE_ON) == 0) {
        /* when SYSTEM_CPU_WAIT_MODE_FORCE_ON is disabled in WFI mode SBA access to memory does not work for debugger,
           so do not enter that mode when debugger is connected */
        return;
    }
    __asm__ volatile ("wfi\n");
}

static inline void cpu_ll_enable_dedic_gpio_output(uint32_t mask)
{
    RV_WRITE_CSR(CSR_GPIO_OEN_USER, mask);
}

static inline void cpu_ll_write_dedic_gpio_all(uint32_t value)
{
    RV_WRITE_CSR(CSR_GPIO_OUT_USER, value);
}

static inline uint32_t cpu_ll_read_dedic_gpio_in(void)
{
    uint32_t value = RV_READ_CSR(CSR_GPIO_IN_USER);
    return value;
}

static inline uint32_t cpu_ll_read_dedic_gpio_out(void)
{
    uint32_t value = RV_READ_CSR(CSR_GPIO_OUT_USER);
    return value;
}

static inline void cpu_ll_write_dedic_gpio_mask(uint32_t mask, uint32_t value)
{
    RV_SET_CSR(CSR_GPIO_OUT_USER, mask & value);
    RV_CLEAR_CSR(CSR_GPIO_OUT_USER, mask & ~(value));
}

#ifdef __cplusplus
}
#endif
