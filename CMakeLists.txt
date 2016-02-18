
###############################################################################
# cmake settings
###############################################################################

cmake_minimum_required(VERSION 3.0.0)

# In-source builds are disabled.
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
        "CMake generation is not possible within the source directory!\n "
        "Remove CMakeCache.txt and try again from another folder, e.g.:\n "
        "rm CMakeCache.txt\n "
        "mkdir build\n "
        "cd build\n "
        "cmake ..\n "
    )
endif()

set(CMAKE_BINARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_OUTPUT_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake")



###############################################################################
# configuration
###############################################################################

enable_testing()
enable_language(C)

include(TestBigEndian)
include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

set(LEPTONICA_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})
set(LEPTONICA_LIBRARIE ${CMAKE_CURRENT_SOURCE_DIR})
set(LEPTONICA_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

macro(check_keyword_exists KEYWORD VARIABLE)
    # See if compiler supports prototypes.
    check_c_source_compiles(
        "
        ${KEYWORD} int test() { return 0; }
        int main(int argc, char **argv) { return test(); }
        "
        HAVE_${KEYWORD}
    )
    set(VARIABLE HAVE_${KEYWORD})
endmacro()
check_keyword_exists(static HAVE_KEYWORD_INLINE)
if( NOT HAVE_KEYWORD_INLINE )
    add_definitions( -Dinline=__inline )
endif()



###############################################################################
# library settings
###############################################################################

if( NOT LEPTONICA )
    set(LEPTONICA liblept)
endif()
project(${LEPTONICA} C CXX)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 73)
set(VERSION_PLAIN ${VERSION_MAJOR}.${VERSION_MINOR})
set(LEPTONICA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

include(cmake/Find3rdLibs.cmake)    # Here, we find all libraries
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config_auto.h.cmakein
    ${CMAKE_CURRENT_BINARY_DIR}/config_auto.h @ONLY
)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src") # Build the library


# The configuration file and included directories
include_directories( 
    "${${LEPTONICA}_SOURCE_DIR}" "${${LEPTONICA}_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/prog" "${CMAKE_CURRENT_BINARY_DIR}/prog"
)


###############################################################################
# program settings
###############################################################################

# Build all test programs if it's not a sub-project
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/prog")    # Build programs
endif()

