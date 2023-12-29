#ifndef FRUSTRUM_WINDOWS_WINDOW
#define FRUSTRUM_WINDOWS_WINDOW

#include "frustrum/core.hpp"

#include <utility>

#include <Windows.h>

#include "frustrum/window.hpp"

namespace frs::platform::win
{
    class windows_window
    {
        using ex_style_t = DWORD;
        using style_t    = DWORD;

    public: ///< Platform-agnostic
        windows_window();
        ~windows_window();
        bool init(
                const ::frs::shared_ptr<::frs::application>& owningApplication,
                ::frs::window_data data,
                const ::frs::shared_ptr<::frs::window>& parentWindow);
        bool show();

    public:
        [[nodiscard]] FRS_CORE_EXPORT HWND hwnd() const;

    private:
        [[nodiscard]] static std::tuple<style_t, ex_style_t> styles_from(const ::frs::window_data& data);
        [[nodiscard]] static style_t style_from(const ::frs::window_data& data);
        [[nodiscard]] static style_t ex_style_from(const ::frs::window_data& data);

    private:
        HWND _hwnd;
    };
} // namespace frs::platform::win

#endif //FRUSTRUM_WINDOWS_WINDOW
