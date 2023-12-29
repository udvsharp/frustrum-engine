#ifndef FRUSTRUM_LEVEL
#define FRUSTRUM_LEVEL

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include "frustrum/frsdef.hpp"

#include <cstdint>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-macro-usage"
#define FRS_DEBUG_LEVEL_OFF 0u
#define FRS_DEBUG_LEVEL_TRACE 1u
#define FRS_DEBUG_LEVEL_DEBUG 2u
#define FRS_DEBUG_LEVEL_INFO 3u
#define FRS_DEBUG_LEVEL_WARN 4u
#define FRS_DEBUG_LEVEL_ERROR 5u
#define FRS_DEBUG_LEVEL_CRITICAL 6u
#pragma clang diagnostic pop

#ifndef FRS_DEBUG_LEVEL ///< Setting default value
    #define FRS_DEBUG_LEVEL FRS_DEBUG_LEVEL_DEBUG
#endif

namespace frs::debug
{
    using level_t = uint8_t;

    constexpr level_t LEVEL_OFF      = FRS_DEBUG_LEVEL_OFF;
    constexpr level_t LEVEL_TRACE    = FRS_DEBUG_LEVEL_TRACE;
    constexpr level_t LEVEL_DEBUG    = FRS_DEBUG_LEVEL_DEBUG;
    constexpr level_t LEVEL_INFO     = FRS_DEBUG_LEVEL_INFO;
    constexpr level_t LEVEL_WARN     = FRS_DEBUG_LEVEL_WARN;
    constexpr level_t LEVEL_ERROR    = FRS_DEBUG_LEVEL_ERROR;
    constexpr level_t LEVEL_CRITICAL = FRS_DEBUG_LEVEL_CRITICAL;

    enum struct level : level_t
    {
        off      = ::frs::debug::LEVEL_OFF,
        trace    = ::frs::debug::LEVEL_TRACE,
        debug    = ::frs::debug::LEVEL_DEBUG,
        info     = ::frs::debug::LEVEL_INFO,
        warn     = ::frs::debug::LEVEL_WARN,
        error    = ::frs::debug::LEVEL_ERROR,
        critical = ::frs::debug::LEVEL_CRITICAL,
    };

    inline string to_string(level level)
    {
        switch (level)
        {
        case level::trace:
            return L"trace";
        case level::debug:
            return L"debug";
        case level::info:
            return L"info";
        case level::warn:
            return L"warn";
        case level::error:
            return L"error";
        case level::critical:
            return L"critical";
        default:
            return L"NULL";
        }
    }
} // namespace frs::debug

#endif //FRUSTRUM_LEVEL
