cmake_minimum_required(VERSION 3.15)

project(tests_arcade)

#include_directories("/home/emilien/googletest/googletest/include" "/home/emilien/googletest/")

SET(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(../games/Qix/include)

add_executable(tests_arcade test_bitmap_reader.cpp
        ../games/Qix/src/bitmapReader.cpp
        ../games/Qix/include/bitmapReader.hpp)

target_link_libraries(tests_arcade gtest gtest_main pthread)