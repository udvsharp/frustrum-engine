#include "frustrum/platform/win/win_logger.hpp"

#include <iostream>

namespace frs
{
    template<typename... Args>
    void print_formatted(format_string_t<Args...> fmt, Args&&... args)
    {
        memory_buffer_t buffer;
        std::format_to(std::back_inserter(buffer),
                       std::forward<format_string_t<Args...>>(fmt),
                       std::forward<Args>(args)...);

        std::wcout << buffer << std::endl;
    }
} // namespace frs

// TODO: rewrite to multiple sinks like spdlog, this should be called msvc_debug_sink
namespace frs
{

    platform::win::windows_logger::windows_logger()
    {
    }

    // TODO: write implementation for that
    void platform::win::windows_logger::log(frs::debug::message message)
    {
        print_formatted(
                L"[{}]: {}",
                to_string(message.level),
                message.data); // TODO: doesn't work with source location
        // OutputDebugString(message.data.data());
    }

} // namespace frs
