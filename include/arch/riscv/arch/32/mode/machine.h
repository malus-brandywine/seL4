/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once

#include <util.h>
#include <arch/model/smp.h>
#include <stdint.h>
#include <plat/machine/devices_gen.h>
#include <plat/platform_gen.h>

#define CLINT_MTIME_LO_OFFSET 0xbff8
#define CLINT_MTIME_HI_OFFSET 0xbffc

static inline uint64_t riscv_read_time(void)
{
    word_t nH1, nL, nH2;

    nH1 = *(volatile word_t *)(CLINT_PPTR + CLINT_MTIME_HI_OFFSET);
    nL = *(volatile word_t *)(CLINT_PPTR + CLINT_MTIME_LO_OFFSET);
    nH2 = *(volatile word_t *)(CLINT_PPTR + CLINT_MTIME_HI_OFFSET);
    if (nH1 != nH2) {
        /* Ensure that the time is correct if there is a rollover in the
         * high bits between reading the low and high bits. */
        nL = *(volatile word_t *)(CLINT_PPTR + CLINT_MTIME_LO_OFFSET);
    }
    return (((uint64_t)nH2) << 32) | nL;
}


static inline uint64_t riscv_read_cycle(void)
{
    word_t nH1, nL, nH2;
    asm volatile(
        "rdcycleh %0\n"
        "rdcycle  %1\n"
        "rdcycleh %2\n"
        : "=r"(nH1), "=r"(nL), "=r"(nH2));
    if (nH1 != nH2) {
        /* Ensure that the cycles are correct if there is a rollover in the
         * high bits between reading the low and high bits. */
        asm volatile("rdcycle  %0\n" : "=r"(nL));
    }
    return (((uint64_t)nH2) << 32) | nL;
}
