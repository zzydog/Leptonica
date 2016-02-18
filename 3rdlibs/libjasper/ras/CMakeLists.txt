###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(RAS libras)
project(${RAS} C)

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS ras_cod.h ras_enc.h )
set( SOURCES ras_cod.c ras_dec.c ras_enc.c )

# The definitions
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

# Set up the library
add_library(${RAS} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})

# Set properties on the target.
set_target_properties(${RAS} PROPERTIES PREFIX "")
set_target_properties(${RAS} PROPERTIES LIBRARY_OUTPUT_NAME ${RAS})
if(MSVC)
	set_target_properties(${RAS} PROPERTIES COMPILE_PDB_NAME ${RAS})
endif()
