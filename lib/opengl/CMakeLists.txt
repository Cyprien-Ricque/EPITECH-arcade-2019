cmake_minimum_required(VERSION 3.15)

project(opengl)

include_directories(include)
include_directories(../../core/include)

add_library(lib_arcade_opengl.so SHARED
            src/opengl.cpp
            include/opengl.hpp)
