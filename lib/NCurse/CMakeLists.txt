cmake_minimum_required(VERSION 3.15)

project(ncurse)

include_directories(include)
include_directories(../../core/include)

add_library(lib_arcade_ncurse.so SHARED
        src/color.cpp
        src/ncurse.cpp
        include/ncurse.hpp)
