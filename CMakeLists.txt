# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (delaunay-triangulation)

add_executable(main 
	Main.cpp
	Delaunay.h
	Line.h
	Numeric.h
	Triangle.h
	Tetrahedron.h
	Point.h
)
