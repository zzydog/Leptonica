###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(BASE libbase)
project(${BASE} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
file(GLOB LIBRARY_HEADERS jasper/*.h)
set( HEADERS "" )
set( SOURCES
	jas_debug.c jas_getopt.c jas_icc.c jas_iccdata.c
	jas_image.c jas_init.c jas_malloc.c jas_seq.c
	jas_stream.c jas_string.c jas_tmr.c jas_tvp.c jas_version.c
)

# Set up the library
add_library(${BASE} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${BASE} PROPERTIES COMPILE_PDB_NAME ${BASE})
endif()

# Set properties on the target.
set_target_properties(${BASE} PROPERTIES PREFIX "")
set_target_properties(${BASE} PROPERTIES LIBRARY_OUTPUT_NAME ${BASE})

