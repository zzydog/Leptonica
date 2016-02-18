###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(PGX libpgx)
project(${PGX} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS pgx_cod.h pgx_enc.h )
set( SOURCES pgx_cod.c pgx_dec.c pgx_enc.c )

# Set up the library
add_library(${PGX} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${PGX} PROPERTIES COMPILE_PDB_NAME ${PGX})
endif()

# Set properties on the target.
set_target_properties(${PGX} PROPERTIES PREFIX "")
set_target_properties(${PGX} PROPERTIES LIBRARY_OUTPUT_NAME ${PGX})
