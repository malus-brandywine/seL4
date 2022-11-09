#pragma once

#include <autoconf.h>

#if !defined(CONFIG_ARM_NVIDIA_CARMEL)
#error CONFIG_ARM_NVIDIA_CARMEL is not defined
#endif

/* Xavier SoC manual, Section 5.13.2.2 */
#define seL4_NumHWBreakpoints           6
#define seL4_NumExclusiveBreakpoints    6
#define seL4_NumExclusiveWatchpoints    4

#ifdef CONFIG_HARDWARE_DEBUG_API

#define seL4_FirstBreakpoint             0
#define seL4_FirstWatchpoint             6

#define seL4_NumDualFunctionMonitors     0
#define seL4_FirstDualFunctionMonitor    (-1)

#endif /* CONFIG_HARDWARE_DEBUG_API */
