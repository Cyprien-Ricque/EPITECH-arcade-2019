cmake_minimum_required(VERSION 3.15)

project(sfml)

include_directories(include)
include_directories(../../core/include)

add_library(lib_arcade_sfml.so SHARED
        src/sfml.cpp
        include/sfml.hpp)
