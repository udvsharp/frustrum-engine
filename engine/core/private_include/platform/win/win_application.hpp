#ifndef FRUSTRUM_WIN_APPLICATION
#define FRUSTRUM_WIN_APPLICATION

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include <Windows.h>

#include "frustrum/frsdef.hpp"

namespace frs::platform::win
{
    class windows_application {
        using wndclass_t = const TCHAR[];
    public:
        static inline wndclass_t window_class = TEXT("FrustrumEngineWindow");

    public:
        FRS_CORE_EXPORT windows_application();
        FRS_CORE_EXPORT ~windows_application();

        bool init(HINSTANCE instanceHandle, HICON hIcon = nullptr);

        const HINSTANCE instance_handle() const { return _instanceHandle; }

        [[nodiscard]] FRS_CORE_EXPORT ATOM wndclass_id() const { return _windowClassId; }
    private:
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] bool register_class(HICON hIcon);
    private:
        ATOM _windowClassId;
        HINSTANCE _instanceHandle {};
    };
}

#endif //FRUSTRUM_WIN_APPLICATION
