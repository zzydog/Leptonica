###############################################################################
# cmake settings
###############################################################################
cmake_minimum_required(VERSION 2.8.11)

###############################################################################
# library settings
###############################################################################
set(WEBP libwebp)
project(${WEBP}  C)
set(WEBP_VERSION "0.4.3")

include(CheckTypeSize)
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckCSourceCompiles)

# The configuration file and included directories
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
)
# The files in our project
set( HEADERS 
	dec/webpi.h dec/vp8li.h dec/vp8i.h dec/decode_vp8.h dec/alphai.h
	dsp/yuv_tables_sse2.h dsp/yuv.h dsp/neon.h dsp/lossless.h dsp/dsp.h
	enc/vp8li.h enc/vp8enci.h 
	enc/histogram.h enc/cost.h enc/backward_references.h 
	mux/muxi.h
	utils/utils.h utils/thread.h utils/rescaler.h utils/random.h
	utils/bit_writer.h utils/bit_reader_inl.h utils/bit_reader.h
	utils/quant_levels_dec.h utils/quant_levels.h utils/huffman_encode.h
	utils/huffman.h utils/filters.h utils/endian_inl.h utils/color_cache.h
)
set( SOURCES 
	dec/webp.c dec/vp8l.c dec/vp8.c dec/tree.c dec/quant.c dec/io.c
	dec/idec.c dec/frame.c dec/buffer.c dec/alpha.c
	demux/demux.c
	dsp/yuv_sse2.c dsp/yuv_mips32.c dsp/yuv.c dsp/upsampling_sse2.c
	dsp/upsampling_neon.c dsp/upsampling.c dsp/lossless_sse2.c
	dsp/lossless_neon.c dsp/lossless_mips32.c dsp/lossless.c
	dsp/enc_sse2.c dsp/enc_neon.c dsp/enc_mips32.c dsp/enc_avx2.c
	dsp/enc.c dsp/dec_sse2.c dsp/dec_neon.c dsp/dec_mips32.c
	dsp/dec_clip_tables.c dsp/dec.c dsp/cpu.c
	dsp/alpha_processing_sse2.c dsp/alpha_processing.c
	enc/backward_references.c enc/analysis.c enc/alpha.c
	enc/quant.c enc/picture_tools.c enc/picture_rescale.c 
	enc/webpenc.c enc/vp8l.c enc/tree.c enc/token.c enc/syntax.c
	enc/histogram.c enc/frame.c enc/filter.c enc/cost.c enc/config.c
	enc/picture_psnr.c enc/picture_csp.c enc/picture.c enc/iterator.c
	mux/muxread.c mux/muxinternal.c mux/muxedit.c
	utils/huffman_encode.c
	utils/utils.c utils/thread.c utils/rescaler.c utils/random.c
	utils/quant_levels_dec.c utils/quant_levels.c utils/bit_reader.c
	utils/huffman.c utils/filters.c utils/color_cache.c utils/bit_writer.c
)
file(GLOB LIBRARY_HEADERS webp/*.h)

# The fllowing code is copied from OpenCV project
if(ANDROID AND ARMEABI_V7A AND NOT NEON)
	foreach(file ${SOURCES})
		if("${file}" MATCHES "_neon.c")
			  set_source_files_properties(
			  "${file}" COMPILE_FLAGS "-mfpu=neon")
		endif()
	endforeach()
endif()
add_definitions(-DWEBP_USE_THREAD)	# Enable thread support
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

# Set up the library
add_library(${WEBP} STATIC ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
target_link_libraries(${WEBP} )

# Set properties on the target.
set_target_properties(${WEBP} PROPERTIES PREFIX "")
set_target_properties(${WEBP} PROPERTIES LIBRARY_OUTPUT_NAME ${WEBP})
if(MSVC)
	set_target_properties(${WEBP} PROPERTIES COMPILE_PDB_NAME ${WEBP})
endif()

