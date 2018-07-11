#pragma once

#include "Point.h"

template <class T>
class Line
{
public:
	using Vector3 = Point<T>;

	Line(const Vector3 &p1, const Vector3 &p2) : p1(p1), p2(p2), isBad(false) {};
	Line(const Line &e) : p1(e.p1), p2(e.p2), isBad(false) {};

	Vector3 p1;
	Vector3 p2;

	bool isBad;
};

template <class T>
inline std::ostream &operator << (std::ostream &str, Line<T> const &e)
{
	return str << "Edge " << e.p1 << ", " << e.p2;
}

template <class T>
inline bool operator == (const Line<T> & e1, const Line<T> & e2)
{
	return
		(e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
		(e1.p1 == e2.p2 && e1.p2 == e2.p1);
}

template <class T>
inline bool almost_equal(const Line<T> & e1, const Line<T> & e2)
{
	return
		(almost_equal(e1.p1, e2.p1) && almost_equal(e1.p2, e2.p2)) ||
		(almost_equal(e1.p1, e2.p2) && almost_equal(e1.p2, e2.p1));
}
