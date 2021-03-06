cmake_minimum_required( VERSION 2.8 )

project( c-utility-library )

if (NOT DEFINED IS_SET_OUTPUT_DIRECTORY)
    set(IS_SET_OUTPUT_DIRECTORY 1)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )

if(ENABLE_LOG)
    message( STATUS "ENABLE_LOG" )
    add_definitions(-DENABLE_LOG)
endif()

if(ENABLE_SQLITE3)
    find_package( SQLite3 REQUIRED )
    find_package( Boost REQUIRED COMPONENTS date_time regex )
else()
    find_package( Boost REQUIRED COMPONENTS date_time )
endif()

add_subdirectory( logger )
add_subdirectory( encoding )
add_subdirectory( random_related )
add_subdirectory( sqlite3_wrapper )
add_subdirectory( console )

#
# Testing
#

set( TEST_DATA_DIR "${PROJECT_SOURCE_DIR}/data" )
if (WIN32)
    set( BASE64_EXE "${CMAKE_BINARY_DIR}/bin/base64-console.exe" )
endif()
if (UNIX)
    set( BASE64_EXE "${CMAKE_BINARY_DIR}/bin/base64-console" )
endif()
    
enable_testing()

add_test( base64_encode1 ${BASE64_EXE} "encode" "${TEST_DATA_DIR}/base64-encode-test-input-1.txt" )
set_tests_properties( base64_encode1 
    PROPERTIES
    PASS_REGULAR_EXPRESSION "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="
) 

add_test( base64_decode1 ${BASE64_EXE} "decode" "${TEST_DATA_DIR}/base64-decode-test-input-1.txt" )
set_tests_properties( base64_decode1 
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure."
) 

if(ENABLE_SQLITE3)
    file( COPY "${CMAKE_CURRENT_SOURCE_DIR}/data/check.sql"
        DESTINATION ${CMAKE_BINARY_DIR}
        )
    if(WIN32)
        set( SQLITE3_EXE "${CMAKE_BINARY_DIR}/bin/sqlite3-console.exe" )
        message( FATAL_ERROR "TODO" )
    endif()
    if(UNIX)
        set( SQLITE3_EXE "${CMAKE_BINARY_DIR}/bin/sqlite3-console" )
        add_test( sqlite3-bin ${SQLITE3_EXE} test.db )
        add_test( sqlite3-check sqlite3 test.db ".tables" )
        set_tests_properties( sqlite3-check
            PROPERTIES PASS_REGULAR_EXPRESSION "test_table"
            ) 
        add_test( sqlite3-chmod chmod "u-r" test.db )
        add_test( sqlite3-fail ${SQLITE3_EXE} test.db )
        set_tests_properties( sqlite3-fail
            PROPERTIES PASS_REGULAR_EXPRESSION "Unable to open the database file"
            )
        add_test( sqlite3-clean rm test.db )
    endif()
endif()