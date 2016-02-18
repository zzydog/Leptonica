
execute_process( 
	COMMAND ${MEMCHECK} ${PROGRAM} ${ARGS}
	OUTPUT_FILE "${OUTPUT}" RESULT_VARIABLE TEST_STATUS )
if( TEST_STATUS )
	message( FATAL_ERROR "Returned failed status ${TEST_STATUS}! \
		Output (if any) is in \"${OUTPUT}\"" )
endif()

if( SOURCE AND TARGET )
	if( EXISTS ${SOURCE} )
		file( MD5 ${SOURCE} SOURCE )
	else()
		string( MD5 SOURCE ${SOURCE} )
	endif()
	if( EXISTS ${TARGET} )
		file( MD5 ${TARGET} TARGET )
	else()
		string( MD5 TARGET ${TARGET} )
	endif()
	string( TOLOWER ${SOURCE} SOURCE )
	string( TOLOWER ${TARGET} TARGET )
	if( ${SOURCE} STREQUAL ${TARGET} )
		message( STATUS "Test Passed, The data we test is OK, Job done!" )
	else()
		message( FATAL_ERROR "Test Failed, Data corruption is detected!" )
	endif()
endif()
