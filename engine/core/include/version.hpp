#ifndef FRUSTRUM_VERSION
#define FRUSTRUM_VERSION

#include <cstdint>

#define FRS_VERSION_MAJOR 1
#define FRS_VERSION_MINOR 0
#define FRS_VERSION_PATCH 0
#define FRS_VERSION_TWEAK 0

#define FRS_VERSION_TO_NUMBER(major, minor, patch, tweak) ((major * 1000000) + (minor * 10000) + (patch * 100) + tweak)
#define FRS_VERSION FRS_VERSION_TO_NUMBER(FRS_VERSION_MAJOR, FRS_VERSION_MINOR, FRS_VERSION_PATCH, FRS_VERSION_TWEAK)

namespace frs
{
    constexpr std::uint16_t VERSION_MAJOR = FRS_VERSION_MAJOR;
    constexpr std::uint16_t VERSION_MINOR = FRS_VERSION_MINOR;
    constexpr std::uint16_t VERSION_PATCH = FRS_VERSION_PATCH;
    constexpr std::uint16_t VERSION_TWEAK = FRS_VERSION_TWEAK;

    constexpr std::uint32_t VERSION = FRS_VERSION;
}

#endif //FRUSTRUM_VERSION
