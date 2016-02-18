###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(BMP libbmp)
project(${BMP} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS bmp_cod.h bmp_enc.h )
set( SOURCES bmp_cod.c bmp_dec.c bmp_enc.c )

# Set up the library
add_library(${BMP} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${BMP} PROPERTIES COMPILE_PDB_NAME ${BMP})
endif()

# Set properties on the target.
set_target_properties(${BMP} PROPERTIES PREFIX "")
set_target_properties(${BMP} PROPERTIES LIBRARY_OUTPUT_NAME ${BMP})
