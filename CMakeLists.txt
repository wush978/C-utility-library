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