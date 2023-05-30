cmake_minimum_required(VERSION 3.14)
project(SudokuGenerator_test VERSION 1.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(HEADERS includes/Grid_test.h)
set(SOURCES src/Util_test.cpp
    src/Grid_test.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADER})
target_link_libraries(${PROJECT_NAME} gtest gtest_main util structures builders)