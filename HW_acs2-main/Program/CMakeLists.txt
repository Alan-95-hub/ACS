cmake_minimum_required(VERSION 3.19)
project(Alan)

set(CMAKE_CXX_STANDARD 20)

add_executable(Alan Figure.cpp Circle.cpp Rectangle.cpp Triangle.cpp Point.cpp Container.cpp main.cpp)