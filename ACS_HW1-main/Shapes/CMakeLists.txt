cmake_minimum_required (VERSION 3.8)
project(Shapes C)

project(Homework LANGUAGES CXX)

set(CMAKE_C_STANDARD 99)
set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

set(BINARY_DIR "${CMAKE_BINARY_DIR}")

set (SOURCE_FILES "circle.c" 
				  "container.c" 
				  "main.c" 
				  "rectangle.c" 
				  "shape.c" 
				  "triangle.c" 
				  "circle.c" 
				  "container.c" 
				  "main.c" 
				  "rectangle.c" 
				  "shape.c" 
				  "triangle.c"
				  "circle.h" 
				  "container.h" 
				  "rectangle.h" 
				  "shape.h" 
				  "triangle.h" 
				  "circle.h" 
				  "container.h" 
				  "rectangle.h" 
				  "shape.h" 
				  "triangle.h")

add_executable(Shapes ${SOURCE_FILES} "pch.h" "pch.c")