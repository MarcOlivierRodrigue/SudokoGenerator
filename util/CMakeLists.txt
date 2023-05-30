set(HEADERS
    includes/Util.h
    includes/Types.h)

set(SOURCES
    src/Util.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(util ${HEADERS} ${SOURCES})

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)