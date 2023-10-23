#ifndef FRUSTRUM_MESSAGE
#define FRUSTRUM_MESSAGE

#include "frustrum/core.hpp"

#include <chrono>
#include <source_location>

#include "frustrum/debug/level.hpp"
#include "frustrum/frsdef.hpp"
#include "frustrum/frustrum_core_export.hpp"

namespace frs::debug
{
    using clock = std::chrono::system_clock;

    struct FRS_CORE_EXPORT message {
        FRS_DEFAULT_COPY(message);
        FRS_DISABLE_MOVE(message);

        message() = default;
        message(string_view data,
                debug::level level,
                std::source_location location = std::source_location::current(),
                clock::time_point timestamp = clock::now());

        frs::string_view data;
        frs::debug::level level;
        clock::time_point timestamp;
        std::source_location location;

        frs::thread_id_t thread_id;
    };
} // namespace frs::debug

#endif //FRUSTRUM_MESSAGE
