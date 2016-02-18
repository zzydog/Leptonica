###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(JP2 libjp2)
project(${JP2} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS jp2_cod.h jp2_dec.h )
set( SOURCES jp2_cod.c jp2_dec.c jp2_enc.c )

# Set up the library
add_library(${JP2} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${JP2} PROPERTIES COMPILE_PDB_NAME ${JP2})
endif()

# Set properties on the target.
set_target_properties(${JP2} PROPERTIES PREFIX "")
set_target_properties(${JP2} PROPERTIES LIBRARY_OUTPUT_NAME ${JP2})
