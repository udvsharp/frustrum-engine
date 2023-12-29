include_guard(GLOBAL)

include(CMakeParseArguments)

include(ext/TypeTraits)

## Constants
set(__modulePublicHeadersDirName "include")
set(__modulePrivateHeadersDirName "private_include")
set(__modulePublicGenDirName "include_generated")
set(__modulePrivateGenDirName "private_include_generated")
set(__moduleSourceDirName "src")

set(__frsTargetNamespace frs)

function (__frs_module_check_structure resultVar module moduleRoot quiet)
    # Public headers dir
    if (NOT EXISTS "${moduleRoot}/${__modulePublicHeadersDirName}")
        set(${resultVar} OFF PARENT_SCOPE)

        if (NOT quiet)
            message(STATUS "${module} module structure is wrong! Public headers dir is non-existent(${moduleRoot}/${__modulePublicHeadersDirName})!")
        endif ()
    endif ()

    # Private headers dir
    if (NOT EXISTS "${moduleRoot}/${__modulePrivateHeadersDirName}")
        set(${resultVar} OFF PARENT_SCOPE)

        if (NOT quiet)
            message(STATUS "${module} module structure is wrong! Private headers dir is non-existent(${moduleRoot}/${__modulePrivateHeadersDirName})!")
        endif ()
    endif ()

    # Sources dir
    if (NOT EXISTS "${moduleRoot}/${__moduleSourceDirName}")
        set(${resultVar} OFF PARENT_SCOPE)

        if (NOT quiet)
            message(STATUS "${module} module structure is wrong! Source dir is non-existent(${moduleRoot}/${__moduleSourceDirName})!")
        endif ()
    endif ()

    set(${resultVar} ON PARENT_SCOPE)
    if (NOT quiet)
        message(STATUS "Module structure checked up: ${module}")
    endif ()
endfunction ()

function (__create_symlink location symlink)
    if (NOT EXISTS "${location}")
        message(FATAL_ERROR "Can't create a symlink - path is non-existent: ${location}")
    endif ()

    file(CREATE_LINK "${location}" "${symlink}" RESULT createLinkStatus SYMBOLIC)

    if (NOT "${createLinkStatus}" STREQUAL "0")
        message(STATUS "Failed to create symlink for ${location}: ${createLinkStatus}")
    endif ()
endfunction ()

function (__frs_module_create_symlinks module sourceDir binaryDir omitPrefix)
    set(publicIncludeSourceDir "${sourceDir}/${__modulePublicHeadersDirName}")
    set(privateIncludeSourceDir "${sourceDir}/${__modulePrivateHeadersDirName}")

    set(publicIncludeBinaryDirPrefix "${binaryDir}/${__modulePublicHeadersDirName}")
    set(privateIncludeBinaryDirPrefix "${binaryDir}/${__modulePrivateHeadersDirName}")

    set(modulePublicIncludeDirSymlink "${publicIncludeBinaryDirPrefix}/${FRS_LIBRARY_NAME}")
    set(modulePrivateIncludeDirSymlink "${privateIncludeBinaryDirPrefix}/${FRS_LIBRARY_NAME}")
    if (NOT omitPrefix)
        string(APPEND modulePublicIncludeDirSymlink "/${module}")
        string(APPEND modulePrivateIncludeDirSymlink "/${module}")
    endif ()

    file(MAKE_DIRECTORY "${publicIncludeBinaryDirPrefix}")
    file(MAKE_DIRECTORY "${privateIncludeBinaryDirPrefix}")

    __create_symlink(${publicIncludeSourceDir} ${modulePublicIncludeDirSymlink})
    __create_symlink(${privateIncludeSourceDir} ${modulePrivateIncludeDirSymlink})
endfunction ()

function (__frs_module_create_gen_dirs module binaryDir omitPrefix)
    file(MAKE_DIRECTORY "${binaryDir}/${__modulePublicGenDirName}")
    file(MAKE_DIRECTORY "${binaryDir}/${__modulePublicGenDirName}/frustrum/generated")

    file(MAKE_DIRECTORY "${binaryDir}/${__modulePrivateGenDirName}")
    file(MAKE_DIRECTORY "${binaryDir}/${__modulePrivateGenDirName}/frustrum/generated")
endfunction ()

function (__frs_module_generate_export_header module binaryDir moduleShort macroPrefix)
    set(customContentFile "${binaryDir}/export_header_content.h")

    set(macroNamePrefix "${macroPrefix}_")
    configure_file("${CMAKE_SOURCE_DIR}/cmake/export_header_content.hpp.in" "${customContentFile}")
    file(READ "${customContentFile}" customContent)

    # TODO: install generated header
    generate_export_header(
            ${module}
            BASE_NAME FRS_${macroPrefix}

            # TODO: include dir as a property or var?
            EXPORT_FILE_NAME "${binaryDir}/${__modulePublicGenDirName}/frustrum/frustrum_${moduleShort}_export.hpp"
            PREFIX_NAME FRS_${macroPrefix}_

            EXPORT_MACRO_NAME EXPORT
            NO_EXPORT_MACRO_NAME NO_EXPORT
            DEPRECATED_MACRO_NAME DEPRECATED
            NO_DEPRECATED_MACRO_NAME NO_DEPRECATED

            STATIC_DEFINE STATIC
            INCLUDE_GUARD_NAME FRUSTRUM_${macroPrefix}_GEN_EXPORT
            DEFINE_NO_DEPRECATED
            CUSTOM_CONTENT_FROM_VARIABLE customContent
            #        EXPORT_FILE_NAME
    )

    add_compile_definitions(
            ${module}
            PRIVATE
            FRS_${macroPrefix}_EXPORTS
    )

    unset(customContent)
    unset(customContentFile)
