#include "frustrum/platform/win/win_window.hpp"

#include <cstdint>
#include <string>

#include <Windows.h>

#include "frustrum/debug.hpp"

extern HINSTANCE g_hInstance;

namespace
{

}

namespace frs::platform::win
{
    LRESULT windows_window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

    windows_window::windows_window()
        : _nativeHandle {}
    {
    }

    HWND windows_window::nativeHandle() const
    {
        return _nativeHandle;
    }

    bool windows_window::init()
    {
        if (g_hInstance == nullptr)
        {
            return false;
        }

        // TODO: get styles from config
        int frameX      = CW_USEDEFAULT,
            frameY      = CW_USEDEFAULT,
            frameWidth  = CW_USEDEFAULT,
            frameHeight = CW_USEDEFAULT;

        DWORD style = WS_OVERLAPPEDWINDOW;
        // TODO: conditional
        DWORD exStyle = 0;
        // TODO: param
        const wchar_t* wideTitle = L"Test window name";

        WNDCLASSEXW wc   = {.cbSize = sizeof(wc)};
        wc.lpfnWndProc   = windows_window::WindowProc;
        wc.hInstance     = g_hInstance;
        wc.lpszClassName = L"FRS10";
        // wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        // TODO: user provided Icon
        // wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        // TODO: custom classname and why?
        // TODO: store this! It's a unique created window ID
        ATOM classId = RegisterClassEx(&wc);

        if (!classId)
        {
            // TODO: error
            return false;
        }

        _nativeHandle = CreateWindowEx(
                exStyle,
                MAKEINTATOM(classId),
                wideTitle,
                style,
                frameX, frameY,
                frameWidth, frameHeight,

                nullptr,
                // No parent window
                nullptr,     // No window menu
                g_hInstance, // TODO: add instance
                nullptr      // TODO: this is additional ptr
        );

        if (_nativeHandle == nullptr)
        {
            const auto error = GetLastError();

            /// Have seen that
            FRS_DEBUG_LOG_ERROR(L"Failed to create window - handle is invalid: {}", error);

            // TODO: handle error codes

            return false;
        }

        return true;
    }

    bool windows_window::show()
    {
        BOOL showError = ShowWindow((HWND)_nativeHandle, SW_SHOWNA);
        if (showError != 0)
        {
            return false;
        }

        return true;
    }

} // namespace frs::platform::win
