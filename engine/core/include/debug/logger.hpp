#ifndef FRUSTRUM_LOGGER
#define FRUSTRUM_LOGGER

#include "frustrum/core.hpp"

#include <cstdint>
#include <format>
#include <source_location>

#include "frustrum/debug/level.hpp"
#include "frustrum/debug/message.hpp"
#include "frustrum/frsdef.hpp"
#include "frustrum/pimpl.hpp"

FRS_DECLARE_PIMPL(logger)
#ifndef FRS_GENERATING
    #ifdef FRS_PLATFORM_WINDOWS
        #include "frustrum/generated/windows_logger_traits.hpp"
    #endif
#endif

namespace frs::debug
{
    constexpr string_view to_string_view(const memory_buffer_t& buffer)
    {
        return string_view {buffer.data(), buffer.size()};
    }

    template<typename T, typename... Args>
    constexpr string_view to_string_view(
            std::basic_format_string<T, Args...> fmt) noexcept
    {
        return fmt.get();
    }

    class logger
    {
        using impl = FRS_PLATFORM_IMPL_NAMESPACED(logger);

    public:
        logger();

        template<typename... Args>
        void log(level level,
                 std::source_location location,
                 format_string_t<Args...> fmt,
                 Args&&... args)
        {
            _log(level, location, fmt, std::forward<Args>(args)...);
        }

        template<typename T>
        void log(level level,
                 std::source_location location,
                 const T& msg)
        {
            log(level, location, msg);
        }
        // region Per-level formatted logging
        template<typename... Args>
        void trace(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::trace, location, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void debug(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::debug, location, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void info(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::info, location, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void warn(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::warn, location, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void error(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::error, location, fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        void critical(std::source_location location, format_string_t<Args...> fmt, Args&&... args)
        {
            log(level::critical, location, fmt, std::forward<Args>(args)...);
        }
        // endregion
        // region Simple message logging
        template<typename T>
        void trace(const T& msg)
        {
            log(level::trace, msg);
        }

        template<typename T>
        void debug(const T& msg)
        {
            log(level::debug, msg);
        }

        template<typename T>
        void info(const T& msg)
        {
            log(level::info, msg);
        }

        template<typename T>
        void warn(const T& msg)
        {
            log(level::warn, msg);
        }

        template<typename T>
        void error(const T& msg)
        {
            log(level::error, msg);
        }

        template<typename T>
        void critical(const T& msg)
        {
            log(level::critical, msg);
        }
        // endregion

        bool should_log(frs::debug::level level)
        {
            return _level >= level;
        }

    private:
        template<typename... Args>
        void _log(level level,
                  std::source_location location,
                  format_string_t<Args...> fmt,
                  Args&&... args)
        {
            if (!should_log(level))
            {
                return;
            }

            memory_buffer_t buffer;
            std::format_to(std::back_inserter(buffer),
                           std::forward<format_string_t<Args...>>(fmt),
                           std::forward<Args>(args)...);

            const frs::debug::message message {buffer, level, location};
            _log_msg(message);
        }

        /// Main log function
        void _log_msg(frs::debug::message message);

    private:
        frs::string _name;
        frs::debug::level _level {level::info};
        // TODO: sink ptr

        /// Platform-specific logger implementation
        frs::pimpl<impl> _pimpl;
    };

} // namespace frs::debug

#endif //FRUSTRUM_LOGGER
