###############################################################################
#  Detect and load 3rd-party image IO libraries
###############################################################################

# Here is the zlib librarie (required) 
include(FindZLIB)
if(ZLIB_FOUND AND EXISTS ${ZLIB_INCLUDE_DIRS}/zlib.h)
	set(ZLIB ${ZLIB_LIBRARIES})
	include_directories(${ZLIB_INCLUDE_DIRS})
	message(STATUS "Find the 'zlib' package in ${ZLIB_INCLUDE_DIRS}")
	# Here, we should get the libraries and parse the version
	# ...
else()
	set(ZLIB libzlib)
	set(ZLIB_FOUND TRUE)
	message(STATUS "Can't find 'zlib', we'll build it")
	add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libzlib")
	include_directories("${${ZLIB}_SOURCE_DIR}" "${${ZLIB}_BINARY_DIR}")
endif()


# Here is the libtiff library (required, should be searched after zlib)
include(FindTIFF)
if(TIFF_FOUND AND EXISTS ${TIFF_INCLUDE_DIR}/tiff.h)
	set(TIFF ${TIFF_LIBRARIES})
	include_directories(${TIFF_INCLUDE_DIR})
	message(STATUS "Find the 'tiff' package in ${TIFF_INCLUDE_DIR}")
	# Here, we should get the libraries and parse the version
	# ...
else()
	set(TIFF libtiff)
	set(TIFF_FOUND TRUE)
	message(STATUS "Can't find 'tiff', we'll build it")
    add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libtiff")
	include_directories("${${TIFF}_SOURCE_DIR}" "${${TIFF}_BINARY_DIR}")
	# Here, we should parse the version
	# ...
endif()


# Here is the libjpeg library (required, should be searched after zlib)
include(FindJPEG)
if(JPEG_FOUND AND EXISTS ${JPEG_INCLUDE_DIR}/jpeglib.h)
	set(JPEG ${JPEG_LIBRARIES})
	include_directories(${JPEG_INCLUDE_DIR})
	message(STATUS "Find the 'jpeg' package in ${JPEG_INCLUDE_DIR}")
	# Here, we should get the libraries and parse the version
	# ...
else()
	set(JPEG libjpeg)
	set(JPEG_FOUND TRUE)
	message(STATUS "Can't find 'jpeg', we'll build it")
    add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libjpeg")
	include_directories("${${JPEG}_SOURCE_DIR}" "${${JPEG}_BINARY_DIR}")
	# Here, we should parse the version
	# ...
endif()

# Here is the libpng library (required, should be searched after zlib)
include(FindPNG)
if(PNG_FOUND AND EXISTS ${PNG_INCLUDE_DIRS}/png.h)
	set(PNG ${PNG_LIBRARIES})
	include_directories(${PNG_INCLUDE_DIRS})
	message(STATUS "Find the 'png' package in ${PNG_INCLUDE_DIRS}")
	# Here, we should get the libraries and parse the version
	# ...
else()
	set(PNG libpng)
	set(PNG_FOUND TRUE)
	message(STATUS "Can't find 'png', we'll build it")
    add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libpng")
	include_directories("${${PNG}_SOURCE_DIR}" "${${PNG}_BINARY_DIR}")
	# Here, we should parse the version
	# ...
endif()


# Here is the libjasper library (required, should be searched after zlib)
#include(FindJasper)
#if(JASPER_FOUND)
#	set(JASPER ${JASPER_LIBRARIES})
#	include_directories(${JASPER_INCLUDE_DIR})
#	# Here, we should get the libraries and parse the version
#	# ...
#else()
#	set(JASPER libjasper)
#	add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libjasper")
#	include_directories("${${JASPER}_SOURCE_DIR}" "${${JASPER}_BINARY_DIR}")
#	# Here, we should parse the version
#	# ...
#endif()

# Here is the libwebp library (required, should be searched after zlib)
#set(MIN_VER_WEBP "0.4.3")
#find_package(WEBP "${MIN_VER_WEBP}")
#if(WEBP_FOUND)
#	set(WEBP ${WEBP_LIBRARIES})
#	include_directories(${WEBP_INCLUDE_DIR})
	# Here, we should get the libraries and parse the version
	# ...
#else()
#	set(WEBP libwebp)
#	add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/libwebp")
#	include_directories("${${WEBP}_SOURCE_DIR}" "${${WEBP}_BINARY_DIR}")
	# Here, we should parse the version
	# ...
#endif()


# Here is the openexr library (required, should be searched after zlib)
#set(MIN_VER_OPENEXR "1.0.3")
#find_package(OPENEXR "${MIN_VER_OPENEXR}")
#if(OPENEXR_FOUND)
#	set(OPENEXR ${OPENEXR_LIBRARIES})
#	include_directories(${OPENEXR_INCLUDE_DIR})
	# Here, we should get the libraries and parse the version
	# ...
#else()
#	set(OPENEXR libwebp)
#	add_subdirectory("${LEPTONICA_DIRECTORY}/3rdlibs/openexr")
#	include_directories("${${OPENEXR}_SOURCE_DIR}" "${${OPENEXR}_BINARY_DIR}")
	# Here, we should parse the version
	# ...
#endif()

# Here is the GDAL library (required, should be searched after zlib)
# ... Not support yet