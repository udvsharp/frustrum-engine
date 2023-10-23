macro (__frs_parse_version_part outVariable versionMacro fileContents)
    string(REGEX MATCH "${versionMacro} ([0-9]+)" _ "${fileContents}")
    if (NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from the version.hpp header")
    endif ()
    set(${outVariable} ${CMAKE_MATCH_1})
endmacro ()

function (frs_extract_version)
    file(READ "${CMAKE_SOURCE_DIR}/engine/core/include/version.hpp" fileContents)

    set(versionMacroPrefix "FRS_VERSION")

    __frs_parse_version_part(versionMajor "${versionMacroPrefix}_MAJOR" "${fileContents}")
    __frs_parse_version_part(versionMinor "${versionMacroPrefix}_MINOR" "${fileContents}")
    __frs_parse_version_part(versionPatch "${versionMacroPrefix}_PATCH" "${fileContents}")
    __frs_parse_version_part(versionTweak "${versionMacroPrefix}_TWEAK" "${fileContents}")

    set(FRS_VERSION_MAJOR ${versionMajor} PARENT_SCOPE)
    set(FRS_VERSION_MINOR ${versionMinor} PARENT_SCOPE)
    set(FRS_VERSION_PATCH ${versionPatch} PARENT_SCOPE)
    set(FRS_VERSION_TWEAK ${versionTweak} PARENT_SCOPE)
    set(FRS_VERSION "${versionMajor}.${versionMinor}.${versionPatch}.${versionTweak}" CACHE STRING "Frustrum engine version" FORCE)

    message(STATUS "Frustrum engine version ${FRS_VERSION}")
endfunction ()
