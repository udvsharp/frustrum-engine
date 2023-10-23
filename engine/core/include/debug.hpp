#ifndef FRUSTRUM_DEBUG
#define FRUSTRUM_DEBUG

#include "frustrum/core.hpp"

#include "frustrum/debug/level.hpp"
#include "frustrum/debug/logger.hpp"

namespace frs::debug
{
    frs::shared_ptr<logger> default_logger();

    // region Per-level formatted logging
    template<typename... Args>
    void trace(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->trace(location, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void debug(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->debug(location, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->info(location, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void warn(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->warn(location, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void error(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->error(location, fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void critical(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
    {
        default_logger()->critical(location, fmt, std::forward<Args>(args)...);
    }
    // endregion
    // region Simple message logging
    template<typename T>
    void trace(const T& msg)
    {
        default_logger()->trace(msg);
    }

    template<typename T>
    void debug(const T& msg)
    {
        default_logger()->debug(msg);
    }

    template<typename T>
    void info(const T& msg)
    {
        default_logger()->info(msg);
    }

    template<typename T>
    void warn(const T& msg)
    {
        default_logger()->warn(msg);
    }

    template<typename T>
    void error(const T& msg)
    {
        default_logger()->error(msg);
    }

    template<typename T>
    void critical(const T& msg)
    {
        default_logger()->critical(msg);
    }
    // endregion
} // namespace frs::debug

#define FRS_DEBUG_LOG_TRACE(...)     ::frs::debug::trace(std::source_location::current(), __VA_ARGS__)
#define FRS_DEBUG_LOG_DEBUG(...)     ::frs::debug::debug(std::source_location::current(), __VA_ARGS__)
#define FRS_DEBUG_LOG_INFO(...)      ::frs::debug::info(std::source_location::current(), __VA_ARGS__)
#define FRS_DEBUG_LOG_WARN(...)      ::frs::debug::warn(std::source_location::current(), __VA_ARGS__)
#define FRS_DEBUG_LOG_ERROR(...)     ::frs::debug::error(std::source_location::current(), __VA_ARGS__)
#define FRS_DEBUG_LOG_CRITICAL(...)  ::frs::debug::critical(std::source_location::current(), __VA_ARGS__)

#endif //FRUSTRUM_DEBUG
