#pragma once

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Tetrahedron.h"

#include <vector>
#include <algorithm>

template <class T>
class Delaunay
{
public:
	using Tetra = Tetrahedron<T>; 
	using Tri = Triangle<T>;
	using Edge = Line<T>;
	using Vector3 = Point<T>;

	const std::vector<Tri>& triangulate(std::vector<Vector3> &vertices)
	{
		// Store the vertices locally
		_vertices = vertices;

		// Determinate the super tetra
		T minX = vertices[0].x;
		T minY = vertices[0].y;
		T minZ = vertices[0].z;
		T maxX = minX;
		T maxY = minY;
		T maxZ = minZ;

		for (std::size_t i = 0; i < vertices.size(); ++i)
		{
			if (vertices[i].x < minX) minX = vertices[i].x;
			if (vertices[i].y < minY) minY = vertices[i].y;
			if (vertices[i].z < minZ) minZ = vertices[i].z;
			if (vertices[i].x > maxX) maxX = vertices[i].x;
			if (vertices[i].y > maxY) maxY = vertices[i].y;
			if (vertices[i].z > maxZ) maxZ = vertices[i].z;
		}

		const T dx = maxX - minX;
		const T dy = maxY - minY;
		const T dz = maxZ - minZ;
		const T deltaMax = std::max(dx, std::max(dy, dz));
		const T midX = half(minX + maxX);
		const T midY = half(minY + maxY);
		const T midZ = half(minZ + maxZ);

		// Make super tetra
		const Vector3 p2(minX - 20, minY - 20, maxZ + 20);
		const Vector3 p3(minX - 20, maxY + 20, minZ - 20);
		const Vector3 p4(minX - 20, maxY + 20, maxZ + 20);
		const Vector3 p1(minX - 20, minY - 20, minZ - 20);
		const Vector3 p5(maxX + 20, minY - 20, minZ - 20);
		const Vector3 p6(maxX + 20, minY - 20, maxZ + 20);
		const Vector3 p7(maxX + 20, maxY + 20, minZ - 20);
		const Vector3 p8(maxX + 20, maxY + 20, maxZ + 20);

		std::cout << "Super cube: " << std::endl;
		std::cout << p1 << std::endl;
		std::cout << p2 << std::endl;
		std::cout << p3 << std::endl;
		std::cout << p4 << std::endl;
		std::cout << p5 << std::endl;
		std::cout << p6 << std::endl;
		std::cout << p7 << std::endl;
		std::cout << p8 << std::endl;

		// Create a list of triangles, and add the super cube triangles to it
		_triangles.push_back(Tri(p1, p5, p7));
		_triangles.push_back(Tri(p1, p7, p3));
		_triangles.push_back(Tri(p1, p3, p4));
		_triangles.push_back(Tri(p1, p4, p2));
		_triangles.push_back(Tri(p3, p7, p8));
		_triangles.push_back(Tri(p3, p8, p4));
		_triangles.push_back(Tri(p5, p8, p7));
		_triangles.push_back(Tri(p5, p6, p8));
		_triangles.push_back(Tri(p1, p6, p5));
		_triangles.push_back(Tri(p1, p2, p6));
		_triangles.push_back(Tri(p2, p8, p6));
		_triangles.push_back(Tri(p2, p4, p8));

		for (auto p = begin(vertices); p != end(vertices); p++)
		{
			//std::cout << "Traitement du point " << *p << std::endl;
			std::cout << "0 _triangles contains " << _triangles.size() << " elements" << std::endl;

			std::vector<Edge> polygon;

			for (auto & t : _triangles)
			{
				//std::cout << "Processing " << std::endl << *t << std::endl;

				if (t.circumCircleContains(*p))
				{
					std::cout << "Pushing bad triangle " << t << std::endl;
					t.isBad = true;
					polygon.push_back(t.e1);
					polygon.push_back(t.e2);
					polygon.push_back(t.e3);
				}
				else
				{
					std::cout << " does not contains " << *p << " in his circum center" << std::endl;
				}
			}

			std::cout << "1 _triangles contains " << _triangles.size() << " elements" << std::endl;

			_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [](Tri &t)
			{
				return t.isBad;
			}), end(_triangles));

			std::cout << "2 _triangles contains " << _triangles.size() << " elements" << std::endl;

			for (auto e1 = begin(polygon); e1 != end(polygon); ++e1)
			{
				for (auto e2 = e1 + 1; e2 != end(polygon); ++e2)
				{
					if (almost_equal(*e1, *e2))
					{
						e1->isBad = true;
						e2->isBad = true;
					}
				}
			}

			std::cout << "polygon contains " << polygon.size() << " elements" << std::endl;

			polygon.erase(std::remove_if(begin(polygon), end(polygon), [](Edge &e)
			{
				return e.isBad;
			}), end(polygon));

			std::cout << "polygon contains " << polygon.size() << " elements" << std::endl;

			for (const auto e : polygon)
				_triangles.push_back(Tri(e.p1, e.p2, *p));

		}

		std::cout << "3 _triangles contains " << _triangles.size() << " elements" << std::endl;

		_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3, p4, p5, p6, p7, p8](Tri &t)
		{
			return 
				t.containsVertex(p1) || 
				t.containsVertex(p2) || 
				t.containsVertex(p3) ||
				t.containsVertex(p4) || 
				t.containsVertex(p5) || 
				t.containsVertex(p6) || 
				t.containsVertex(p7) || 
				t.containsVertex(p8);
		}), end(_triangles));

		for (const auto t : _triangles)
		{
			_edges.push_back(t.e1);
			_edges.push_back(t.e2);
			_edges.push_back(t.e3);
		}

		std::cout << "4 _triangles contains " << _triangles.size() << " elements" << std::endl;

		return _triangles;
	}

	const std::vector<Tetra>& getTetrahedrons() const
	{
		return _tetrahedrons;
	};

	const std::vector<Tri>& getTriangles() const
	{
		return _triangles;
	};

	const std::vector<Edge>& getEdges() const
	{
		return _edges;
	};

	const std::vector<Vector3>& getVertices() const
	{
		return _vertices;
	};

private:
	std::vector<Tetra> _tetrahedrons;
	std::vector<Tri> _triangles;
	std::vector<Edge> _edges;
	std::vector<Vector3> _vertices;
};
