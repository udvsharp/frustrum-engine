include(CMakeParseArguments)

function (__generate_type_traits_test_file outFile type typeNoPrefix includeStatements)
    set(typeTraitsFileIn "${CMAKE_SOURCE_DIR}/cmake/ext/TypeTraitsTest.cpp.in")
    set(typeTraitsFile "${CMAKE_BINARY_DIR}/ext/TypeTraitsTest_${typeNoPrefix}.cpp")

    # Set variables and generate file
    set(headers "${includeStatements}")
    set(typeName "${type}")
    configure_file(${typeTraitsFileIn} ${typeTraitsFile} @ONLY)

    set(${outFile} "${typeTraitsFile}" PARENT_SCOPE)
endfunction ()

function (__get_type_traits type typeNoPrefix includeStatements additionalIncludeDirs)
    __generate_type_traits_test_file(typeTraitsTestFile ${type} ${typeNoPrefix} ${includeStatements})

    try_run(
            RUN_RESULT COMPILE_RESULT
            ${CMAKE_BINARY_DIR}/TypeTraitsExecutable_${typeNoPrefix}
            ${typeTraitsTestFile}
            CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${additionalIncludeDirs}"
            # LINK_LIBRARIES ${GTT_DEPENDENCIES} # TODO: linking doesn't work with targets
            COMPILE_DEFINITIONS "-DFRS_PLATFORM_WINDOWS -DFRS_GENERATING" # TODO: conditional
            RUN_OUTPUT_VARIABLE RUN_OUT
            COMPILE_OUTPUT_VARIABLE COMPILE_OUT
    )

    if (NOT COMPILE_RESULT)
        message(FATAL_ERROR "Failed to get type traits - test file compilation failed: ${COMPILE_OUT}")
    endif ()

    string(REGEX MATCH "([0-9]+)[\r\n]+([0-9]+)" MATCHES ${RUN_OUT})
    set(${typeNoPrefix}Size ${CMAKE_MATCH_2} PARENT_SCOPE)
    set(${typeNoPrefix}Alignment ${CMAKE_MATCH_1} PARENT_SCOPE)
endfunction ()

function (__generate_type_traits_header typeName typeNoPrefix includeGuardName genDir headerName)
    if (NOT EXISTS "${genDir}")
        message(FATAL_ERROR "Can't generate type traits header for ${typeName} - destination path doesn't exist: ${genDir}")
    endif ()

    set(typeTraitsHeaderIn "${CMAKE_SOURCE_DIR}/cmake/ext/TypeTraitsHeader.hpp.in")
    set(typeTraitsHeader "${genDir}/${headerName}.hpp")

    set(typeSize "${${typeNoPrefix}Size}")
    set(typeAlignment "${${typeNoPrefix}Alignment}")
    configure_file(${typeTraitsHeaderIn} ${typeTraitsHeader} @ONLY)
endfunction ()

function (__generate_include_statements outputVar headersList)
    set(statements "")

    foreach (header IN LISTS headersList)
        list(APPEND statements "${formatted_headers}#include <${header}>\n")
    endforeach ()

    set(${outputVar} "${statements}" PARENT_SCOPE)
endfunction ()

function(__generate_include_dirs outputVar includeDirs targets)
    set(additionalIncludeDirs)

    # Get initial include dirs
    foreach (dir IN LISTS includeDirs)
        list(APPEND additionalIncludeDirs "${dir}")
    endforeach ()

    # Get include dirs from targets
    foreach (target IN LISTS targets)
        get_target_property(INTERFACE_INCLUDE_DIRS ${target} INCLUDE_DIRECTORIES)
        get_target_property(INCLUDE_DIRS ${target} INTERFACE_INCLUDE_DIRECTORIES)

        list(APPEND additionalIncludeDirs "${INTERFACE_INCLUDE_DIRS}" "${INCLUDE_DIRS}")
    endforeach ()

    set(${outputVar} ${additionalIncludeDirs} PARENT_SCOPE)
endfunction ()

function (generate_type_traits typeName typeNameNoPrefix)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs DEPENDENCIES HEADERS ADDITIONAL_INCLUDE_DIRS GEN_DIR INCLUDE_GUARD_NAME HEADER_NAME)
    cmake_parse_arguments(PARSE_ARGV 2 GTT
            "${options}" "${oneValueArgs}" "${multiValueArgs}")

    __generate_include_statements(includeStatements "${GTT_HEADERS}")
    __generate_include_dirs(additionalIncludeDirs "${GTT_ADDITIONAL_INCLUDE_DIRS}" "${GTT_DEPENDENCIES}")

    set(includeGuardName "${GTT_INCLUDE_GUARD_NAME}")
    set(headerName "${GTT_HEADER_NAME}")
    set(genDir "${GTT_GEN_DIR}")

    # TODO: need to re-generate type traits after any changes to dependent classes
    # TODO: should be build target too
    __get_type_traits("${typeName}" "${typeNameNoPrefix}" "${includeStatements}" "${additionalIncludeDirs}")
    __generate_type_traits_header("${typeName}" "${typeNameNoPrefix}" "${includeGuardName}" "${genDir}" "${headerName}")

    message(STATUS "Generated type traits: ${typeName}")
endfunction ()
