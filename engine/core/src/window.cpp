#include "frustrum/window.hpp"

#ifdef FRS_PLATFORM_WINDOWS
    #include "frustrum/platform/win/win_window.hpp"
#endif

namespace frs
{

    window::window()
        : _pimpl()
    {
    }

    window::~window() = default;

    bool window::init()
    {
        return _pimpl->init();
    }

    bool window::show()
    {
        return _pimpl->show();
    }
} // namespace frs
