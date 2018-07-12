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

		//const Vector3 center(midX, midY, midZ);
		const T radius = half(deltaMax) * (T)1.1;
		const T edge = radius * sqrtt((T)24);
		const T height = sqrtt((T)2 / (T)3) * edge;
		const T face = edge / sqrtt((T)3);

		// Make super tetra
		const Vector3 p1(midX - face, midY - radius, midZ);
		const Vector3 p2(midX + half(face), midY - radius, midZ - half(edge));
		const Vector3 p3(midX + half(face), midY - radius, midZ + half(edge));
		const Vector3 p4(midX, midY - radius + height, midZ);

		std::cout << "Super tetra: " << std::endl;
		std::cout << p1 << std::endl;
		std::cout << p2 << std::endl;
		std::cout << p3 << std::endl;
		std::cout << p4 << std::endl;

		// Create a list of tetras, and add the super tetra to it
		_tetrahedrons.push_back(Tetra(p1, p2, p3, p4));

		for (auto p = begin(vertices); p != end(vertices); p++)
		{
			std::vector<Edge> polygon;

			for (auto & t : _triangles)
			{
				//std::cout << "Processing " << std::endl << *t << std::endl;

				//if (t.circumCircleContains(*p))
				if (false)
				{
					std::cout << "Pushing bad triangle " << t << std::endl;
					t.isBad = true;
					polygon.push_back(t.e1);
					polygon.push_back(t.e2);
					polygon.push_back(t.e3);
				}
				else
				{
					std::cout << " does not contain " << *p << " in its circumcenter" << std::endl;
				}
			}

			_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [](Tri &t)
			{
				return t.isBad;
			}), end(_triangles));


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

		_tetrahedrons.erase(std::remove_if(begin(_tetrahedrons), end(_tetrahedrons), [p1, p2, p3, p4](Tetra &t)
		{
			return
				t.containsVertex(p1) ||
				t.containsVertex(p2) ||
				t.containsVertex(p3) ||
				t.containsVertex(p4);
		}), end(_tetrahedrons));

		for (const auto t : _tetrahedrons)
		{
			// generate triangles
		}

		for (const auto t : _triangles)
		{
			// generate edges
			_edges.push_back(t.e1);
			_edges.push_back(t.e2);
			_edges.push_back(t.e3);
		}

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
