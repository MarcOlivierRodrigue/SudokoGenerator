cmake_minimum_required(VERSION 3.10)
project(SudokuGenerator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS includes/Grid.h
	includes/Printer.h
    includes/Builder.h
    includes/BuilderBitMaps.h
    includes/Logic.h)

set(SOURCES src/Grid.cpp
    src/Printer.cpp
    src/Builder.cpp
    src/BuilderBitMaps.cpp
    src/Logic.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes) 

add_executable(SudokuGenerator main.cpp ${HEADERS} ${SOURCES})