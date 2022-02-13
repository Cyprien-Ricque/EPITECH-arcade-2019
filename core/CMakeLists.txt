cmake_minimum_required(VERSION 3.15)

project(arcade)

include_directories(include/)

add_executable(arcade
        src/main.cpp
        include/Arcade.hpp
        include/DLLoader.hpp
        include/IGraphicalModule.hpp
        include/IGameModule.hpp
        src/Menu.cpp
        include/Menu.hpp
        src/Arcade.cpp
        src/GameEngine.cpp
        include/GameEngine.hpp
        include/color.hpp
        include/text.hpp
        include/bitmapReader.hpp
        src/bitmapReader.cpp
        include/Clock.hpp
        src/Clock.cpp include/arcadeError.hpp src/arcadeError.cpp)

target_link_libraries(arcade dl)