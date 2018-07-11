#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <array>

#include "Point.h"
#include "Triangle.h"
#include "Delaunay.h"

float RandomFloat(float a, float b)
{
	const float random = ((float)rand()) / (float)RAND_MAX;
	const float diff = b - a;
	const float r = random * diff;
	return a + r;
}

int main(int argc, char * argv[])
{
	int numberPoints = 40;
	if (argc == 1)
	{
		numberPoints = (int)roundf(RandomFloat(4, numberPoints));
	}
	else if (argc > 1)
	{
		numberPoints = atoi(argv[1]);
	}

	numberPoints = 4;

	std::cout << "Generating " << numberPoints << " NOT random points" << std::endl;

	std::vector<Point<float> > points;
	//for (int i = 0; i < numberPoints; ++i)
	//{
	//	points.push_back(Point<float>(RandomFloat(0, 800), RandomFloat(0, 600)));
	//}
	points.push_back(Point<float>(1.0f, 1.0f, 0.0f));
	points.push_back(Point<float>(-1.0f, 1.0f, 0.0f));
	points.push_back(Point<float>(-1.0f, -1.0f, 0.0f));
	points.push_back(Point<float>(1.0f, -1.0f, 0.0f));
	points.push_back(Point<float>(0.0f, 0.0f, 1.0f));

	Delaunay<float> triangulation;
	const std::vector<Triangle<float> > triangles = triangulation.triangulate(points);
	std::cout << triangles.size() << " triangles generated\n";
	const std::vector<Line<float> > edges = triangulation.getEdges();

	std::cout << std::endl << " ========= " << std::endl;

	std::cout << "\nPoints : " << points.size() << std::endl;
	for (int i = 0; i < points.size(); i++)
		std::cout << i << " " << points[i] << std::endl;

	std::cout << "\nTriangles : " << triangles.size() << std::endl;
	for (int i = 0; i < triangles.size(); i++)
		std::cout << i << " " << triangles[i] << std::endl;

	std::cout << "\nEdges : " << edges.size() << std::endl;
	for (int i = 0; i < edges.size(); i++)
		std::cout << i << " " << edges[i] << std::endl;

	return 0;

	std::ofstream objFile;
	objFile.open("test.obj");
	objFile << "g test" << std::endl << std::endl;

	objFile.close();

	return 0;
}
