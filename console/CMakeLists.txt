
project( base64-console )
add_executable( base64-console base64-console.cpp )
target_link_libraries( base64-console encoding )

project( shuffle-console )
add_executable( shuffle-console shuffle-console.cpp )
target_link_libraries( shuffle-console random_related )

project( logger-console )
add_executable( logger-console logger-console.cpp )
target_link_libraries( logger-console logger )

if(ENABLE_SQLITE3)
    project( sqlite3-console )
    message( STATUS " SQLITE3_INCLUDE_DIRS: ${SQLITE3_INCLUDE_DIRS}")
    message( STATUS " SQLITE3_LIBRARIES: ${SQLITE3_LIBRARIES}")
    
    include_directories( ${SQLITE3_INCLUDE_DIRS} )
    add_executable( sqlite3-console sqlite3-console.cpp )
    if(ENABLE_LOG)
        target_link_libraries( sqlite3-console sqlite3_wrapper encoding ${SQLITE3_LIBRARIES} logger )
    else()
        target_link_libraries( sqlite3-console sqlite3_wrapper encoding ${SQLITE3_LIBRARIES} )
    endif()
endif()