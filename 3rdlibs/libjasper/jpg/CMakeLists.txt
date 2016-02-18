###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(JPG libjpg)
project(${JPG} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS jpg_cod.h jpg_enc.h jpg_jpeglib.h )
set( SOURCES jpg_val.c jpg_dec.c jpg_enc.c jpg_dummy.c )

# Set up the library
add_library(${JPG} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${JPG} PROPERTIES COMPILE_PDB_NAME ${JPG})
endif()

# Set properties on the target.
set_target_properties(${JPG} PROPERTIES PREFIX "")
set_target_properties(${JPG} PROPERTIES LIBRARY_OUTPUT_NAME ${JPG})
