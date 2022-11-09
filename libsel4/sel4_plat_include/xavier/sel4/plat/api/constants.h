/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <autoconf.h>

#if defined(CONFIG_ARM_NVIDIA_CARMEL)
#include <sel4/arch/constants_nvidia_carmel.h>
#else
#error "unsupported core"
#endif
