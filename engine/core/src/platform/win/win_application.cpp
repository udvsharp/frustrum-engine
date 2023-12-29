#include "frustrum/platform/win/win_application.hpp"

#include "frustrum/debug.hpp"

extern HINSTANCE g_hInstance;

namespace frs::platform::win
{
    LRESULT windows_application::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // TODO: get custom pointer from hwnd
        switch (uMsg)
        {
        case WM_CLOSE:
            if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            }
            // Else: User canceled. Do nothing.
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    windows_application::windows_application()
        : _instanceHandle()
        , _windowClassId()
    {
        // FRS_DEBUG_ASSERT(instanceHandle)
    }

    windows_application::~windows_application() = default;

    bool windows_application::init(HINSTANCE instanceHandle, HICON hIcon)
    {
        _instanceHandle = instanceHandle;
        return register_class(hIcon);
    }

    bool windows_application::register_class(HICON hIcon)
    {
        // TODO: per-application?
        WNDCLASSEXW wndclass;
        memset(&wndclass, 0, sizeof(wndclass)); ///< TODO: abstract this to some utility file

        wndclass.cbSize        = sizeof(wndclass);
        wndclass.lpszClassName = windows_application::window_class; ///< TODO: figure it out...
        wndclass.lpfnWndProc   = windows_application::WindowProc;
        wndclass.hInstance     = _instanceHandle;
        wndclass.style         = CS_DBLCLKS; ///< TODO: more options?
        wndclass.cbClsExtra    = 0;          ///< TODO: figure out when this is needed
        wndclass.cbWndExtra    = 0;          ///< TODO: figure out when this is needed
        wndclass.hCursor       = nullptr;    ///< Will be managed by the engine
        wndclass.hIcon         = nullptr;    ///< TODO: user-provided icon?
        wndclass.lpszMenuName  = nullptr;
        wndclass.hbrBackground = nullptr;

        _windowClassId = ::RegisterClassEx(&wndclass);

        if (_windowClassId == 0U)
        {
            const auto error = GetLastError();

            // TODO: Have seen that it's helpful to write here
            //  counts of GDI and user objects, number of handles existing in app
            FRS_DEBUG_LOG_ERROR(L"Failed to register window class: {}", error);

            return false;
        }

        return true;
    }

} // namespace frs::platform::win
