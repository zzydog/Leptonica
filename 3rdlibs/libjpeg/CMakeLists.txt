
###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 3.0.0)



###############################################################################
# configuration
###############################################################################
enable_testing()
ENABLE_LANGUAGE(C)
include(TestBigEndian)
include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

set( HAVE_UNSIGNED_CHAR 1 )
set( HAVE_UNSIGNED_SHORT 1 )

# We don't support Utah RLE image file format, beacause it 
# needs Utah Raster Toolkit which is not necessary for libjpeg
remove_definitions( -DRLE_SUPPORTED )

check_type_size("unsigned char" UNSIGNED_CHAR)
check_type_size("unsigned short" UNSIGNED_SHORT)

check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)

if( HAVE_STRINGS_H AND NOT HAVE_STRING_H )
    set(NEED_BSD_STRINGS 1)		# Find more details in jconfig.h.in
endif()
check_type_size(size_t SIZE_T)
if( NOT HAVE_SIZE_T )
    set(NEED_SYS_TYPES_H 1)		# Find more details in jconfig.h.in
endif()

# The following code is copied from 
# https://github.com/mmarat/jpeg8d-cmake/blob/master/CMakeLists.txt

# See if compiler supports prototypes.
check_c_source_compiles("
    int testfunction (int arg1, int * arg2); /* check prototypes */
    struct methods_struct { /* check method-pointer declarations */
      int (*error_exit) (char *msgtext);
      int (*trace_message) (char *msgtext);
      int (*another_method) (void);
    };
    int testfunction (int arg1, int * arg2) /* check definitions */
    { return arg2[arg1]; }
    int test2function (void) /* check void arg list */
    { return 0; }
    int main(int argc, char **argv) {return 0;}"
    HAVE_PROTOTYPES
)
if( NOT HAVE_PROTOTYPES )
    message(WARNING "Compiler doesn't know about function prototypes.")
endif()

# checking to see if char is signed
check_c_source_compiles("
    #include <limits.h>
    #if CHAR_MIN >= 0
    # error \"char is unsigned\"
    #endif
    int main() {return 0;}"
    CHAR_IS_SIGNED
)
if( CHAR_IS_SIGNED )
    message(STATUS "Assuming that char is signed on target machine.")
else()
    message(WARNING "Assuming that char is UNsigned on target machine.")
    set(CHAR_IS_UNSIGNED 1)
endif()

# We can't check for bogus warnings, but we can check for errors
check_c_source_compiles("
    typedef struct undefined_structure * undef_struct_ptr; 
    int main(){return 0;}"
    INCOMPLETE_TYPES_NOT_BROKEN
)
if( NOT INCOMPLETE_TYPES_NOT_BROKEN )
    set(INCOMPLETE_TYPES_BROKEN 1)
    message(WARNING "Compiler does not support pointers to structures.")
endif()

# Test whether global names are unique to at least 15 chars
check_c_source_compiles("
    int possibly_duplicate_function () { return 0; }
    int possibly_dupli_function () { return 1; }
    int main() {return 0;}"
    HAVE_LONG_EXTERNAL_NAMES
)
if( NOT HAVE_LONG_EXTERNAL_NAMES )
    message(WARNING "C compiler can't undestand long function names")
    set(NEED_SHORT_EXTERNAL_NAMES 1)
endif()

# checking to see if right shift is signed
check_c_source_compiles("
    #define NTST1 -0x7F7E80CL
    #define NVAL -0x7F7E80B1L
    #if  ((NVAL)>>4) != NTST1
    # error \"right shift is unsigned\"
    #endif
    int main() {return 0;}"
    RIGHT_SHIFT_IS_SIGNED
)
if( RIGHT_SHIFT_IS_SIGNED )
    message(STATUS "Assuming that right shift is signed .")
else()
    set(RIGHT_SHIFT_IS_UNSIGNED 1)
    message(WARNING "Broken compiler can't handle right shift.")
endif()

