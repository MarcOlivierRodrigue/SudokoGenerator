cmake_minimum_required(VERSION 3.14)
project(SudokuGenerator VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/util)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/structures)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/builders)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC util)
target_link_libraries(${PROJECT_NAME} PUBLIC structures)
target_link_libraries(${PROJECT_NAME} PUBLIC builders)