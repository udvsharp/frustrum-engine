#ifndef FRUSTRUM_WINDOW
#define FRUSTRUM_WINDOW

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include <concepts>
#include <type_traits>

#include "frustrum/frsdef.hpp"
#include "frustrum/pimpl.hpp"
#include "frustrum/window_data.hpp"

FRS_DECLARE_PIMPL(window)
#ifndef FRS_GENERATING
    #ifdef FRS_PLATFORM_WINDOWS
        #include "frustrum/generated/windows_window_traits.hpp"
    #endif
#endif

namespace frs
{
    class application;

    class window
    {
        using impl = FRS_PLATFORM_IMPL_NAMESPACED(window);

    public:
        FRS_CORE_EXPORT window();
        FRS_CORE_EXPORT ~window();

        FRS_CORE_EXPORT bool init(
                const ::frs::shared_ptr<::frs::application>& owningApplication,
                ::frs::window_data data,
                const ::frs::shared_ptr<::frs::window>& parentWindow = {});
        FRS_CORE_EXPORT bool show();

    private:
        ::frs::pimpl<window, impl> _pimpl;
    };
} // namespace frs

#endif //FRUSTRUM_WINDOW
