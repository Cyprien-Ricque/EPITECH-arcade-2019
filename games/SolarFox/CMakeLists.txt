cmake_minimum_required(VERSION 3.15)

project(SolarFox)

include_directories(include/)
include_directories(../../core/include)

add_library(lib_arcade_solar_fox.so SHARED
        src/solarFox.cpp
        src/GameEngine.cpp
        src/bitmapReader.cpp
        src/Clock.cpp
        include/Clock.hpp
        include/solarFox.hpp
        include/GameEngine.hpp
        include/bitmapReader.hpp src/Starship.cpp include/Starship.hpp src/Bullet.cpp include/Bullet.hpp include/Fire.hpp src/Fire.cpp include/Objective.hpp src/Objective.cpp
        src/arcadeError.cpp
        include/arcadeError.hpp)