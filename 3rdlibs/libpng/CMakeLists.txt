
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



###############################################################################
# library settings
###############################################################################

if(NOT PNG)
    set(PNG libpng)
endif()
project(${PNG} C)
set(PNG_VERSION "1.6.20")

# We need the zlib library
if( NOT ZLIB )
    include(FindZLIB)
    if( ZLIB_FOUND AND EXISTS ${ZLIB_INCLUDE_DIRS}/zlib.h )
        set(ZLIB ${ZLIB_LIBRARIES})
        include_directories( ${ZLIB_INCLUDE_DIRS} )
    else()
        message(FATAL_ERROR "Can not Find the 'zlib' package")
    endif()
endif()
# We need the math library
if(NOT WIN32)
    find_library(MATH NAMES m PATHS /usr/lib /usr/local/lib)
    if(NOT MATH)
        message(STATUS "'libm' not found, floating point support disabled")
    endif()
else()
	set(MATH "")	# not needed on windows
endif()

# The configuration file and included directories
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pnglibconf.h.cmakein"
    "${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h" @ONLY)
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
# The files in our project
set( LIBRARY_HEADERS
    png.h pngconf.h ${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h
)
set( HEADERS pngdebug.h pnginfo.h pngpriv.h pngstruct.h )
set( SOURCES
    png.c pngerror.c pngget.c pngmem.c pngpread.c pngread.c pngrio.c 
    pngrtran.c pngrutil.c pngset.c pngtrans.c pngwio.c pngwrite.c 
    pngwtran.c pngwutil.c
)

# Set up the library
add_library(${PNG} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
target_link_libraries(${PNG} ${ZLIB} ${MATH})	# Need zlib and math

# Set properties on the target.
set_target_properties(${PNG} PROPERTIES PREFIX "")
set_target_properties(${PNG} PROPERTIES LIBRARY_OUTPUT_NAME ${PNG})
if ( MSVC )
	set_target_properties(${PNG} PROPERTIES COMPILE_PDB_NAME ${PNG})
endif()


# Compiler/Linker features on the target

if ( WIN32 )
    target_compile_definitions(${PNG} PRIVATE __WIN32__)
endif()

if (CYGWIN)
    target_compile_definitions(${PNG} PRIVATE __CYGWIN__)
endif()

if ( MSVC AND WIN32 )
    # Enable Security Features
    target_compile_options(${PNG} PRIVATE /GS)
    if (NOT ( MSVC_VERSION LESS 1900 ))
        target_compile_options(${PNG} PRIVATE /guard:cf)
    endif()
    if (NOT ( MSVC_VERSION LESS 1700 ))
        target_compile_options(${PNG} PRIVATE /sdl /analyze)
    endif()
    # Multiple Processes Building
    if(MSVC_VERSION GREATER 1400)
        set(PROCESSOR_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
        target_compile_options(${PNG} PRIVATE "/MP${PROCESSOR_COUNT}")
    endif()
endif()

if ( MINGW AND WIN32 )
    # Enable Security Features
    target_compile_options(${PNG} PRIVATE -Wall)
    target_compile_definitions(${PNG} PRIVATE _FORTIFY_SOURCE=2)
    target_compile_options(${PNG} PRIVATE -fstack-protector-strong)
    # Enable security APIs
    target_compile_definitions(${PNG} PRIVATE MINGW_HAS_SECURE_API)
endif()



###############################################################################
# program settings
###############################################################################

# Build all test programs if LEPTONICA is not a sub-project
if(${CMAKE_SOURCE_DIR} STREQUAL ${LEPTONICA_DIRECTORY})

    add_executable(pngvalid contrib/libtests/pngvalid.c)
    target_link_libraries(pngvalid ${PNG})
    add_test(NAME pngvalid COMMAND pngvalid)
    if ( WIN32 )
        target_compile_definitions(pngvalid PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(pngvalid PRIVATE _CRT_SECURE_NO_DEPRECATE)
        target_compile_definitions(pngvalid PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
    endif()

    add_executable(pngstest contrib/libtests/pngstest.c)
    target_link_libraries(pngstest ${PNG})
    add_test(NAME pngstest COMMAND pngstest
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g01.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g02.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g04.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn0g16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn2c08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn2c16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p01.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p02.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p04.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn4a08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn4a16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn6a08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/basn6a16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g01.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g02.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn0g04.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn2c16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbbn3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbgn2c16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbgn3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbrn2c08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbwn0g16.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbwn3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftbyn3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n0g08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n2c08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp0n3p08.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/contrib/pngsuite/ftp1n3p08.png"
    )
    if ( WIN32 )
        target_compile_definitions(pngstest PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(pngstest PRIVATE _CRT_SECURE_NO_DEPRECATE)
        target_compile_definitions(pngstest PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
    endif()
    
    add_executable(pngtest pngtest.c)
    target_link_libraries(pngtest ${PNG})
    add_test(NAME pngtest COMMAND pngtest 
        "${CMAKE_CURRENT_SOURCE_DIR}/pngtest.png")
    if ( WIN32 )
        target_compile_definitions(pngtest PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(pngtest PRIVATE _CRT_SECURE_NO_DEPRECATE)
        target_compile_definitions(pngtest PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
    endif()

endif()
