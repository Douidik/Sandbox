#ifndef SBX_DEBUG_BREAK_HPP
#define SBX_DEBUG_BREAK_HPP

#ifdef SBX_DEBUG_MODE

#if defined(SBX_WINDOWS_OS)
#define SBX_DEBUG_BREAK() __debugbreak()

#elif defined(SBX_LINUX_OS)
#include <signal.h>
#define SBX_DEBUG_BREAK() raise(SIGTRAP)

#elif defined(SBX_MAC_OS)
#define SBX_DEBUG_BREAK() __builtin_trap()
#endif

#else
#define SBX_DEBUG_BREAK()

#endif

#endif
