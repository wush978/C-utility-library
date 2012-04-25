cmake_minimum_required( VERSION 2.8 )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (DEFINED PROJECT_NAMESPACE)
else()
  set( PROJECT_NAMESPACE WUSH_UTILITY )
endif()

configure_file (
  "${PROJECT_SOURCE_DIR}/C-utility-library.config.h.in"
  "${PROJECT_BINARY_DIR}/C-utility-library.config.h"
)
include_directories( ${PROJECT_BINARY_DIR} )

add_subdirectory( encoding )
# add_subdirectory( utility )
add_subdirectory( console )

#
# Testing
#

set( TEST_DATA_DIR "${PROJECT_SOURCE_DIR}/data" )
set( BASE64_EXE "${CMAKE_BINARY_DIR}/bin/base64-console.exe" )
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
