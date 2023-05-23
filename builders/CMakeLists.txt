set(HEADERS 
    includes/BuilderBase.h
    includes/BuilderBitMaps.h
    includes/BuilderDancingLinks.h
    includes/Logic.h)

set(SOURCES 
    src/BuilderBase.cpp
    src/BuilderBitMaps.cpp
    src/BuilderDancingLinks.cpp
    src/Logic.cpp)


add_library(builders ${HEADERS} ${SOURCES})

target_include_directories(builders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(builders PRIVATE structures)
target_link_libraries(builders PRIVATE util)