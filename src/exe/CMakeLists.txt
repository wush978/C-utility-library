project( exe )
include_directories( BEFORE "../dll" )
add_executable( exe exe.cpp )
target_link_libraries( exe dll_1 )