#include "frustrum/threads.hpp"

#ifdef FRS_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

namespace
{
    frs::thread_id_t get_current_thread_id()
    {
#ifdef FRS_PLATFORM_WINDOWS
    return static_cast<frs::thread_id_t>(::GetCurrentThreadId());
#else
    #error Unsupported platform!
#endif
    }
} // namespace

namespace frs
{
    frs::thread_id_t thread_id()
    {
        static thread_local const thread_id_t id = ::get_current_thread_id();
        return id;
    }
} // namespace frs