# superficial check to see if fopen accepts b spec
# assuming that it does, it is not used by the library anyway
check_c_source_compiles("
    #include <stdio.h>
    int main() {
        if (fopen(\"conftestdata\", \"wb\") != NULL)
            exit(0);
        exit(1);
    }"
    HAVE_B_MODE_IN_FOPEN
)
if( NOT HAVE_B_MODE_IN_FOPEN )
    set(DONT_USE_B_MODE 1)
    message(WARNING "Do not have 'b' mode in fopen")
endif()



###############################################################################
# library settings
###############################################################################
if(NOT JPEG)
    set(JPEG libjpeg)
endif()
project(${JPEG} C)
set(JPEG_VERSION "9a")

set(JPEG_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# The configuration file and included directories
configure_file( 
    "${CMAKE_CURRENT_SOURCE_DIR}/jconfig.h.cmakein"
    "${CMAKE_CURRENT_BINARY_DIR}/jconfig.h" @ONLY)
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( HEADERS jdct.h jpegint.h jmemsys.h )
set( LIBRARY_HEADERS 
    jerror.h jmorecfg.h jinclude.h jpeglib.h 
    "${CMAKE_CURRENT_BINARY_DIR}/jconfig.h" )
set( SOURCES 
    jaricom.c jcapimin.c jcapistd.c jcarith.c jccoefct.c jccolor.c 
    jcdctmgr.c jchuff.c jcinit.c jcmainct.c jcmarker.c jcmaster.c 
    jcomapi.c jcparam.c jcprepct.c jcsample.c jctrans.c jdapimin.c 
    jdapistd.c jdarith.c jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c 
    jddctmgr.c jdhuff.c jdinput.c jdmainct.c jdmarker.c jdmaster.c 
    jdmerge.c jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c 
    jfdctfst.c jfdctint.c jidctflt.c jidctfst.c jidctint.c jquant1.c 
    jquant2.c jutils.c jmemmgr.c	# The memory manager
)
# Check out the file 'install.txt'. We have 3 situation here.
if( APPLE )
    list(APPEND SOURCES jmemmac.c)	# Use jmemmac.c for Apple Macintosh
elseif( CMAKE_SIZEOF_VOID_P EQUAL 2 AND MSVC )
    list(APPEND SOURCES jmemdos.c)	# Use jmemdos.c for 16-bit MS-DOS
else()
    list(APPEND SOURCES jmemansi.c)	# Use jmemansi.c for other cases
    #list(APPEND SOURCES jmemname.c)	# Use jmemname.c for other cases
endif()

# Set up the library
add_library ( ${JPEG} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS} )

# The c properties on the target.
set_target_properties(${JPEG} PROPERTIES PREFIX "")
set_target_properties(${JPEG} PROPERTIES LIBRARY_OUTPUT_NAME ${JPEG})


# Compiler/Linker features on the target

if ( WIN32 )
    target_compile_definitions(${JPEG} PRIVATE __WIN32__)
endif()

if ( CYGWIN )
    target_compile_definitions(${JPEG} PRIVATE __CYGWIN__)
endif()

if ( MSVC AND WIN32 )
    # Enable Security Features
    target_compile_options(${JPEG} PRIVATE /GS)
    if (NOT ( MSVC_VERSION LESS 1900 ))
        target_compile_options(${JPEG} PRIVATE /guard:cf)
    endif()
    if (NOT ( MSVC_VERSION LESS 1700 ))
        target_compile_options(${JPEG} PRIVATE /sdl /analyze)
    endif()
    # Multiple Processes Building
    if(MSVC_VERSION GREATER 1400)
        set(PROCESSOR_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
        target_compile_options(${JPEG} PRIVATE "/MP${PROCESSOR_COUNT}")
    endif()
endif()

if ( MINGW AND WIN32 )
    # Enable Security Features
    # http://stackoverflow.com
    # /questions/4492799/undefined-reference-to-stack-chk-fail
    target_link_libraries(${JPEG} INTERFACE -lssp)
    target_compile_options(${JPEG}  PRIVATE  -Wall)
    target_compile_definitions(${JPEG} PRIVATE _FORTIFY_SOURCE=2)
    target_compile_options(${JPEG} PRIVATE -fstack-protector-strong)
    # Enable security APIs
    target_compile_definitions(${JPEG} PRIVATE MINGW_HAS_SECURE_API)
endif()



###############################################################################
# program settings
###############################################################################

# Build all test programs if LEPTONICA is not a sub-project
if(${CMAKE_SOURCE_DIR} STREQUAL ${LEPTONICA_DIRECTORY})
    add_subdirectory( contrib/tools )
endif()
