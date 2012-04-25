
project( base64-console )
add_executable( base64-console base64-console.cpp )
target_link_libraries( base64-console encoding )

project( shuffle-console )
add_executable( shuffle-console shuffle-console.cpp )
target_link_libraries( shuffle-console random_related )