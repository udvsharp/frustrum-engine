/**
 * @file  pimpl.hpp
 * @brief Contains the definition of pimpl template
 */

#ifndef FRUSTRUM_PIMPL
#define FRUSTRUM_PIMPL

#include "frustrum/core.hpp"

#include <memory>
#include <type_traits>

namespace frs
{
    template<typename T>
    struct type_traits;

    /// @brief concept to check if type traits instantiation is valid
    template<typename T>
    concept type_traits_typename =
#ifndef FRS_GENERATING // To prevent compile errors in generated files
            requires(T type) {
                {
                    T::size
                } -> std::convertible_to<std::size_t>;
                T::size >= 0;

                {
                    T::alignment
                } -> std::convertible_to<std::size_t>;
                T::alignment >= 0;
            };
#else
            true; // Condition is always satisfied
#endif

    /// @brief concept to check if implementation (inside Pimpl object) is suitable
    template<typename T>
    concept pimpl_suitable_implementation_typename = requires(T type) {
        true;

        // TODO: should be incomplete during GENERATING stage
        // TODO: should have a type_traits instantiation
    };

    /// @brief concept to check if container (will have pimpl object inside) is suitable
    template<typename T>
    concept pimpl_suitable_typename = requires(T type) {
        true;

        // TODO: should not have constructors defined in headers(inline)
        // Constructor should be defined in implementation file and exported

        // TODO: should have no public interface usage of pimpl object
    };

    /**
     * @brief  This template class provides a wrapper for PIMPL idiom implementation class.
     *         It manages lifetime of pimpl (implementation pointer) and provides a handy way to access it members.
     * @tparam T Type of implementation class.
     */
    // TODO: maybe we can declare a concept to validate implementation?
    template<
            pimpl_suitable_typename WrapperT,
            pimpl_suitable_implementation_typename T,
            type_traits_typename ImplTraits = type_traits<T>>
    class pimpl final
    {
    public:
        constexpr pimpl();
        template<typename... Args>
        constexpr explicit pimpl(Args&&...);
        constexpr ~pimpl();

    public:
        constexpr T* operator->() noexcept;
        constexpr T& operator*() const noexcept;

    private:
        /// Implementation object storage (not a pointer)
        std::aligned_storage_t<ImplTraits::size, ImplTraits::alignment> _pimpl;
    };
} // namespace frs

// region Macros
/**
 * @def FRS_PLATFORM_IMPL(className)
 * @brief Evaluates to the platform-specific name of class.
 *        "window" -> "windows_window" on Win32.
 * @param className - Platform-agnostic name of the class to be converted to platform-specific.
 */
/**
 * @def FRS_PLATFORM_IMPL_NAMESPACED(className)
 * @brief Evaluates to the platform-specific name of class, prefixed with namespace.
 *        "window" -> "::frs::platform::win::windows_window" on Win32.
 * @param className - Platform-agnostic name of the class to be converted to platform-specific.
 */
/**
 * @def FRS_FORWARD_DECLARE_PLATFORM_IMPL(className)
 * @brief Forward-declares platform implementation class for className.
 * @param className - Platform-agnostic name of the class to be converted to platform-specific and pre-declared.
 */
#if FRS_PLATFORM_WINDOWS
    #define FRS_PLATFORM_IMPL(className) windows##_##className
#else
    #define FRS_PLATFORM_IMPL(className)
    #error Platform not supported
#endif
#define FRS_PLATFORM_IMPL_NAMESPACED(className) ::FRS_PLATFORM_NAMESPACE_NAME::FRS_PLATFORM_IMPL(className)
#define FRS_FORWARD_DECLARE_PLATFORM_IMPL(className) \
    FRS_PLATFORM_NAMESPACE                           \
    {                                                \
        class FRS_PLATFORM_IMPL(className);          \
    }

/**
 * @def FRS_DECLARE_TYPE_TRAITS(className)
 * @brief Declares empty type traits(zero-initialized) to use when compiling test file.
 *        After real type traits class is generated, evaluates to nothing.
 * @param className - Platform-agnostic name of the class to be converted to platform-specific for use it type_traits template param.
 */
#ifdef FRS_GENERATING ///< Will be omitted during generating step to avoid compile errors
    #define FRS_DECLARE_TYPE_TRAITS(className)                            \
        namespace frs                                                     \
        {                                                                 \
            template<>                                                    \
            struct type_traits<FRS_PLATFORM_IMPL_NAMESPACED(className)> { \
                static constexpr std::size_t size      = 0;               \
                static constexpr std::size_t alignment = 0;               \
            };                                                            \
        }


    // #define FRS_TYPE_TRAITS_HEADER(className) "frustrum/version.hpp" // TODO: maybe a better header? (need empty one to work)
#else
    #define FRS_DECLARE_TYPE_TRAITS(className)

    // TODO: would be cool to figure out how to write #include FRS_TYPE_TRAITS_HEADER(window)
    // #define FRS_TYPE_TRAITS_HEADER_IMPL(className) "frustrum/generated/", FRS_EXPAND_STRINGIFY(FRS_PLATFORM_IMPL(className)), "_traits.hpp"
    // #define FRS_TYPE_TRAITS_HEADER(className) FRS_EXPAND_STRINGIFY(FRS_TYPE_TRAITS_HEADER_IMPL(className))
#endif

/**
 * @def FRS_FORWARD_DECLARE_PLATFORM_IMPL(className)
 * @brief Declares both @see type_traits and platform-specific class.
 *        This macro is a shorthand for using both @see FRS_FORWARD_DECLARE_PLATFORM_IMPL(className)
 *        and @see FRS_DECLARE_TYPE_TRAITS(className).
 * @param className - Platform-agnostic name of the class to be used.
 */
#define FRS_DECLARE_PIMPL(className)             \
    FRS_FORWARD_DECLARE_PLATFORM_IMPL(className) \
    FRS_DECLARE_TYPE_TRAITS(className)

#ifndef FRS_GENERATING ///< Implementation is omitted when generating
    #include "frustrum/inl/pimpl.inl"
#endif
// endregion

#endif //FRUSTRUM_PIMPL
