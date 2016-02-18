###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(MIF libmif)
project(${MIF} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS mif_cod.h )
set( SOURCES mif_cod.c )

# Set up the library
add_library(${MIF} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${MIF} PROPERTIES COMPILE_PDB_NAME ${MIF})
endif()

# Set properties on the target.
set_target_properties(${MIF} PROPERTIES PREFIX "")
set_target_properties(${MIF} PROPERTIES LIBRARY_OUTPUT_NAME ${MIF})
