#ifndef FRUSTRUM_WINDOW_DATA
#define FRUSTRUM_WINDOW_DATA

#include "frustrum/core.hpp"
#include "frustrum/frustrum_core_export.hpp"

#include "frustrum/frsdef.hpp"

namespace frs
{
    enum class window_type : window_type_t
    {
        general,
        menu,
        tooltip,
        notification,
        game
    };

    struct window_data {
        window_type type;

        window_position_t x;
        window_position_t y;

        window_dimension_t width;
        window_dimension_t height;

        window_dimension_t max_width;
        window_dimension_t max_height;

        // TODO: more compact memory?
        bool has_sizing_frame;
        bool has_close_btn;
        bool supports_maximise;
        bool supports_minimise;
        bool is_always_topmost;
        bool is_focused_by_default;

        bool should_preserve_aspect_ratio;

        bool has_os_window_border;
        // TODO: enum PerPixel/PerWindow/None?
        bool supports_transparency;
        bool accepts_input;

        string title;

        static window_data FRS_CORE_EXPORT make_default();
    };
}

#endif //FRUSTRUM_WINDOW_DATA