endfunction ()

function (__frs_module_create_target name type)
    add_library(${name} ${type})

    add_library(${__frsTargetNamespace}::${name} ALIAS ${name})

    # TODO: gflags +sls (Show loader snaps)
    target_include_directories(
            ${name}
            PUBLIC
            $<BUILD_INTERFACE:${binaryDir}/${__modulePublicHeadersDirName}>
            $<BUILD_INTERFACE:${binaryDir}/${__modulePublicGenDirName}>
            $<INSTALL_INTERFACE:include>
            PRIVATE
            $<BUILD_INTERFACE:${binaryDir}/${__modulePrivateHeadersDirName}>
            $<BUILD_INTERFACE:${binaryDir}/${__modulePrivateGenDirName}>
    )
endfunction ()

function (frs_declare_module name type)
    set(options NO_INCLUDE_PREFIX QUIET EXCLUDE_STRUCTURE)
    set(oneValueArgs NAME_SHORT)
    set(multiValueArgs)
    cmake_parse_arguments(PARSE_ARGV 2 FRSDM "${options}" "${oneValueArgs}" "${multiValueArgs}")

    set(moduleName "${name}")
    set(moduleNameShort "${moduleName}")
    set(moduleType "${type}")
    set(sourceDir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(binaryDir "${CMAKE_CURRENT_BINARY_DIR}")
    set(omitIncludeDirPrefix ${FRSDM_NO_INCLUDE_PREFIX})

    if (FRSDM_NAME_SHORT)
        set(moduleNameShort "${FRSDM_NAME_SHORT}")
    endif ()

    string(TOUPPER "${moduleName}" nameUpper)
    string(TOUPPER "${moduleNameShort}" nameShortUpper)

    if (NOT moduleName)
        message(FATAL_ERROR "Module name not provided or empty!")
    endif ()

    # TODO: abstract to __impl method
    # Checks
    __frs_module_check_structure(structureCheck "${name}" "${sourceDir}" ${FRSDM_QUIET})
    if (NOT structureCheck AND FRSDM_EXCLUDE_STRUCTURE)
        message(FATAL_ERROR "Module structure check failed: ${name}")
    endif ()

    # Do a pre-target setup
    __frs_module_create_symlinks(${moduleName} ${sourceDir} ${binaryDir} ${omitIncludeDirPrefix})
    __frs_module_create_gen_dirs(${moduleName} ${binaryDir} ${omitIncludeDirPrefix})

    # Create target
    __frs_module_create_target(${moduleName} ${moduleType})

    # Setup on target
    __frs_module_generate_export_header(${moduleName} ${binaryDir} ${moduleNameShort} ${nameShortUpper})

    message(STATUS "Module setup complete: ${moduleName}")
endfunction ()

# TODO: accept relative path to module include dir or root
# TODO: check if header exists
function (frs_module_generate_type_traits module type typeNoPrefix header)
    if (NOT TARGET ${module})
        message(FATAL_ERROR "Can't generate type traits for non-existent module target!")
    endif ()

    if (NOT type)
        message(FATAL_ERROR "Can't generate type traits - type not specified!")
    endif ()

    string(TOUPPER "${module}" moduleUpper)
    string(TOUPPER "${type}" typeUpper)
    string(TOUPPER "${typeNoPrefix}" typeNoPrefixUpper)

    set(additionalIncludeDirs)
    list(APPEND additionalIncludeDirs "${CMAKE_BINARY_DIR}/engine/${module}/${__modulePublicHeadersDirName}")
    list(APPEND additionalIncludeDirs "${CMAKE_BINARY_DIR}/engine/${module}/${__modulePrivateHeadersDirName}")
    list(APPEND additionalIncludeDirs "${CMAKE_BINARY_DIR}/engine/${module}/${__modulePublicGenDirName}")
    list(APPEND additionalIncludeDirs "${CMAKE_BINARY_DIR}/engine/${module}/${__modulePrivateGenDirName}")

    # TODO: property
    set(genDir "${CMAKE_BINARY_DIR}/engine/${module}/${__modulePublicGenDirName}/frustrum/generated")

    generate_type_traits(
            ${type} ${typeNoPrefix}
            HEADERS "${header}"
            DEPENDENCIES ${module}
            # TODO: property
            ADDITIONAL_INCLUDE_DIRS ${additionalIncludeDirs}
            GEN_DIR "${genDir}"
            HEADER_NAME "${typeNoPrefix}_traits"
            INCLUDE_GUARD_NAME "FRS_${moduleUpper}_${typeNoPrefixUpper}_TYPE_TRAITS" # TODO: get short name for module
    )
endfunction ()
