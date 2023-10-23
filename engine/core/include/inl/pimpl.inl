#ifndef FRUSTRUM_PIMPL_INL
#define FRUSTRUM_PIMPL_INL

#include "frustrum/pimpl.hpp"

namespace frs
{
    // TODO: implement custom allocation
    template<typename T, type_traits_typename ImplTraits>
    pimpl<T, ImplTraits>::pimpl() : _pimpl {}
    {
        // TODO: check if type_traits are valid
        ::new(::std::addressof(_pimpl)) T();
    }

    template<typename T, type_traits_typename ImplTraits>
    template<typename ...Args>
    pimpl<T, ImplTraits>::pimpl(Args&& ...args)
            : _pimpl {}
    {
        // TODO: check if type_traits are valid
        ::new(::std::addressof(_pimpl)) T(std::forward<Args>()...);
    }

    template<typename T, type_traits_typename ImplTraits>
    pimpl<T, ImplTraits>::~pimpl()
    {
        ::std::destroy_at(
                std::launder(
                        reinterpret_cast<T*>(std::addressof(_pimpl)
                        )
                )
        );
    }

    template<typename T, type_traits_typename ImplTraits>
    T* pimpl<T, ImplTraits>::operator->()
    {
        return reinterpret_cast<T*>(&_pimpl);
    }

    template<typename T, type_traits_typename ImplTraits>
    T& pimpl<T, ImplTraits>::operator*()
    {
        return reinterpret_cast<T*>(&_pimpl);
    }
}

#endif //FRUSTRUM_PIMPL_INL
