#include "frustrum/platform/win/win_logger.hpp"

// TODO: rewrite to multiple sinks like spdlog, this should be called msvc_debug_sink
namespace frs
{

    platform::win::windows_logger::windows_logger()
    {
    }

    // TODO: write implementation for that
    void platform::win::windows_logger::log(frs::debug::message message)
    {
        OutputDebugString(message.data.data());
    }

} // namespace frs
