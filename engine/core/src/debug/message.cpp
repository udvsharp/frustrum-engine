#ifndef FRUSTRUM_DEBUG_MESSAGE
#define FRUSTRUM_DEBUG_MESSAGE

#include "frustrum/debug/message.hpp"

#include "frustrum/threads.hpp"

namespace frs::debug
{
    message::message(string_view data,
                     debug::level level,
                     std::source_location location,
                     clock::time_point timestamp)
        : data(data)
        , level(level)
        , timestamp(timestamp)
        , location(location)
        , thread_id(frs::thread_id())
    {
    }

} // namespace frs::debug

#endif //FRUSTRUM_DEBUG_MESSAGE
