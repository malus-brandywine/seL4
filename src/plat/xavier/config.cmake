#
# Copyright 2022, UNSW // @ivanv
#
# SPDX-License-Identifier: GPL-2.0-only
#

cmake_minimum_required(VERSION 3.7.2)

declare_platform(xavier KernelPlatformXavier PLAT_XAVIER KernelSel4ArchAarch64)

if(KernelPlatformXavier)
    declare_seL4_arch(aarch64)
    set(KernelArmNvidiaCarmel ON)
    set(KernelArchArmV8a ON)
    config_set(KernelARMPlatform ARM_PLAT xavier)
    config_set(KernelArmMach MACH "nvidia")
    list(APPEND KernelDTSList "tools/dts/xavier.dts")
    list(APPEND KernelDTSList "src/plat/xavier/overlay-xavier.dts")
    # @ivanv: come back to these values
    declare_default_headers(
        TIMER_FREQUENCY 31250000
        MAX_IRQ 383
        INTERRUPT_CONTROLLER arch/machine/gic_v2.h
        NUM_PPI 32
        TIMER drivers/timer/arm_generic.h
        CLK_SHIFT 57u
        CLK_MAGIC 4611686019u
        KERNEL_WCET 10u
    )
endif()

add_sources(
    DEP "KernelPlatformXavier"
    CFILES src/arch/arm/machine/gic_v2.c src/arch/arm/machine/l2c_nop.c
)
