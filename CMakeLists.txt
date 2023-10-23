cmake_minimum_required(VERSION 3.26.4 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(utils/Version)

frs_extract_version()

set(FRS_LIBRARY_NAME "frustrum")

project(
        frustrum
        VERSION ${FRS_VERSION} # TODO: add versioning
        DESCRIPTION "Frustrum game engine" # TODO: cool description
        HOMEPAGE_URL "https://udvsharp.github.io" # TODO: add URL
        LANGUAGES C CXX
)

if(NOT DEFINED FRS_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(FRS_MASTER_PROJECT ON)
    else()
        set(FRS_MASTER_PROJECT OFF)
    endif()
endif()

### Options
# Build options
option(FRS_ENABLE_PCH "Use precompiled headers during build (speeds up compilation times)" OFF)
option(FRS_ENABLE_PIC "Generate PIC (Position-independent-code)" ON) # TODO: check if should disable?
# Target Options
option(FRS_INSTALL "Generate install target" ${FRS_MASTER_PROJECT})
option(FRS_BUILD_EXAMPLES "Build examples" ${FRS_MASTER_PROJECT})
option(FRS_BUILD_TESTS "Build tests" ${FRS_MASTER_PROJECT})
option(FRS_BUILD_BENCHMARK "Build benchmarks with google benchmark library" OFF)
option(FRS_BUILD_DOCS "Build documentation (using Doxygen)" ${FRS_MASTER_PROJECT})
# Instrumentation options
option(FRS_SANITIZE "Enable google sanitizers" OFF)
option(FRS_SANITIZE_ADDRESS "Enable ASAN" OFF)
# Tools options
option(FRS_COMPILER_WARNINGS "Enable compiler warnings (not useful when using as a dependency)" ${FRS_MASTER_PROJECT})
option(FRS_CLANG_TOOLS "Run clang-tools (clang-tidy, clang-format) on project" ${FRS_MASTER_PROJECT})

### Options checks
if (NOT FRS_SANITIZE)
    if (FRS_SANITIZE_ADDRESS)
        message(STATUS "FRS_SANITIZE is off -> FRS_SANITIZE_* options are ignored")
    endif ()
endif ()

if (FRS_CLANG_TOOLS) # TODO: make this work
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    message(STATUS "Clang-tools are enabled")
endif ()

set(CMAKE_POSITION_INDEPENDENT_CODE ${FRS_ENABLE_PIC})

### Modules
include(Module)

if (FRS_BUILD_DOCS)
    include(Doxygen)
endif ()

if (NOT WIN32)
    message(FATAL_ERROR "Only win32 is supported rn")
endif ()

### Binary directory layout setup
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

### Language setup
# C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # TODO: extensions

### CMake setup
# DLL setup
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN ON)

# TODO: move this to a target?
if (WIN32)
    add_compile_definitions(FRS_PLATFORM_WINDOWS)
endif ()

include(Dependencies)

### Subdirectories
add_subdirectory(engine)
add_subdirectory(example)
add_subdirectory(tests)
add_subdirectory(benchmark)
