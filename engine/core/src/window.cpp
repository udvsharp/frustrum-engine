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

    bool window::init(
            const ::frs::shared_ptr<::frs::application>& owningApplication,
            ::frs::window_data data,
            const ::frs::shared_ptr<window>& parentWindow)
    {
        return _pimpl->init(owningApplication, std::move(data), parentWindow);
    }

    bool window::show()
    {
        return _pimpl->show();
    }
} // namespace frs
