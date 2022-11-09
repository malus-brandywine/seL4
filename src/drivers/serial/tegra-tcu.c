/*
 * Copyright 2022, UNSW
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <config.h>
#include <stdint.h>
#include <util.h>
#include <machine/io.h>
#include <plat/machine/devices_gen.h>

#define UART_REG(x) ((volatile uint32_t *)(UART_PPTR + (x)))

#ifdef CONFIG_PRINTING
void uart_drv_putchar(unsigned char c)
{
    while (!(*UART_REG() & ));
    *UART_REG() = c;
}
#endif /* CONFIG_PRINTING */

#ifdef CONFIG_DEBUG_BUILD
unsigned char uart_drv_getchar(void)
{
    while (!(*UART_REG() & ));
    return *UART_REG();
}
#endif /* CONFIG_DEBUG_BUILD */
