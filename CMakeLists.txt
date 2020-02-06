cmake_minimum_required(VERSION 3.15)
project(TGE)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TGE
        tge.hpp tge_unix.hpp tge_win.hpp
        main.cpp GameObject.cpp Grid.cpp)
