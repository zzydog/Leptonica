

execute_process( 
	COMMAND ${MEMCHECK} ${PROGRAM} ${ARGS}
	OUTPUT_FILE "${OUTPUT}" RESULT_VARIABLE TEST_STATUS )
if( TEST_STATUS )
	message( FATAL_ERROR "Returned failed status ${TEST_STATUS}! \
		Output (if any) is in \"${OUTPUT}\"" )
endif()

if( SOURCE AND DIGEST )
	if( EXISTS ${SOURCE} )
		file( MD5 ${SOURCE} SOURCE )
	else()
		string( MD5 SOURCE ${SOURCE} )
	endif()
	string( TOLOWER ${SOURCE} SOURCE )
	string( TOLOWER ${DIGEST} DIGEST )
	if( ${SOURCE} STREQUAL ${DIGEST} )
		message( STATUS "Test Passed!" )
	else()
		message( FATAL_ERROR "Test Failed, Data corruption is detected!" )
	endif()
endif()
