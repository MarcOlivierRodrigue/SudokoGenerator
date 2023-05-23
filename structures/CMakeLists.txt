set(HEADERS 
    includes/Grid.h
    includes/DancingLinks.h
    includes/Printer.h)

set(SOURCES 
    src/Grid.cpp
    src/DancingLinks.cpp
    src/Printer.cpp)

add_library(structures ${HEADERS} ${SOURCES})

target_include_directories(structures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(structures PRIVATE util)