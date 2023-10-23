find_package(Doxygen)

if (NOT DOXYGEN_FOUND)
    set(messageType STATUS)
    if (FRS_BUILD_DOCS)
        set(messageType FATAL_ERROR)
    endif ()

    message(${messageType} "Doxygen not found, documentation will not be built...")
    return()
endif ()

set(DOXYGEN_IN "${CMAKE_SOURCE_DIR}/Doxyfile.in")
set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
)
