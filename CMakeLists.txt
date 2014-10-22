cmake_minimum_required(VERSION 2.8.4)
project(QuadTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB SOURCE_FILES
    "source/Point.hpp"
    "source/Point.cpp"
    "source/Rect.hpp"
    "source/Rect.cpp"

    "source/QuadNode.hpp"
    "source/QuadNode.cpp"
    "source/QuadTree.hpp"
    "source/QuadTree.cpp"
    "source/QuadTreeApp.hpp"
    "source/QuadTreeApp.cpp"

    "source/drawing/drawing_c.h"
    "source/drawing/drawing.c"

    "source/main.cpp"
)

add_executable(QuadTree ${SOURCE_FILES})