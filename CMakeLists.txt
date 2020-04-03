cmake_minimum_required(VERSION 3.15)
project(TGE)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(TGE SHARED
        tge.hpp
        ColoredOutput.cpp Controls.cpp GameObject.cpp Grid.cpp ClearScreen.cpp)

link_directories(${CMAKE_BINARY_DIR})

message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

add_executable(test main.cpp)
target_link_libraries(test TGE)