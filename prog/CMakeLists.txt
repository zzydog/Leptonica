

###############################################################################
# program settings
###############################################################################

macro(add_prog target)
	set(${target}_src "${ARGN}")
	add_executable(${target} ${ARGN})
	target_link_libraries(${target} ${LEPTONICA})
	if ( WIN32 )
		target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS)
		target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_DEPRECATE)
		target_compile_definitions(${target} PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
	endif()
endmacro(add_prog)

add_prog(adaptmap_dark adaptmap_dark.c)
add_test(NAME adaptmap_dark COMMAND adaptmap_dark
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(adaptmaptest adaptmaptest.c)
add_test(NAME adaptmaptest COMMAND adaptmaptest "map1.jpg"
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(adaptnorm_reg adaptnorm_reg.c)
add_test(NAME adaptnorm_reg COMMAND adaptnorm_reg 
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(affine_reg affine_reg.c)
add_test(NAME affine_reg COMMAND affine_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(alphaops_reg alphaops_reg.c)
add_test(NAME alphaops-gen COMMAND alphaops_reg "generate" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME alphaops-cmp COMMAND alphaops_reg  "compare" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(alphaxform_reg alphaxform_reg.c)
add_test(NAME alphaxform-gen COMMAND alphaxform_reg "generate" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME alphaxform-cmp COMMAND alphaxform_reg  "compare" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(arabic_lines arabic_lines.c)
add_test(NAME arabic_lines COMMAND arabic_lines
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(arithtest arithtest.c)
add_test(NAME arithtest COMMAND arithtest "blendtext.tif" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(autogentest1 autogentest1.c)
add_test(NAME autogentest1 COMMAND autogentest1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(barcodetest barcodetest.c)
add_test(NAME barcodetest COMMAND barcodetest "blendtext.tif" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(baselinetest baselinetest.c)
add_test(NAME baselinetest COMMAND baselinetest 
		"blendtext.tif" "blendout.tif" 
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(bilateral1_reg bilateral1_reg.c)
add_test(NAME bilateral1-gen COMMAND bilateral1_reg "generate" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME bilateral1-cmp COMMAND bilateral1_reg  "compare" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(bilateral2_reg bilateral2_reg.c)
add_test(NAME bilateral2-gen COMMAND bilateral2_reg "generate" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME bilateral2-cmp COMMAND bilateral2_reg  "compare" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(bilinear_reg bilinear_reg.c)
add_test(NAME bilinear_reg COMMAND bilinear_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binarize_reg binarize_reg.c)
add_test(NAME binarize-gen COMMAND binarize_reg "generate" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME binarize-cmp COMMAND binarize_reg  "compare" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binarize_set binarize_set.c)
add_test(NAME binarize_set COMMAND binarize_set "blendtext.tif" 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binarizefiles binarizefiles.c)

add_prog(bincompare bincompare.c)
add_test(NAME bincompare COMMAND bincompare  
		"blendtext.tif" "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binmorph1_reg binmorph1_reg.c)
add_test(NAME binmorph1_reg COMMAND binmorph1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binmorph2_reg binmorph2_reg.c)
add_test(NAME binmorph2_reg COMMAND binmorph2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binmorph3_reg binmorph3_reg.c)
add_test(NAME binmorph3_reg COMMAND binmorph3_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binmorph4_reg binmorph4_reg.c)
add_test(NAME binmorph4_reg COMMAND binmorph4_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(binmorph5_reg binmorph5_reg.c)
add_test(NAME binmorph5_reg COMMAND binmorph5_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blackwhite_reg blackwhite_reg.c)
add_test(NAME blackwhite-gen COMMAND blackwhite_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME blackwhite-cmp COMMAND blackwhite_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blend1_reg blend1_reg.c)
add_test(NAME blend1_reg COMMAND blend1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blend2_reg blend2_reg.c)
add_test(NAME blend2_reg COMMAND blend2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blend3_reg blend3_reg.c)
add_test(NAME blend3-gen COMMAND blend3_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME blend3-cmp COMMAND blend3_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blend4_reg blend4_reg.c)
add_test(NAME blend4-gen COMMAND blend4_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME blend4-cmp COMMAND blend4_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(blendcmaptest blendcmaptest.c)
add_test(NAME blendcmaptest COMMAND blendcmaptest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(boxa1_reg boxa1_reg.c)
add_test(NAME boxa1_reg COMMAND boxa1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(buffertest buffertest.c)
add_test(NAME buffertest COMMAND buffertest 
		"blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(byteatest byteatest.c)
add_test(NAME byteatest COMMAND byteatest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ccbordtest ccbordtest.c)
add_test(NAME ccbordtest COMMAND ccbordtest "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(cctest1 cctest1.c)
add_test(NAME cctest1 COMMAND cctest1 "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ccthin1_reg ccthin1_reg.c)
add_test(NAME ccthin1_reg COMMAND ccthin1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ccthin2_reg ccthin2_reg.c)
add_test(NAME ccthin2_reg COMMAND ccthin2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(cleanpdf cleanpdf.c)
target_compile_definitions(cleanpdf PRIVATE MINGW_HAS_SECURE_API)

add_prog(cmapquant_reg cmapquant_reg.c)
add_test(NAME cmapquant_reg COMMAND cmapquant_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorcontent_reg colorcontent_reg.c)
add_test(NAME colorcontent-gen COMMAND colorcontent_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME colorcontent-cmp COMMAND colorcontent_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(coloring_reg coloring_reg.c)
add_test(NAME coloring-gen COMMAND coloring_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME coloring-cmp COMMAND coloring_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorize_reg colorize_reg.c)
add_test(NAME colorize-gen COMMAND colorize_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME colorize-cmp COMMAND colorize_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colormask_reg colormask_reg.c)
add_test(NAME colormask-gen COMMAND colormask_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME colormask-cmp COMMAND colormask_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colormorphtest colormorphtest.c)
add_test(NAME colormorphtest COMMAND colormorphtest "test8.jpg" 10
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorquant_reg colorquant_reg.c)
add_test(NAME colorquant-gen COMMAND colorquant_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME colorquant-cmp COMMAND colorquant_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorseg_reg colorseg_reg.c)
add_test(NAME colorseg_reg COMMAND colorseg_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorsegtest colorsegtest.c)
add_test(NAME colorsegtest COMMAND colorsegtest  
		"blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorspace_reg colorspace_reg.c)
add_test(NAME colorspace-gen COMMAND colorspace_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME colorspace-cmp COMMAND colorspace_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(colorspacetest colorspacetest.c)
add_test(NAME colorspacetest COMMAND colorspacetest "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(compare_reg compare_reg.c)
add_test(NAME compare-gen COMMAND compare_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME compare-cmp COMMAND compare_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(comparepages comparepages.c)
add_test(NAME comparepages COMMAND comparepages  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(comparetest comparetest.c)
add_test(NAME comparetest COMMAND comparetest  
		"blendtext.tif" "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(compfilter_reg compfilter_reg.c)
add_test(NAME compfilter_reg COMMAND compfilter_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(concatpdf concatpdf.c)
add_test(NAME concatpdf COMMAND concatpdf "${CMAKE_CURRENT_SOURCE_DIR}"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(conncomp_reg conncomp_reg.c)
add_test(NAME conncomp_reg COMMAND conncomp_reg 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(contrasttest contrasttest.c)
add_test(NAME contrasttest COMMAND contrasttest  
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(conversion_reg conversion_reg.c)
add_test(NAME conversion_reg COMMAND conversion_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(convertfilestopdf convertfilestopdf.c)

add_prog(convertfilestops convertfilestops.c)

add_prog(convertformat convertformat.c)
add_test(NAME convertformat COMMAND convertformat 
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(convertsegfilestopdf convertsegfilestopdf.c)

add_prog(convertsegfilestops convertsegfilestops.c)

add_prog(converttogray converttogray.c)
add_test(NAME converttogray COMMAND converttogray 
        "blendtext.tif" "blendout.tif"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(converttopdf converttopdf.c)
add_test(NAME converttopdf COMMAND converttopdf  
        "recog/bootnums" "allfiles"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(converttops converttops.c)
add_test(NAME converttops COMMAND converttops  
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(convolve_reg convolve_reg.c)
add_test(NAME convolve-gen COMMAND convolve_reg "generate"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME convolve-cmp COMMAND convolve_reg  "compare"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(convolvetest convolvetest.c)
add_test(NAME convolvetest COMMAND convolvetest  
        "blendtext.tif" 1 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(cornertest cornertest.c)
add_test(NAME cornertest COMMAND cornertest  
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(croptest croptest.c)
add_test(NAME croptest COMMAND croptest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(croptext croptext.c)

add_prog(dewarp_reg dewarp_reg.c)
add_test(NAME dewarp-gen COMMAND dewarp_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME dewarp-cmp COMMAND dewarp_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarprules dewarprules.c)
add_test(NAME dewarprules COMMAND dewarprules 1 1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarptest1 dewarptest1.c)
add_test(NAME dewarptest1 COMMAND dewarptest1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarptest2 dewarptest2.c)
add_test(NAME dewarptest2 COMMAND dewarptest2 1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarptest3 dewarptest3.c)
add_test(NAME dewarptest3 COMMAND dewarptest3  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarptest4 dewarptest4.c)
add_test(NAME dewarptest4 COMMAND dewarptest4  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dewarptest5 dewarptest5.c)
add_test(NAME dewarptest5 COMMAND dewarptest5  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(digitprep1 digitprep1.c)
add_test(NAME digitprep1 COMMAND digitprep1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(displayboxa displayboxa.c)

add_prog(displaypix displaypix.c)
add_test(NAME displaypix COMMAND displaypix "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(displaypixa displaypixa.c)

add_prog(distance_reg distance_reg.c)
add_test(NAME distance-gen COMMAND distance_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME distance-cmp COMMAND distance_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dithertest dithertest.c)
add_test(NAME dithertest COMMAND dithertest 
        "test8.jpg" "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dna_reg dna_reg.c)
add_test(NAME dna-gen COMMAND dna_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME dna-cmp COMMAND dna_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(dwalineargen dwalineargen.c)
add_test(NAME dwalineargen COMMAND dwalineargen  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(edgetest edgetest.c)
add_test(NAME edgetest COMMAND edgetest 
        "test8.jpg" "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(enhance_reg enhance_reg.c)
add_test(NAME enhance-gen COMMAND enhance_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME enhance-cmp COMMAND enhance_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(equal_reg equal_reg.c)
add_test(NAME equal_reg COMMAND equal_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(expand_reg expand_reg.c)
add_test(NAME expand_reg COMMAND expand_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(extrema_reg extrema_reg.c)
add_test(NAME extrema-gen COMMAND extrema_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME extrema-cmp COMMAND extrema_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(falsecolortest falsecolortest.c)
add_test(NAME falsecolortest COMMAND falsecolortest 1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fcombautogen fcombautogen.c)
add_test(NAME fcombautogen COMMAND fcombautogen  1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fhmtauto_reg fhmtauto_reg.c)
add_test(NAME fhmtauto_reg COMMAND fhmtauto_reg "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fhmtautogen fhmtautogen.c)
add_test(NAME fhmtautogen COMMAND fhmtautogen 1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fileinfo fileinfo.c)
add_test(NAME fileinfo COMMAND fileinfo "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(files_reg files_reg.c)
add_test(NAME files_reg COMMAND files_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(findcorners_reg findcorners_reg.c)
add_test(NAME findcorners-gen COMMAND findcorners_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME findcorners-cmp COMMAND findcorners_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(findpattern1 findpattern1.c)

add_prog(findpattern2 findpattern2.c)
add_test(NAME findpattern2 COMMAND findpattern2  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(findpattern3 findpattern3.c)
add_test(NAME findpattern3 COMMAND findpattern3  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(findpattern_reg findpattern_reg.c)
add_test(NAME findpattern-gen COMMAND findpattern_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME findpattern-cmp COMMAND findpattern_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(flipdetect_reg flipdetect_reg.c)
add_test(NAME flipdetect_reg COMMAND flipdetect_reg "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(flipselgen flipselgen.c)
add_test(NAME flipselgen COMMAND flipselgen  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fmorphauto_reg fmorphauto_reg.c)
add_test(NAME fmorphauto_reg COMMAND fmorphauto_reg "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fmorphautogen fmorphautogen.c)
add_test(NAME fmorphautogen COMMAND fmorphautogen 1
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fpix1_reg fpix1_reg.c)
add_test(NAME fpix1-gen COMMAND fpix1_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME fpix1-cmp COMMAND fpix1_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fpix2_reg fpix2_reg.c)
add_test(NAME fpix2_reg COMMAND fpix2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(fpixcontours fpixcontours.c)

add_prog(gammatest gammatest.c)
add_test(NAME gammatest COMMAND gammatest
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(genfonts_reg genfonts_reg.c)
add_test(NAME genfonts-gen COMMAND genfonts_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME genfonts-cmp COMMAND genfonts_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(gifio_leaktest gifio_leaktest.c)
add_test(NAME gifio_leaktest COMMAND gifio_leaktest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(gifio_reg gifio_reg.c)
add_test(NAME gifio_reg COMMAND gifio_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(graphicstest graphicstest.c)

add_prog(grayfill_reg grayfill_reg.c)
add_test(NAME grayfill_reg COMMAND grayfill_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(graymorph1_reg graymorph1_reg.c)
add_test(NAME graymorph1_reg COMMAND graymorph1_reg "test8.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(graymorph2_reg graymorph2_reg.c)
add_test(NAME graymorph2_reg COMMAND graymorph2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(graymorphtest graymorphtest.c)
add_test(NAME graymorphtest COMMAND graymorphtest 
        "test8.jpg" 10 10 "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(grayquant_reg grayquant_reg.c)
add_test(NAME grayquant_reg COMMAND grayquant_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(hardlight_reg hardlight_reg.c)
add_test(NAME hardlight-gen COMMAND hardlight_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME hardlight-cmp COMMAND hardlight_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(heap_reg heap_reg.c)
add_test(NAME heap_reg COMMAND heap_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(histotest histotest.c)
add_test(NAME histotest COMMAND histotest "test8.jpg" 1
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(insert_reg insert_reg.c)
add_test(NAME insert-gen COMMAND insert_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME insert-cmp COMMAND insert_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ioformats_reg ioformats_reg.c)
add_test(NAME ioformats_reg COMMAND ioformats_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(iotest iotest.c)
add_test(NAME iotest COMMAND iotest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(italictest italictest.c)
add_test(NAME italictest COMMAND italictest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(jbcorrelation jbcorrelation.c)

add_prog(jbrankhaus jbrankhaus.c)

add_prog(jbwords jbwords.c)

add_prog(jp2kio_reg jp2kio_reg.c)
add_test(NAME jp2kio_reg COMMAND jp2kio_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(jpegio_reg jpegio_reg.c)
add_test(NAME jpegio-gen COMMAND jpegio_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME jpegio-cmp COMMAND jpegio_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(kernel_reg kernel_reg.c)
add_test(NAME kernel-gen COMMAND kernel_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME kernel-cmp COMMAND kernel_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(label_reg label_reg.c)
add_test(NAME label-gen COMMAND label_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME label-cmp COMMAND label_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(lineremoval lineremoval.c)
add_test(NAME lineremoval COMMAND lineremoval "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(listtest listtest.c)
add_test(NAME listtest COMMAND listtest "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_adapt livre_adapt.c)
add_test(NAME livre_adapt COMMAND livre_adapt  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_hmt livre_hmt.c)

add_prog(livre_makefigs livre_makefigs.c)
add_test(NAME livre_makefigs COMMAND livre_makefigs  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_orient livre_orient.c)
add_test(NAME livre_orient COMMAND livre_orient  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_pageseg livre_pageseg.c)
add_test(NAME livre_pageseg COMMAND livre_pageseg "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_seedgen livre_seedgen.c)
add_test(NAME livre_seedgen COMMAND livre_seedgen  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(livre_tophat livre_tophat.c)
add_test(NAME livre_tophat COMMAND livre_tophat  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(locminmax_reg locminmax_reg.c)
add_test(NAME locminmax_reg COMMAND locminmax_reg 
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(logicops_reg logicops_reg.c)
add_test(NAME logicops_reg COMMAND logicops_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(lowaccess_reg lowaccess_reg.c)
add_test(NAME lowaccess_reg COMMAND lowaccess_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(maketile maketile.c)

add_prog(maze_reg maze_reg.c)
add_test(NAME maze-gen COMMAND maze_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME maze-cmp COMMAND maze_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(misctest1 misctest1.c)
add_test(NAME misctest1 COMMAND misctest1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(modifyhuesat modifyhuesat.c)

add_prog(morphseq_reg morphseq_reg.c)
add_test(NAME morphseq_reg COMMAND morphseq_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(morphtest1 morphtest1.c)
add_test(NAME morphtest1 COMMAND morphtest1  
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(mtifftest mtifftest.c)
add_test(NAME mtifftest COMMAND mtifftest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(multitype_reg multitype_reg.c)
add_test(NAME multitype-gen COMMAND multitype_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME multitype-cmp COMMAND multitype_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(nearline_reg nearline_reg.c)
add_test(NAME nearline-gen COMMAND nearline_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME nearline-cmp COMMAND nearline_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(newspaper_reg newspaper_reg.c)
add_test(NAME newspaper-gen COMMAND newspaper_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME newspaper-cmp COMMAND newspaper_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(numa1_reg numa1_reg.c)
add_test(NAME numa1_reg COMMAND numa1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(numa2_reg numa2_reg.c)
add_test(NAME numa2_reg COMMAND numa2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(numaranktest numaranktest.c)
add_test(NAME numaranktest COMMAND numaranktest "test8.jpg" 10  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(otsutest1 otsutest1.c)
add_test(NAME otsutest1 COMMAND otsutest1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(otsutest2 otsutest2.c)
add_test(NAME otsutest2 COMMAND otsutest2  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(overlap_reg overlap_reg.c)
add_test(NAME overlap-gen COMMAND overlap_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME overlap-cmp COMMAND overlap_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pagesegtest1 pagesegtest1.c)
add_test(NAME pagesegtest1 COMMAND pagesegtest1 "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pagesegtest2 pagesegtest2.c)
add_test(NAME pagesegtest2 COMMAND pagesegtest2 
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(paint_reg paint_reg.c)
add_test(NAME paint-gen COMMAND paint_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME paint-cmp COMMAND paint_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(paintmask_reg paintmask_reg.c)
add_test(NAME paintmask-gen COMMAND paintmask_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME paintmask-cmp COMMAND paintmask_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(partitiontest partitiontest.c)
add_test(NAME partitiontest COMMAND partitiontest "test8.jpg" 10
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pdfiotest pdfiotest.c)
add_test(NAME pdfiotest COMMAND pdfiotest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pdfseg_reg pdfseg_reg.c)
add_test(NAME pdfseg-gen COMMAND pdfseg_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME pdfseg-cmp COMMAND pdfseg_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixa1_reg pixa1_reg.c)
add_test(NAME pixa1_reg COMMAND pixa1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixa2_reg pixa2_reg.c)
add_test(NAME pixa2_reg COMMAND pixa2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixaatest pixaatest.c)
add_test(NAME pixaatest COMMAND pixaatest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixadisp_reg pixadisp_reg.c)
add_test(NAME pixadisp_reg COMMAND pixadisp_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixalloc_reg pixalloc_reg.c)
add_test(NAME pixalloc_reg COMMAND pixalloc_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixcomp_reg pixcomp_reg.c)
add_test(NAME pixcomp_reg COMMAND pixcomp_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixmem_reg pixmem_reg.c)
add_test(NAME pixmem_reg COMMAND pixmem_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixserial_reg pixserial_reg.c)
add_test(NAME pixserial-gen COMMAND pixserial_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME pixserial-cmp COMMAND pixserial_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pixtile_reg pixtile_reg.c)
add_test(NAME pixtile_reg COMMAND pixtile_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(plottest plottest.c)
add_test(NAME plottest COMMAND plottest
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pngio_reg pngio_reg.c)
add_test(NAME pngio_reg COMMAND pngio_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pnmio_reg pnmio_reg.c)
add_test(NAME pnmio_reg COMMAND pnmio_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(printimage printimage.c)
add_test(NAME printimage COMMAND printimage "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(printsplitimage printsplitimage.c)
add_test(NAME printsplitimage COMMAND printsplitimage 
        "blendtext.tif" 10 10
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(printtiff printtiff.c)
add_test(NAME printtiff COMMAND printtiff "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(projection_reg projection_reg.c)
add_test(NAME projection-gen COMMAND projection_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME projection-cmp COMMAND projection_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(projective_reg projective_reg.c)
add_test(NAME projective_reg COMMAND projective_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(psio_reg psio_reg.c)
add_test(NAME psio-gen COMMAND psio_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME psio-cmp COMMAND psio_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(psioseg_reg psioseg_reg.c)
add_test(NAME psioseg-gen COMMAND psioseg_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME psioseg-cmp COMMAND psioseg_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(pta_reg pta_reg.c)
add_test(NAME pta-gen COMMAND pta_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME pta-cmp COMMAND pta_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ptra1_reg ptra1_reg.c)
add_test(NAME ptra1_reg COMMAND ptra1_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ptra2_reg ptra2_reg.c)
add_test(NAME ptra2_reg COMMAND ptra2_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(quadtreetest quadtreetest.c)
add_test(NAME quadtreetest COMMAND quadtreetest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rank_reg rank_reg.c)
add_test(NAME rank_reg COMMAND rank_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rankbin_reg rankbin_reg.c)
add_test(NAME rankbin-gen COMMAND rankbin_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME rankbin-cmp COMMAND rankbin_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rankhisto_reg rankhisto_reg.c)
add_test(NAME rankhisto-gen COMMAND rankhisto_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME rankhisto-cmp COMMAND rankhisto_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(ranktest ranktest.c)
add_test(NAME ranktest COMMAND ranktest 
        "test8.jpg" 10 10 10 "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rasterop_reg rasterop_reg.c)
add_test(NAME rasterop_reg COMMAND rasterop_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rasteropip_reg rasteropip_reg.c)
add_test(NAME rasteropip-gen COMMAND rasteropip_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME rasteropip-cmp COMMAND rasteropip_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(recogsort recogsort.c)
add_test(NAME recogsort COMMAND recogsort  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(recogtest1 recogtest1.c)
add_test(NAME recogtest1 COMMAND recogtest1  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(reducetest reducetest.c)
add_test(NAME reducetest COMMAND reducetest 
        "blendtext.tif" "blendout.tif" 1 2 3 4
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(removecmap removecmap.c)
add_test(NAME removecmap COMMAND removecmap
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(renderfonts renderfonts.c)
add_test(NAME renderfonts COMMAND renderfonts  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotate1_reg rotate1_reg.c)
add_test(NAME rotate1-gen COMMAND rotate1_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME rotate1-cmp COMMAND rotate1_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotate2_reg rotate2_reg.c)
add_test(NAME rotate2-gen COMMAND rotate2_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME rotate2-cmp COMMAND rotate2_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotatefastalt rotatefastalt.c)
add_test(NAME rotatefastalt COMMAND rotatefastalt  
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotateorth_reg rotateorth_reg.c)
add_test(NAME rotateorth_reg COMMAND rotateorth_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotateorthtest1 rotateorthtest1.c)
add_test(NAME rotateorthtest1 COMMAND rotateorthtest1
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(rotatetest1 rotatetest1.c)
add_test(NAME rotatetest1 COMMAND rotatetest1  
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(runlengthtest runlengthtest.c)
add_test(NAME runlengthtest COMMAND runlengthtest  
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(scale_reg scale_reg.c)
add_test(NAME scale-gen COMMAND scale_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME scale-cmp COMMAND scale_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(scaleandtile scaleandtile.c)

add_prog(scaletest1 scaletest1.c)
add_test(NAME scaletest1 COMMAND scaletest1 
        "test8.jpg" 1 1 "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(scaletest2 scaletest2.c)
add_test(NAME scaletest2 COMMAND scaletest2 "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(seedfilltest seedfilltest.c)
add_test(NAME seedfilltest COMMAND seedfilltest  
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(seedspread_reg seedspread_reg.c)
add_test(NAME seedspread-gen COMMAND seedspread_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME seedspread-cmp COMMAND seedspread_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(selio_reg selio_reg.c)
add_test(NAME selio-gen COMMAND selio_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME selio-cmp COMMAND selio_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(sharptest sharptest.c)
add_test(NAME sharptest COMMAND sharptest 
        "test8.jpg" 1 1 "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(shear1_reg shear1_reg.c)
add_test(NAME shear1-gen COMMAND shear1_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME shear1-cmp COMMAND shear1_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(shear2_reg shear2_reg.c)
add_test(NAME shear2-gen COMMAND shear2_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME shear2-cmp COMMAND shear2_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(sheartest sheartest.c)
add_test(NAME sheartest COMMAND sheartest
        "blendtext.tif" 1 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(showedges showedges.c)
add_test(NAME showedges COMMAND showedges 
        "test8.jpg" "${CMAKE_CURRENT_BINARY_DIR}/testout.jpg"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(skew_reg skew_reg.c)
add_test(NAME skew-gen COMMAND skew_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME skew-cmp COMMAND skew_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(skewtest skewtest.c)
add_test(NAME skewtest COMMAND skewtest
        "blendtext.tif" "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(smallpix_reg smallpix_reg.c)
add_test(NAME smallpix_reg COMMAND smallpix_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(smoothedge_reg smoothedge_reg.c)
add_test(NAME smoothedge_reg COMMAND smoothedge_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(snapcolortest snapcolortest.c)
add_test(NAME snapcolortest COMMAND snapcolortest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(sorttest sorttest.c)
add_test(NAME sorttest COMMAND sorttest "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(splitcomp_reg splitcomp_reg.c)
add_test(NAME splitcomp-gen COMMAND splitcomp_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME splitcomp-cmp COMMAND splitcomp_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(splitimage2pdf splitimage2pdf.c)
add_test(NAME splitimage2pdf COMMAND splitimage2pdf
        "blendtext.tif" 10 10 "blendout.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(string_reg string_reg.c)
add_test(NAME string_reg COMMAND string_reg "blendtext.tif"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(subpixel_reg subpixel_reg.c)
add_test(NAME subpixel-gen COMMAND subpixel_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME subpixel-cmp COMMAND subpixel_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(sudokutest sudokutest.c)
add_test(NAME sudokutest COMMAND sudokutest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(texturefill_reg texturefill_reg.c)
add_test(NAME texturefill-gen COMMAND texturefill_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME texturefill-cmp COMMAND texturefill_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(threshnorm_reg threshnorm_reg.c)
add_test(NAME threshnorm-gen COMMAND threshnorm_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME threshnorm-cmp COMMAND threshnorm_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(translate_reg translate_reg.c)
add_test(NAME translate-gen COMMAND translate_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME translate-cmp COMMAND translate_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(trctest trctest.c)

add_prog(viewertest viewertest.c)

add_prog(warper_reg warper_reg.c)
add_test(NAME warper-gen COMMAND warper_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME warper-cmp COMMAND warper_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(warpertest warpertest.c)
add_test(NAME warpertest COMMAND warpertest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(watershedtest watershedtest.c)
add_test(NAME watershedtest COMMAND watershedtest  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(webpio_reg webpio_reg.c)
add_test(NAME webpio_reg COMMAND webpio_reg  
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(wordboxes_reg wordboxes_reg.c)
add_test(NAME wordboxes-gen COMMAND wordboxes_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME wordboxes-cmp COMMAND wordboxes_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(wordsinorder wordsinorder.c)

add_prog(writemtiff writemtiff.c)

add_prog(writetext_reg writetext_reg.c)
add_test(NAME writetext-gen COMMAND writetext_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME writetext-cmp COMMAND writetext_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(xformbox_reg xformbox_reg.c)
add_test(NAME xformbox-gen COMMAND xformbox_reg "generate"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME xformbox-cmp COMMAND xformbox_reg  "compare"
         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_prog(xtractprotos xtractprotos.c)

add_prog(yuvtest yuvtest.c)

