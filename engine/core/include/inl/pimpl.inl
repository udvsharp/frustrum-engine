#ifndef FRUSTRUM_PIMPL_INL
#define FRUSTRUM_PIMPL_INL

#include "frustrum/pimpl.hpp"

#include <new>
#include <type_traits>
#include <utility>
#include <xmemory>
#include <xstddef>
#include <xutility>


namespace frs
{
    // TODO: implement custom allocation
    template<pimpl_suitable_typename WrapperT,
            pimpl_suitable_implementation_typename T,
             type_traits_typename ImplTraits>
    constexpr pimpl<WrapperT, T, ImplTraits>::pimpl()
        : _pimpl {}
    {
        ::std::construct_at(
                reinterpret_cast<T*>(&_pimpl));
    }

    template<pimpl_suitable_typename WrapperT,
            pimpl_suitable_implementation_typename T,
             type_traits_typename ImplTraits>
    template<typename... Args>
    constexpr pimpl<WrapperT, T, ImplTraits>::pimpl(Args&&... args)
        : _pimpl {}
    {
        ::std::construct_at(
                reinterpret_cast<T*>(&_pimpl),
                std::forward<Args>(args)...);
    }

    template<pimpl_suitable_typename WrapperT,
            pimpl_suitable_implementation_typename T,
             type_traits_typename ImplTraits>
    constexpr pimpl<WrapperT, T, ImplTraits>::~pimpl()
    {
        ::std::destroy_at(
                std::launder(
                        reinterpret_cast<T*>(&_pimpl)));
    }

    template<pimpl_suitable_typename WrapperT,
            pimpl_suitable_implementation_typename T,
             type_traits_typename ImplTraits>
    constexpr T* pimpl<WrapperT, T, ImplTraits>::operator->() noexcept
    {
        return reinterpret_cast<T*>(&_pimpl);
    }

    template<pimpl_suitable_typename WrapperT, pimpl_suitable_implementation_typename T, type_traits_typename ImplTraits>
    constexpr T& pimpl<WrapperT, T, ImplTraits>::operator*() const noexcept
    {
        return *std::launder(
                const_cast<T*>(
                        reinterpret_cast<const T*>(&_pimpl)));
    }
} // namespace frs

#endif //FRUSTRUM_PIMPL_INL
