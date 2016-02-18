
###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 3.0.0)



###############################################################################
# configuration
###############################################################################
enable_testing()
ENABLE_LANGUAGE(C)
include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

# Check to see if we have large file support
check_type_size(off64_t OFF64_T)
# Check for fseeko
check_function_exists(fseeko HAVE_FSEEKO)
# Check for unistd.h
check_include_file(unistd.h Z_HAVE_UNISTD_H)

check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)

if(NOT HAVE_FSEEKO)
    add_definitions(-DNO_FSEEKO)
endif()

if(HAVE_OFF64_T)
    add_definitions(-D_LARGEFILE64_SOURCE=1)
endif()



###############################################################################
# library settings
###############################################################################

if(NOT ZLIB)
    set(ZLIB libzlib)
endif()
project(${ZLIB} C)
set(ZLIB_VERSION "1.2.8")

set(ZLIB_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# The configuration file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/zconf.h.cmakein"
    "${CMAKE_CURRENT_BINARY_DIR}/zconf.h" @ONLY )
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set(HEADERS 
    crc32.h deflate.h gzguts.h inffast.h inffixed.h inflate.h
    inftrees.h trees.h zutil.h
)
set(SOURCES
    adler32.c compress.c crc32.c deflate.c gzclose.c gzlib.c
    gzread.c gzwrite.c inflate.c infback.c inftrees.c
    inffast.c trees.c uncompr.c zutil.c
)
set(LIBRARY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/zconf.h" zlib.h)

# Set up the library
add_library(${ZLIB} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})

# Set properties on the target.
set_target_properties(${ZLIB} PROPERTIES PREFIX "")
set_target_properties(${ZLIB} PROPERTIES LIBRARY_OUTPUT_NAME ${ZLIB})
if(MSVC)
    set_target_properties(${ZLIB} PROPERTIES COMPILE_PDB_NAME ${ZLIB})
endif()

# Compiler/Linker features on the target

if ( WIN32 )
    target_compile_definitions(${ZLIB} PRIVATE __WIN32__)
endif()

if ( CYGWIN )
    target_compile_definitions(${ZLIB} PRIVATE __CYGWIN__)
endif()

if ( MSVC AND WIN32 )
    # Enable Security Features
    target_compile_options(${ZLIB} PRIVATE /GS)
    if (NOT ( MSVC_VERSION LESS 1900 ))
        target_compile_options(${ZLIB} PRIVATE /guard:cf)
    endif()
    if (NOT ( MSVC_VERSION LESS 1700 ))
        target_compile_options(${ZLIB} PRIVATE /sdl /analyze)
    endif()
    # Multiple Processes Building
    if(MSVC_VERSION GREATER 1400)
        set(PROCESSOR_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
        target_compile_options(${ZLIB} PRIVATE "/MP${PROCESSOR_COUNT}")
    endif()
endif()

if ( MINGW AND WIN32 )
    # Enable Security Features
    # http://stackoverflow.com
    # /questions/4492799/undefined-reference-to-stack-chk-fail
    target_link_libraries(${ZLIB} INTERFACE -lssp)
    target_compile_options(${ZLIB} PRIVATE -Wall)
    target_compile_definitions(${ZLIB} PRIVATE _FORTIFY_SOURCE=2)
    target_compile_options(${ZLIB} PRIVATE -fstack-protector-strong)
    # Enable security APIs
    target_compile_definitions(${ZLIB} PRIVATE MINGW_HAS_SECURE_API)
endif()



###############################################################################
# program settings
###############################################################################

# Build all test programs if LEPTONICA is not a sub-project
if(${CMAKE_SOURCE_DIR} STREQUAL ${LEPTONICA_DIRECTORY})

    add_executable(example contrib/test/example.c)
    target_link_libraries(example ${ZLIB})
    if ( WIN32 )
        target_compile_definitions(example PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(example PRIVATE _CRT_SECURE_NO_DEPRECATE)
        target_compile_definitions(example PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
    endif()

    add_executable(minigzip contrib/test/minigzip.c)
    target_link_libraries(minigzip ${ZLIB})
    if ( WIN32 )
        target_compile_definitions(minigzip PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(minigzip PRIVATE _CRT_SECURE_NO_DEPRECATE)
        target_compile_definitions(minigzip PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
    endif()

    if ( HAVE_OFF64_T )
        # For 64bit, we should define _FILE_OFFSET_BITS.
        target_compile_definitions(example PRIVATE _FILE_OFFSET_BITS=64)
        target_compile_definitions(minigzip PRIVATE _FILE_OFFSET_BITS=64)
    endif()

    macro(zlib_tester name program args source digest output)
        add_test(NAME "${name}" COMMAND "${CMAKE_COMMAND}"
            "-DPROGRAM=$<TARGET_FILE:${program}>"
            "-DARGS=${args}" 
            "-DSOURCE=${source}" "-DDIGEST=${digest}" 
            "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${output}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/zlibtester.cmake"
        )
    endmacro()

    zlib_tester( example example "" "" "" "example-result.txt" )

    zlib_tester( minigzip minigzip 
        "-d;${CMAKE_CURRENT_BINARY_DIR}/foo.gz" 
        "${CMAKE_CURRENT_BINARY_DIR}/foo" 
        "4C23A67F52D131D98E1FFEA31EE6CCD6" "minigzip-result.txt" 
    )

endif()