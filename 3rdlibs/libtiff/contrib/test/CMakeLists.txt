# CMake build for libtiff
#
# Copyright © 2015 Open Microscopy Environment / University of Dundee
# Written by Roger Leigh <rleigh@codelibre.net>
#
# 12/25/2015, Modified by Gerron Jo
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.



set(GIFIMAGES images/palette-1c-8b.gif)

set(BMPIMAGES
    images/palette-1c-8b.bmp images/rgb-3c-8b.bmp)

set(PNMIMAGES
    images/minisblack-1c-8b.pgm 
    images/miniswhite-1c-1b.pbm images/rgb-3c-8b.ppm)

# This list should contain all of the TIFF files in the 'images'
# subdirectory which are intended to be used as input images for
# tests.  All of these files should use the extension ".tiff".
set(TIFFIMAGES
    images/quad-tile.jpg.tiff
    images/rgb-3c-16b.tiff images/rgb-3c-8b.tiff 
    images/palette-1c-4b.tiff images/palette-1c-8b.tiff
    images/miniswhite-1c-1b.tiff images/palette-1c-1b.tiff
    images/logluv-3c-16b.tiff images/minisblack-1c-16b.tiff
    images/minisblack-1c-8b.tiff images/minisblack-2c-8b-alpha.tiff
)
# All uncompressed image files
set(UNCOMPRESSEDIMAGES
    images/rgb-3c-8b.tiff
    images/palette-1c-4b.tiff images/palette-1c-8b.tiff
    images/miniswhite-1c-1b.tiff images/palette-1c-1b.tiff
    images/minisblack-1c-16b.tiff images/minisblack-1c-8b.tiff)

add_executable(ascii_tag ascii_tag.c)
target_link_libraries(ascii_tag ${TIFF} ${ZLIB} ${PORT})

add_executable(custom_dir custom_dir.c)
target_link_libraries(custom_dir ${TIFF} ${ZLIB} ${PORT})

add_executable(long_tag long_tag.c check_tag.c)
target_link_libraries(long_tag ${TIFF} ${ZLIB} ${PORT})

add_executable(short_tag short_tag.c check_tag.c)
target_link_libraries(short_tag ${TIFF} ${ZLIB} ${PORT})

add_executable(strip_rw strip_rw.c strip.c test_arrays.c)
target_link_libraries(strip_rw ${TIFF} ${ZLIB} ${PORT})

add_executable(rewrite_tag rewrite_tag.c)
target_link_libraries(rewrite_tag ${TIFF} ${ZLIB} ${PORT})

if(JPEG_SUPPORT)
    add_executable(raw_decode raw_decode.c)
    target_link_libraries(raw_decode ${TIFF} ${ZLIB} ${PORT})
endif()

set(TESTOUTPUT "${CMAKE_CURRENT_BINARY_DIR}/output")
file(MAKE_DIRECTORY "${TESTOUTPUT}")

macro(tiff_test_convert name command1 command2 command3 
        infile outfile validate)
    add_test(NAME "${name}" COMMAND "${CMAKE_COMMAND}"
        "-DCONVERT_COMMAND1=${command1}"
        "-DCONVERT_COMMAND2=${command2}"
        "-DCONVERT_COMMAND3=${command3}"
        "-DINFILE=${infile}"
        "-DOUTFILE=${outfile}"
        "-DTIFFINFO=$<TARGET_FILE:tiffinfo>"
        "-DLIBTIFF=$<TARGET_FILE:${TIFF}>"
        "-DVALIDATE=${validate}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/TiffLibsTester.cmake")
endmacro()

