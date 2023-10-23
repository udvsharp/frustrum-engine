#ifndef FRUSTRUM_WIN_LOGGER
#define FRUSTRUM_WIN_LOGGER

#include "frustrum/core.hpp"

#include <Windows.h>

#include "frustrum/debug/logger.hpp"

namespace frs::platform::win
{
    class windows_logger {
    public:
        windows_logger();

        void FRS_CORE_EXPORT log(frs::debug::message message);
    };
}

#endif //FRUSTRUM_WIN_LOGGER
