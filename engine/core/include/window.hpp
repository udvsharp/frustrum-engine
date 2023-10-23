#ifndef FRS_WINDOW
#define FRS_WINDOW

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include <concepts>
#include <type_traits>

#include "frustrum/frsdef.hpp"
#include "frustrum/pimpl.hpp"

FRS_DECLARE_PIMPL(window)
#ifndef FRS_GENERATING
    #ifdef FRS_PLATFORM_WINDOWS
        #include "frustrum/generated/windows_window_traits.hpp"
    #endif
#endif

namespace frs
{
    class window
    {
        using impl = FRS_PLATFORM_IMPL_NAMESPACED(window);
    public:
        FRS_CORE_EXPORT window();
        FRS_CORE_EXPORT ~window();
        FRS_CORE_EXPORT bool init();
        FRS_CORE_EXPORT bool show();
    private:
        pimpl<impl> _pimpl;
    };
} // namespace frs

#endif //FRS_WINDOW
