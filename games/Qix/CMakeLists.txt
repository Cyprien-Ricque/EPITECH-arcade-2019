cmake_minimum_required(VERSION 3.15)

project(Qix)

include_directories(include/)
include_directories(src/)

add_library(lib_arcade_qix.so SHARED
        src/qix.cpp
        src/GameEngine.cpp
        src/bitmapReader.cpp
        include/GameEngine.hpp
        include/qix.hpp
        include/bitmapReader.hpp src/GameObject.cpp include/GameObject.hpp include/mapData.hpp src/QixMonster.cpp include/QixMonster.hpp src/Player.cpp include/Player.hpp src/Sparks.cpp include/Sparks.hpp src/Fire.cpp include/Fire.hpp src/Map.cpp include/Map.hpp)