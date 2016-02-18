###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(PNM libpnm)
project(${PNM} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS pnm_cod.h pnm_enc.h )
set( SOURCES pnm_cod.c pnm_dec.c pnm_enc.c )

# Set up the library
add_library(${PNM} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${PNM} PROPERTIES COMPILE_PDB_NAME ${PNM})
endif()

# Set properties on the target.
set_target_properties(${PNM} PROPERTIES PREFIX "")
set_target_properties(${PNM} PROPERTIES LIBRARY_OUTPUT_NAME ${PNM})
