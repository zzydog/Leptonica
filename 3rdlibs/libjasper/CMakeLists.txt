###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(JASPER libjasper)
project(${JASPER}  C)
set(JASPER_VERSION "1.900.1")

include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

# The sub components we won't support.
#add_definitions(
#	-DEXCLUDE_MIF_SUPPORT -DEXCLUDE_PNM_SUPPORT -DEXCLUDE_BMP_SUPPORT 
#	-DEXCLUDE_RAS_SUPPORT -DEXCLUDE_JPG_SUPPORT -DEXCLUDE_PGX_SUPPORT
#)

# The fllowing code is copied from OpenCV project
if(WIN32 AND NOT MINGW)
	add_definitions(-DJAS_WIN_MSVC_BUILD)
endif(WIN32 AND NOT MINGW)

# The configuration file and included directories
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}"
)

# Now, compile all components
#add_subdirectory(base)
#add_subdirectory(bmp)		# Don't define EXCLUDE_BMP_SUPPORT
#add_subdirectory(jp2)		# Don't define EXCLUDE_JP2_SUPPORT
#add_subdirectory(jpc)		# Don't define EXCLUDE_JPC_SUPPORT
#add_subdirectory(jpg)		# Don't define EXCLUDE_JPG_SUPPORT
#add_subdirectory(mif)		# Don't define EXCLUDE_MIF_SUPPORT
#add_subdirectory(pgx)		# Don't define EXCLUDE_PGX_SUPPORT
#add_subdirectory(pnm)		# Don't define EXCLUDE_PNM_SUPPORT
#add_subdirectory(ras)		# Don't define EXCLUDE_RAS_SUPPORT

# The files in our project
set( HEADERS 
	mif/mif_cod.h
	pgx/pgx_cod.h pgx/pgx_enc.h
	pnm/pnm_cod.h pnm/pnm_enc.h
	ras/ras_cod.h ras/ras_enc.h
	jp2/jp2_cod.h jp2/jp2_dec.h
	jpc/jpc_bs.h jpc/jpc_cod.h jpc/jpc_cs.h jpc/jpc_dec.h
	jpc/jpc_enc.h jpc/jpc_fix.h jpc/jpc_flt.h jpc/jpc_mct.h
	jpc/jpc_math.h jpc/jpc_qmfb.h jpc/jpc_util.h jpc/jpc_tsfb.h
	jpc/jpc_mqcod.h jpc/jpc_mqdec.h jpc/jpc_t1cod.h jpc/jpc_t1dec.h
	jpc/jpc_t2cod.h jpc/jpc_t2dec.h jpc/jpc_t2enc.h
	jpc/jpc_mqenc.h jpc/jpc_t1enc.h jpc/jpc_tagtree.h
)
set( SOURCES 
	mif/mif_cod.c
	pgx/pgx_cod.c pgx/pgx_dec.c pgx/pgx_enc.c
	pnm/pnm_cod.c pnm/pnm_dec.c pnm/pnm_enc.c
	ras/ras_cod.c ras/ras_dec.c ras/ras_enc.c
	base/jas_cm.c base/jas_debug.c base/jas_getopt.c base/jas_icc.c
	base/jas_iccdata.c base/jas_image.c base/jas_init.c base/jas_tvp.c 
	base/jas_seq.c base/jas_stream.c base/jas_string.c base/jas_tmr.c
	base/jas_version.c base/jas_malloc.c
	jp2/jp2_cod.c jp2/jp2_dec.c jp2/jp2_enc.c
	jpc/jpc_cs.c jpc/jpc_dec.c jpc/jpc_enc.c jpc/jpc_math.c
	jpc/jpc_mct.c jpc/jpc_mqcod.c jpc/jpc_mqdec.c jpc/jpc_mqenc.c
	jpc/jpc_qmfb.c jpc/jpc_t1cod.c jpc/jpc_t1dec.c jpc/jpc_t1enc.c
	jpc/jpc_t2cod.c jpc/jpc_t2dec.c jpc/jpc_t2enc.c jpc/jpc_tagtree.c
	jpc/jpc_tsfb.c jpc/jpc_util.c jpc/jpc_bs.c
)
file(GLOB LIBRARY_HEADERS jasper/*.h)

# Set up the library
add_library(${JASPER} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
target_link_libraries( ${JASPER} )

# Set properties on the target.
set_target_properties(${JASPER} PROPERTIES PREFIX "")
set_target_properties(${JASPER} PROPERTIES LIBRARY_OUTPUT_NAME ${JASPER})
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	set_target_properties(${JASPER} PROPERTIES COMPILE_PDB_NAME ${JASPER})
endif()

