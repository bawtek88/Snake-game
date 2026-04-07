cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(snake src/main.cpp src/Snake.cpp src/Game.cpp src/Config.cpp src/Player.cpp)

target_include_directories(snake PRIVATE include)

find_package(SFML 3 REQUIRED COMPONENTS System Window Graphics)

target_link_libraries(snake PRIVATE SFML::System SFML::Window SFML::Graphics)