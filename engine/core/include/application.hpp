#ifndef FRUSTRUM_APPLICATION
#define FRUSTRUM_APPLICATION

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include <memory>

#include "frustrum/frsdef.hpp"
#include "frustrum/pimpl.hpp"
#include "frustrum/window_data.hpp"

FRS_DECLARE_PIMPL(application)
#ifndef FRS_GENERATING
    #ifdef FRS_PLATFORM_WINDOWS
        #include "frustrum/generated/windows_application_traits.hpp"
    #endif
#endif

namespace frs
{
    class window;

    class application
        : public ::std::enable_shared_from_this<application>
    {
        using impl = FRS_PLATFORM_IMPL_NAMESPACED(application);

    private:
        struct private_token {}; //< TODO: can be an utility
    public:
        /// @brief hidden because you can only create a shared_ptr
        FRS_CORE_EXPORT application(private_token) noexcept;
        virtual FRS_CORE_EXPORT ~application() noexcept;

#ifdef FRS_CORE_EXPORTS
        FRS_CORE_EXPORT impl& platform() const
        {
            return *_pimpl;
        }
#endif
        FRS_CORE_EXPORT static ::frs::shared_ptr<application> make();

        FRS_CORE_EXPORT ::frs::shared_ptr<::frs::window> make_window();
        FRS_CORE_EXPORT bool init_window(
                ::frs::window_data data,
                const ::frs::shared_ptr<::frs::window>& window,
                const ::frs::shared_ptr<::frs::window>& parentWindow = {});

    private:
        ::frs::pimpl<application, impl> _pimpl;
    };

    FRS_CORE_EXPORT std::shared_ptr<application> current_application();
} // namespace frs

#endif //FRUSTRUM_APPLICATION
