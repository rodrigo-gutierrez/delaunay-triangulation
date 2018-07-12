#pragma once

#include "Numeric.h"

#include <iostream>
#include <cmath>

template <typename T>
class Point
{
public:
	//
	// Constructors
	//

	Point() : x(0), y(0), z(0) {}

	Point(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

	Point(const Point &v) : x(v.x), y(v.y), z(v.z) {}

	//
	// Operations
	//
	T distance(const Point &v) const
	{
		T dx = x - v.x;
		T dy = y - v.y;
		T dz = z - v.z;
		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	T magnitude() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	T norm2() const
	{
		return x * x + y * y;
	}

	Point<T> normalize() const
	{
		T mag = this.magnitude();
		return Point<T>(x / mag, y / mag, z / mag);
	}

	T x;
	T y;
	T z;
};

template<typename T>
std::ostream &operator << (std::ostream &str, Point<T> const &point)
{
	return str << "Point x: " << point.x << " y: " << point.y << " z: " << point.z;
}

template<typename T>
bool operator == (const Point<T>& v1, const Point<T>& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

template<typename T>
Point<T> operator - (const Point<T>& v1, const Point<T>& v2)
{
	return Point<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template<typename T>
Point<T> operator - (const Point<T>& v)
{
	return Point<T>(-v.x, -v.y, -v.z);
}

template<typename T>
Point<T> operator + (const Point<T>& v1, const Point<T>& v2)
{
	return Point<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template<typename T>
Point<T> cross(const Point<T>& v1, const Point<T>& v2)
{
	return Point<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template<typename T>
T dot(const Point<T>& v1, const Point<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(const Point<T>& v1, const Point<T>& v2, int ulp = 2)
{
	return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}
