#pragma once

#include "numeric.h"

#include <iostream>
#include <cmath>

template <typename T>
class Point
{
public:
	//
	// Constructors
	//

	Point() : x(0), y(0) {}

	Point(T _x, T _y) : x(_x), y(_y) {}

	Point(const Point &v) : x(v.x), y(v.y) {}

	//
	// Operations
	//
	T dist2(const Point &v) const
	{
		T dx = x - v.x;
		T dy = y - v.y;
		return dx * dx + dy * dy;
	}

	T dist(const Point &v) const
	{
		return sqrt(dist2(v));
	}

	T norm2() const
	{
		return x * x + y * y;
	}

	T x;
	T y;

};

template <>
float Point<float>::dist(const Point<float> &v) const
{
	return hypotf(x - v.x, y - v.y);
}

template <>
double Point<double>::dist(const Point<double> &v) const
{
	return hypot(x - v.x, y - v.y);
}

template<typename T>
std::ostream &operator << (std::ostream &str, Point<T> const &point)
{
	return str << "Point x: " << point.x << " y: " << point.y;
}

template<typename T>
bool operator == (const Point<T>& v1, const Point<T>& v2)
{
	return (v1.x == v2.x) && (v1.y == v2.y);
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(const Point<T>& v1, const Point<T>& v2, int ulp = 2)
{
	return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}
