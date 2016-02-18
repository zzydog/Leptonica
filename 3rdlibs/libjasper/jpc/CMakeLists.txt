###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(JPC libjpc)
project(${JPC} C)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# The files in our project
set( LIBRARY_HEADERS "" )
set( HEADERS 	
	jpc_bs.h jpc_cod.h jpc_cs.h jpc_dec.h jpc_enc.h jpc_fix.h 
	jpc_flt.h jpc_math.h jpc_mct.h jpc_mqcod.h jpc_mqdec.h 
	jpc_mqenc.h jpc_qmfb.h jpc_tagtree.h jpc_t1cod.h jpc_t1dec.h 
	jpc_t1enc.h jpc_tsfb.h jpc_t2cod.h jpc_t2dec.h jpc_t2enc.h 
	jpc_util.h 
)
set( SOURCES 
	jpc_bs.c jpc_cs.c jpc_dec.c jpc_enc.c jpc_math.c jpc_mct.c 
	jpc_mqcod.c jpc_mqdec.c jpc_mqenc.c jpc_qmfb.c jpc_tagtree.c 
	jpc_t1cod.c jpc_t1dec.c jpc_t1enc.c jpc_tsfb.c jpc_t2cod.c
	jpc_t2dec.c jpc_t2enc.c jpc_util.c
)

# Set up the library
add_library(${JPC} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${JPC} PROPERTIES COMPILE_PDB_NAME ${JPC})
endif()

# Set properties on the target.
set_target_properties(${JPC} PROPERTIES PREFIX "")
set_target_properties(${JPC} PROPERTIES LIBRARY_OUTPUT_NAME ${JPC})
