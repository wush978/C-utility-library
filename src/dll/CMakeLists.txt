project( dll_dll )
add_library( dll_dll SHARED dll.cpp )

project( dll_exe )
add_executable( dll_exe exe.cpp )
target_link_libraries( dll_exe dll_dll )