macro(tiff_test_stdout name command infile outfile)
    add_test(NAME "${name}" COMMAND "${CMAKE_COMMAND}"
        "-DSTDOUT_COMMAND=${command}"
        "-DINFILE=${infile}"
        "-DOUTFILE=${outfile}"
        "-DTIFFINFO=$<TARGET_FILE:tiffinfo>"
        "-DLIBTIFF=$<TARGET_FILE:${TIFF}>"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/TiffLibsTester.cmake")
endmacro()

macro(tiff_test_reader name command infile)
    add_test(NAME "${name}" COMMAND "${CMAKE_COMMAND}"
        "-DREADER_COMMAND=${command}"
        "-DINFILE=${infile}"
        "-DTIFFINFO=$<TARGET_FILE:tiffinfo>"
        "-DLIBTIFF=$<TARGET_FILE:${TIFF}>"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/TiffLibsTester.cmake")
endmacro()

macro(add_convert_test_multi program1 program2 program3
      category args1 args2 args3 image validate)
    string(REPLACE " " "^" escaped_commandargs1 "${args1}")
    string(REPLACE " " "^" escaped_commandargs2 "${args2}")
    string(REPLACE " " "^" escaped_commandargs3 "${args3}")
    get_filename_component(name "${image}" NAME)
    get_filename_component(base "${image}" NAME_WE)
    set(testname "${program1}-${category}-${base}")
    if(program1)
        set(command1 
            "$<TARGET_FILE:${program1}>^${escaped_commandargs1}")
    else()
        set(command1)
    endif()
    if(program2)
        set(command2
            "$<TARGET_FILE:${program2}>^${escaped_commandargs2}")
    else()
        set(command2)
    endif()
    if(program3)
        set(command3
            "$<TARGET_FILE:${program3}>^${escaped_commandargs3}")
    else()
        set(command3)
    endif()
    set(infile "${CMAKE_CURRENT_SOURCE_DIR}/${image}")
    set(outfile "${TESTOUTPUT}/${program1}-${category}-${name}")
    string(REGEX REPLACE "\\.tiff\$" "" name "${name}")
    tiff_test_convert("${testname}" "${command1}" "${command2}" 
        "${command3}" "${infile}" "${outfile}" "${validate}" )
endmacro()

macro(add_convert_test program category args image validate)
    add_convert_test_multi(
        "${program}" "" "" 
        "${category}" "${args}" "" ""
        "${image}" "${validate}" 
    )
endmacro()

macro(add_convert_tests_multi program1 program2 program3 
        category args1 args2 args3 images validate)
    foreach(file ${${images}})
        add_convert_test_multi (
            "${program1}" "${program2}" "${program3}" 
            "${category}" 
            "${args1}" "${args2}" "${args3}" 
            "${file}" "${validate}" 
        )
    endforeach()
endmacro()

macro(add_convert_tests program category args images validate)
    foreach(file ${${images}})
        add_convert_test("${program}" "${category}" "${args}" 
            "${file}" "${validate}")
    endforeach()
endmacro()

macro(add_stdout_test program args image)
    string(REPLACE " " "^" escaped_commandargs "${args}")
    get_filename_component(name "${image}" NAME)
    get_filename_component(base "${image}" NAME_WE)
    set(testname "${program}-${base}")
    set(command "$<TARGET_FILE:${program}>^${escaped_commandargs}")
    set(infile "${CMAKE_CURRENT_SOURCE_DIR}/${image}")
    set(outfile "${TESTOUTPUT}/${program}-${name}")
    string(REGEX REPLACE "\\.tiff\$" "" name "${name}")
    tiff_test_stdout("${testname}" "${command}" "${infile}" "${outfile}")
endmacro()

macro(add_reader_test program args image)
    string(REPLACE " " "^" escaped_commandargs "${args}")
    get_filename_component(name "${image}" NAME)
    get_filename_component(base "${image}" NAME_WE)
    set(testname "${program}-${base}")
    set(command "$<TARGET_FILE:${program}>^${escaped_commandargs}")
    set(infile "${CMAKE_CURRENT_SOURCE_DIR}/${image}")
    string(REGEX REPLACE "\\.tiff\$" "" name "${name}")
    tiff_test_reader("${testname}" "${command}" "${infile}")
endmacro()

# BMP
add_convert_test(bmp2tiff palette "" "images/palette-1c-8b.bmp" TRUE)
add_convert_test(bmp2tiff rgb     "" "images/rgb-3c-8b.bmp"     TRUE)

# GIF
add_convert_test(gif2tiff palette "" "images/palette-1c-8b.gif" TRUE)

# PPM
add_convert_test(ppm2tiff miniswhite "" "images/miniswhite-1c-1b.pbm" TRUE)
add_convert_test(ppm2tiff minisblack "" "images/minisblack-1c-8b.pgm" TRUE)
add_convert_test(ppm2tiff rgb        "" "images/rgb-3c-8b.ppm"        TRUE)

# tiffcp
add_convert_test(tiffcp g3       "-c g3"         "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test(tiffcp g31d     "-c g3:1d"      "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test(tiffcp g31dfill "-c g3:1d:fill" "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test(tiffcp g32d     "-c g3:2d"      "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test(tiffcp g32dfill "-c g3:2d:fill" "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test(tiffcp g4       "-c g4"         "images/miniswhite-1c-1b.tiff"  FALSE)
add_convert_test_multi(
    tiffcp tiffcp "" logluv "-c none" "-c sgilog" "" "images/logluv-3c-16b.tiff" FALSE)
add_convert_test_multi(
    tiffcp thumbnail "" thumbnail "g3:1d" "" "" "images/miniswhite-1c-1b.tiff"   FALSE)

# tiffdump
add_reader_test(tiffdump "" "images/miniswhite-1c-1b.tiff")

# tiffinfo
add_reader_test(tiffinfo "-c -D -d -j -s" "images/minisblack-1c-16b.tiff")

# tiffcp split/join
foreach(image ${UNCOMPRESSEDIMAGES})
    list(APPEND ESCAPED_UNCOMPRESSED "${CMAKE_CURRENT_SOURCE_DIR}/${image}")
endforeach()
string(REPLACE ";" "^" ESCAPED_UNCOMPRESSED "${ESCAPED_UNCOMPRESSED}")
add_test(NAME "tiffcp-split" COMMAND "${CMAKE_COMMAND}"
    "-DTESTFILES=${ESCAPED_UNCOMPRESSED}"
    "-DCONJOINED=${TESTOUTPUT}/tiffcp-split-conjoined.tif"
    "-DSPLITFILE=${TESTOUTPUT}/tiffcp-split-split-"
    "-DTIFFCP=$<TARGET_FILE:tiffcp>"
    "-DTIFFSPLIT=$<TARGET_FILE:tiffsplit>"
    "-DLIBTIFF=$<TARGET_FILE:${TIFF}>"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/TiffSplitTester.cmake")
add_test(NAME "tiffcp-split-join" COMMAND "${CMAKE_COMMAND}"
    "-DTESTFILES=${ESCAPED_UNCOMPRESSED}"
    "-DCONJOINED=${TESTOUTPUT}/tiffcp-split-join-conjoined.tif"
    "-DSPLITFILE=${TESTOUTPUT}/tiffcp-split-join-split-"
    "-DRECONJOINED=${TESTOUTPUT}/tiffcp-split-join-reconjoined.tif"
    "-DTIFFCP=$<TARGET_FILE:tiffcp>"
    "-DTIFFSPLIT=$<TARGET_FILE:tiffsplit>"
    "-DLIBTIFF=$<TARGET_FILE:${TIFF}>"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/TiffSplitTester.cmake")

# PDF
add_stdout_test(tiff2pdf "" "images/miniswhite-1c-1b.tiff" TRUE)

# RGBA
add_convert_tests(tiff2rgba default    ""                         TIFFIMAGES TRUE)
# Test rotations
add_convert_tests(tiffcrop  R90        "-R90"                     TIFFIMAGES TRUE)
# Test flip (mirror)
add_convert_tests(tiffcrop  doubleflip "-F both"                  TIFFIMAGES TRUE)
# Test extracting a section 60 pixels wide and 60 pixels high
add_convert_tests(tiffcrop  extract    "-U px -E top -X 60 -Y 60" TIFFIMAGES TRUE)
# Test extracting the first and fourth quarters from the left side.
add_convert_tests(tiffcrop  extractz14 "-E left -Z1:4,2:4"        TIFFIMAGES TRUE)
