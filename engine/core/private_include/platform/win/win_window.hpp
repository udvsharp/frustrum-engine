#ifndef FRUSTRUM_WINDOWS_WINDOW
#define FRUSTRUM_WINDOWS_WINDOW

#include "frustrum/core.hpp"

#include <Windows.h>

#include "frustrum/window.hpp"

namespace frs::platform::win
{
    class windows_window
    {
    public: ///< Platform-agnostic
        windows_window();
        bool init();
        bool show();

    public:
        [[nodiscard]] FRS_CORE_EXPORT HWND nativeHandle() const;

    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    private:
        HWND _nativeHandle;
    };
} // namespace frs::platform::win

#endif //FRUSTRUM_WINDOWS_WINDOW
