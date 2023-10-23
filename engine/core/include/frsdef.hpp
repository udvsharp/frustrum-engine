#ifndef FRUSTRUM_FRSDEF
#define FRUSTRUM_FRSDEF

#include "frustrum/core.hpp"

#include <cstdint>
#include <format>
#include <memory>
#include <string>
#include <string_view>

namespace frs
{
    // region STD library (for now) aliases
    // region Smart pointers
    template<typename... T>
    using shared_ptr = std::shared_ptr<T...>;

    template<typename... T>
    using unique_ptr = std::unique_ptr<T...>;

    template<typename... T>
    using weak_ptr = std::weak_ptr<T...>;
    // endregion
    // region Common types
    using string =
#if FRS_UNICODE
            std::wstring;
#else
            std::string;
#endif
    using string_view =
#if FRS_UNICODE
            std::wstring_view;
#else
            std::string_view;
#endif
    template<typename... Args>
    using format_string_t =
#if FRS_UNICODE
            std::wformat_string<Args...>;
#else
            std::format_string<Args...>;
#endif

    // TODO: not as performant as static storage (spdlog has fmt::basic_memory_buffer<>)
    using memory_buffer_t = frs::string;
    // endregion
    // endregion

    // Custom defines
    using window_dimension_t = uint32_t;

    using thread_id_t = std::size_t;
} // namespace frs

#endif //FRUSTRUM_FRSDEF
