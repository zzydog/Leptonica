
###############################################################################
# library settings
###############################################################################

# The files in our project
set( HEADERS 
    allheaders.h alltypes.h
    recog.h regutils.h stack.h
    bmf.h bmfdata.h bmp.h ccbord.h
    dewarp.h endianness.h environ.h
    gplot.h heap.h imageio.h jbclass.h
    leptwin.h list.h morph.h pix.h
    stringcode.h sudoku.h watershed.h
    ptra.h queue.h rbtree.h readbarcode.h
    array.h arrayaccess.h bbuffer.h bilateral.h
)
set( SOURCES
    adaptmap.c affine.c
    affinecompose.c arrayaccess.c
    bardecode.c baseline.c bbuffer.c
    bilateral.c bilinear.c binarize.c
    binexpand.c binreduce.c
    blend.c bmf.c bmpio.c bmpiostub.c bootnumgen1.c bootnumgen2.c
    boxbasic.c boxfunc1.c boxfunc2.c boxfunc3.c boxfunc4.c
    bytearray.c ccbord.c ccthin.c classapp.c
    colorcontent.c coloring.c
    colormap.c colormorph.c
    colorquant1.c colorquant2.c
    colorseg.c colorspace.c
    compare.c conncomp.c convertfiles.c
    convolve.c correlscore.c
    dewarp1.c dewarp2.c dewarp3.c dewarp4.c
    dnabasic.c dwacomb.2.c dwacomblow.2.c
    edge.c encoding.c enhance.c
    fhmtauto.c fhmtgen.1.c fhmtgenlow.1.c
    finditalic.c flipdetect.c fliphmtgen.c
    fmorphauto.c fmorphgen.1.c fmorphgenlow.1.c
    fpix1.c fpix2.c gifio.c gifiostub.c
    gplot.c graphics.c graymorph.c
    grayquant.c grayquantlow.c heap.c jbclass.c
    jp2kheader.c jp2kheaderstub.c
    jp2kio.c jp2kiostub.c jpegio.c jpegiostub.c
    kernel.c leptwin.c libversions.c list.c map.c maze.c
    morph.c morphapp.c morphdwa.c morphseq.c
    numabasic.c numafunc1.c numafunc2.c
    pageseg.c paintcmap.c
    parseprotos.c partition.c
    pdfio1.c pdfio1stub.c pdfio2.c pdfio2stub.c
    pix1.c pix2.c pix3.c pix4.c pix5.c
    pixabasic.c pixacc.c pixafunc1.c pixafunc2.c
    pixalloc.c pixarith.c pixcomp.c pixconv.c
    pixlabel.c pixtiling.c pngio.c pngiostub.c
    pnmio.c pnmiostub.c projective.c
    psio1.c psio1stub.c psio2.c psio2stub.c
    ptabasic.c ptafunc1.c ptra.c
    quadtree.c queue.c rank.c rbtree.c
    readbarcode.c readfile.c
    recogbasic.c recogdid.c recogident.c
    recogtrain.c regutils.c
    rop.c ropiplow.c roplow.c
    rotate.c rotateam.c rotateamlow.c
    rotateorth.c rotateshear.c
    runlength.c sarray.c
    scale.c scalelow.c
    seedfill.c seedfilllow.c
    sel1.c sel2.c selgen.c
    shear.c skew.c spixio.c
    stack.c stringcode.c sudoku.c textops.c
    tiffio.c tiffiostub.c
    utils.c viewfiles.c
    warper.c watershed.c
    webpio.c webpiostub.c
    writefile.c zlibmem.c zlibmemstub.c
)

# Default is to Compile a SHARED library
if( NOT LEPTONICA_LIBRARIE_TYPE )
    set(LEPTONICA_LIBRARIE_TYPE "SHARED")
endif()
add_library(${LEPTONICA} ${LEPTONICA_LIBRARIE_TYPE} 
    ${SOURCES} ${HEADERS} ${LIBRARY_HEADERS})
target_link_libraries(${LEPTONICA} ${ZLIB} ${PNG} ${TIFF} ${JPEG})
if( LEPTONICA_LIBRARIE_TYPE STREQUAL "SHARED" )
    # Export all interfaces when compiling a shared library
    target_compile_definitions(${LEPTONICA} PRIVATE LIBLEPT_EXPORTS)
    target_compile_definitions(${LEPTONICA} INTERFACE LIBLEPT_IMPORTS)
endif()

# Set properties on the target.
set_target_properties(${LEPTONICA} PROPERTIES PREFIX "")
set_target_properties(${LEPTONICA} PROPERTIES LIBRARY_OUTPUT_NAME ${LEPTONICA})
if ( MSVC )
    set_target_properties(${LEPTONICA} PROPERTIES COMPILE_PDB_NAME ${LEPTONICA})
endif()

# Compiler/Linker features on the target

if ( WIN32 )
    target_compile_definitions(${LEPTONICA} PRIVATE __WIN32__)
endif()

if (CYGWIN)
    target_compile_definitions(${LEPTONICA} PRIVATE __CYGWIN__)
endif()

if ( MSVC AND WIN32 )
    # Enable Security Features
    target_compile_options(${LEPTONICA} PRIVATE /GS)
    if (NOT ( MSVC_VERSION LESS 1900 ))
        target_compile_options(${LEPTONICA} PRIVATE /guard:cf)
    endif()
    if (NOT ( MSVC_VERSION LESS 1700 ))
        target_compile_options(${LEPTONICA} PRIVATE /sdl /analyze)
    endif()
    # Multiple Processes Building
    if(MSVC_VERSION GREATER 1400)
        set(PROCESSOR_COUNT "$ENV{NUMBER_OF_PROCESSORS}")
        target_compile_options(${LEPTONICA} PRIVATE "/MP${PROCESSOR_COUNT}")
    endif()
endif()

if ( MINGW AND WIN32 )
    # Enable Security Features
    target_compile_definitions(${ZLIB} PRIVATE _FORTIFY_SOURCE=2)
    target_compile_options(${LEPTONICA} PRIVATE -fstack-protector-strong)
    # Enable security APIs
    target_compile_definitions(${LEPTONICA} PRIVATE MINGW_HAS_SECURE_API)
endif()
