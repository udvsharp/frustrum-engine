include(GenerateExportHeader)

# TODO: create frustrum target
frs_declare_module(
        core
        SHARED
        NAME_SHORT "core"
        NO_INCLUDE_PREFIX
)

target_sources(
        core
        PUBLIC
        include/core.hpp
        include/engine.hpp
        include/window.hpp
        include/frsdef.hpp
        include/pimpl.hpp

        include/debug/assertions.hpp
        include/debug/level.hpp
        include/debug/logger.hpp
        include/debug/message.hpp

        include/inl/pimpl.inl

        PRIVATE
        private_include/platform/win/win_window.hpp
        private_include/platform/win/win_logger.hpp

        src/engine.cpp
        src/window.cpp
        src/threads.cpp

        src/debug/logger.cpp
        src/debug/message.cpp

        src/platform/win/win_window.cpp
        src/platform/win/win_logger.cpp
        src/platform/win/dllmain.cpp
)

#target_link_libraries(core PRIVATE spdlog::spdlog)

set_target_properties(
        core
        PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_compile_definitions(
        core
        PUBLIC
        UNICODE # Win32 Define
        STRICT # Win32 Define
        WIN32_LEAN_AND_MEAN # Win32 Define

        # TODO: move to the build system setup
        FRS_DEBUG=1
        FRS_UNICODE=1
)

frs_module_generate_type_traits(core
        "frs::platform::win::windows_window"
        "windows_window"
        "frustrum/platform/win/win_window.hpp")
frs_module_generate_type_traits(core
        "frs::platform::win::windows_logger"
        "windows_logger"
        "frustrum/platform/win/win_logger.hpp")
