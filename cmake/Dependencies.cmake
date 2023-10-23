#include(FetchContent)
#
#FetchContent_Declare(
#        spdlog
#        GIT_REPOSITORY https://github.com/gabime/spdlog.git
#        GIT_TAG v1.x
#)
#
#FetchContent_GetProperties(spdlog)
#if (NOT spdlog_POPULATED)
#    FetchContent_Populate(spdlog)
#
#    option(SPDLOG_BUILD_SHARED OFF)
#    option(SPDLOG_ENABLE_PCH ${FRS_ENABLE_PCH})
#    option(SPDLOG_USE_STD_FORMAT ON)
#    option(SPDLOG_NO_EXCEPTIONS ON)
#    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
#endif()
