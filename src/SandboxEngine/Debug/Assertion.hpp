#ifndef SBX_ASSERTION_HPP
#define SBX_ASSERTION_HPP

#include "DebugBreak.hpp"
#include "LogManager.hpp"

#ifdef SBX_DEBUG_MODE

#define SBX_ERROR(...)                                                                                       \
    SBX_CRITICAL_LOG(__VA_ARGS__);                                                                           \
    SBX_DEBUG_BREAK()

#define SBX_ASSERT(condition, ...)                                                                           \
    if (!static_cast<bool>(condition))                                                                       \
        SBX_ERROR(__VA_ARGS__)

#else
#define SBX_ERROR(condition, message, ...)
#define SBX_ASSERT(message, ...)

#endif

#endif
