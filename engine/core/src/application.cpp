#include "frustrum/application.hpp"

#ifdef FRS_PLATFORM_WINDOWS
    #include "frustrum/platform/win/win_application.hpp"
#endif

#include "frustrum/window.hpp"

#include <memory>

// TODO: upgrade this mechanism
std::shared_ptr<::frs::application> g_app_instance;

namespace frs
{
    std::shared_ptr<application> current_application() {
        return g_app_instance;
    }

    application::application(application::private_token) noexcept
        : ::std::enable_shared_from_this<application>()
        , _pimpl()
    {
    }

    ::frs::shared_ptr<application> application::make()
    {
        return ::std::make_shared<application>(application::private_token());
    }

    application::~application() noexcept = default;

    ::frs::shared_ptr<::frs::window> application::make_window()
    {
        return ::std::make_shared<::frs::window>();
    }

    bool application::init_window(
            ::frs::window_data data,
            const ::frs::shared_ptr<::frs::window>& window,
            const ::frs::shared_ptr<::frs::window>& parentWindow)
    {
        return window->init(
                shared_from_this(),
                std::move(data),
                parentWindow);
    }
} // namespace frs
