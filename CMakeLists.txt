# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (delaunay-triangulation)

add_executable(main 
	main.cpp
	delaunay.h
	edge.h
	numeric.h
	triangle.h
	vector2.h
)
