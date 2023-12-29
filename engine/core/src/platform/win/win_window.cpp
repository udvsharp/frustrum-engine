#include "frustrum/platform/win/win_window.hpp"

#include <cstdint>
#include <string>

#include <Windows.h>

#include "frustrum/application.hpp"
#include "frustrum/debug.hpp"

#include "frustrum/platform/win/win_application.hpp"

namespace frs
{
    window_data window_data::make_default()
    {
        return {
                .type   = window_type::general,
                .x      = CW_USEDEFAULT,
                .y      = CW_USEDEFAULT,
                .width  = CW_USEDEFAULT,
                .height = CW_USEDEFAULT,

                .has_sizing_frame  = true,
                .has_close_btn     = true,
                .supports_maximise = true,
                .supports_minimise = true,
                .is_always_topmost = false,

                .should_preserve_aspect_ratio = false,

                .has_os_window_border  = true,
                .supports_transparency = false,
                .accepts_input         = true,

                .title = L"Frustum Engine Window"};
    }
} // namespace frs

namespace frs::platform::win
{
    windows_window::windows_window()
        : _hwnd {}
    {
    }

    windows_window::~windows_window()
    {
        // TODO: ensure that _hwnd is invalid (should be destroyed earlier)
        // DestroyWindow(_hwnd);
    }

    HWND windows_window::hwnd() const
    {
        return _hwnd;
    }

    windows_window::style_t windows_window::style_from(const window_data& data)
    {
        style_t style = 0;

        // TODO: maybe can be simplified?
        if (data.has_os_window_border)
        {
            style |= WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;

            if (data.type == window_type::general)
            {
                if (data.supports_minimise)
                {
                    style |= WS_MINIMIZEBOX;
                }

                if (data.supports_maximise)
                {
                    style |= WS_MAXIMIZEBOX;
                }

                if (data.has_sizing_frame)
                {
                    style |= WS_THICKFRAME;
                }
                else
                {
                    style |= WS_BORDER;
                }
            }
            else
            {
                style |= WS_POPUP | WS_BORDER;
            }
        }
        else
        {
            style |= WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
        }

        return style;
    }

    windows_window::ex_style_t windows_window::ex_style_from(const window_data& data)
    {
        ex_style_t exStyle = 0;

        if (data.has_os_window_border)
        {
            exStyle |= WS_EX_APPWINDOW;
        }
        else
        {
            exStyle |= WS_EX_WINDOWEDGE;
        }

        if (data.supports_transparency)
        {
            exStyle |= WS_EX_LAYERED;
            // TODO: WS_EX_COMPOSITED if PerPixel transparency
        }

        if (data.is_always_topmost)
        {
            exStyle |= WS_EX_TOPMOST;
        }

        if (!data.accepts_input)
        {
            exStyle |= WS_EX_TRANSPARENT;
        }

        return exStyle;
    }

    std::tuple<windows_window::style_t, windows_window::ex_style_t> windows_window::styles_from(const window_data& data)
    {
        style_t style      = style_from(data);
        ex_style_t exStyle = ex_style_from(data);

        return std::make_tuple(style, exStyle);
    }

    bool windows_window::init(
            const ::frs::shared_ptr<::frs::application>& owningApplication,
            window_data data,
            const ::frs::shared_ptr<::frs::window>& parentWindow)
    {
        // TODO: get styles from config

        const auto [style, ex_style] = styles_from(data);
        const wchar_t* wide_title    = data.title.data();

        const auto classId = owningApplication->platform().wndclass_id();

        _hwnd = ::CreateWindowEx(
                ex_style,
                MAKEINTATOM(classId),
                wide_title,
                style,
                data.x, data.y,
                data.width, data.height,
                nullptr, // TODO: parent handling?
                nullptr, ///< No menu
                owningApplication->platform().instance_handle(),
                nullptr // TODO: this is additional ptr
        );

        if (_hwnd == nullptr)
        {
            const auto error = GetLastError();

            // TODO: Have seen that it's helpful to write here
            //  counts of GDI and user objects, number of handles existing in app
            FRS_DEBUG_LOG_ERROR(L"Failed to create window - handle is invalid: {}", error);

            // TODO: handle error codes

            return false;
        }

        return true;
    }

    bool windows_window::show()
    {
        BOOL showError = ShowWindow(_hwnd, SW_SHOW);
        return showError == 0;
    }

} // namespace frs::platform::win
