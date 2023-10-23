#ifndef FRUSTRUM_CORE
#define FRUSTRUM_CORE

#include "frustrum/version.hpp"

#define FRS_EXPAND_STRINGIFY(value) FRS_STRINGIFY(value)
#define FRS_STRINGIFY(value) #value

#ifndef FRS_UNICODE
    #define FRS_UNICODE 1
#endif

#define FRS_CONCAT(lhs, rhs) lhs##rhs
#define FRS_CONCAT3(val1, val2, val3) val1##val2###val3

#define FRS_FORWARD_DECLARE(className) class className;
#define FRS_FORWARD_DECLARE_NAMESPACED(namespaceName, className) \
    namespace namespaceName {                         \
            class className;                          \
    }

#define FRS_DISABLE_COPY_CTOR(className) className(const className& other) = delete;
#define FRS_DISABLE_COPY_OP(className) className& operator=(const className& other) = delete;
#define FRS_DISABLE_COPY(className) \
    FRS_DISABLE_COPY_CTOR(className) \
    FRS_DISABLE_COPY_OP(className)

#define FRS_DISABLE_MOVE_CTOR(className) className(className&& other) noexcept = delete;
#define FRS_DISABLE_MOVE_OP(className) className& operator=(className&& other) noexcept = delete;
#define FRS_DISABLE_MOVE(className) \
    FRS_DISABLE_MOVE_CTOR(className) \
    FRS_DISABLE_MOVE_OP(className)

#define FRS_DEFAULT_COPY_CTOR(className) className(const className& other) = default;
#define FRS_DEFAULT_COPY_OP(className) className& operator=(const className& other) = default;
#define FRS_DEFAULT_COPY(className) \
    FRS_DEFAULT_COPY_CTOR(className) \
    FRS_DEFAULT_COPY_OP(className)

#define FRS_DEFAULT_MOVE_CTOR(className) className(className&& other) noexcept = default;
#define FRS_DEFAULT_MOVE_OP(className) className& operator=(className&& other) noexcept = default;
#define FRS_DEFAULT_MOVE(className) \
    FRS_DEFAULT_MOVE_CTOR(className) \
    FRS_DEFAULT_MOVE_OP(className)

#ifdef FRS_PLATFORM_WINDOWS
    #define FRS_PLATFORM_NAMESPACE_NAME frs::platform::win
    #define FRS_PLATFORM_NAMESPACE      namespace FRS_PLATFORM_NAMESPACE_NAME
#else
    #error Unsupported platform!
#endif

#endif //FRUSTRUM_CORE
