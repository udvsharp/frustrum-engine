#include "frustrum/debug/logger.hpp"
#include "frustrum/debug.hpp"

#ifdef FRS_PLATFORM_WINDOWS
    #include "frustrum/platform/win/win_logger.hpp"
#endif

namespace frs::debug
{
    frs::shared_ptr<logger> default_logger() {
        // TODO: registry
        static frs::shared_ptr<logger> default_logger = std::make_shared<logger>();
        return default_logger;
    }
    logger::logger()
    {
    }

    // TODO: logs only to console right now
    void logger::_log_msg(frs::debug::message message)
    {
        _pimpl->log(message);
    }
} // namespace frs::debug
