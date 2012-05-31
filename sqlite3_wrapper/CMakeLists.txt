if(ENABLE_SQLITE3)

project( sqlite3_wrapper )

include_directories( ${SQLITE3_INCLUDE_DIRS} )
add_definitions( ${SQLITE3_DEFINITIONS} )

add_library( sqlite3_wrapper STATIC exception.cpp sqlite3_wrapper.cpp Db.cpp Table.cpp Row.cpp)

endif()