#pragma once

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "Numeric.h"

template <class T>
class Tetrahedron
{
public:
	using Edge = Line<T>;
	using Vector3 = Point<T>;

	Tetrahedron(const Vector3 &_p1, const Vector3 &_p2, const Vector3 &_p3, const Vector3 &_p4) : p1(_p1), p2(_p2), p3(_p3), p4(_p4), e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), e4(_p1, _p4), e5(_p2, _p4), e6(_p3, _p4), isBad(false)
	{
		calculateCircumCircle();
	}

	bool containsVertex(const Vector3 &v) const
	{
		return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v) || almost_equal(p4, v);
	}

	bool circumCircleContains(const Vector3 &v) const
	{
		return center.distance(v) <= radius;
	}

	void calculateCircumCircle()
	{
		//center = NULL;
		radius = (T)0;
	}

	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;
	Vector3 center;
	Edge e1;
	Edge e2;
	Edge e3;
	Edge e4;
	Edge e5;
	Edge e6;
	T radius;
	bool isBad;
};

//template <class T>
//inline std::ostream &operator << (std::ostream &str, const Triangle<T> & t)
//{
//	return str << "Triangle:" << std::endl << "\t" << t.p1 << std::endl << "\t" << t.p2 << std::endl << "\t" << t.p3 << std::endl << "\t" << t.e1 << std::endl << "\t" << t.e2 << std::endl << "\t" << t.e3 << std::endl;
//}
//
//template <class T>
//inline bool operator == (const Triangle<T> &t1, const Triangle<T> &t2)
//{
//	return
//		(t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) &&
//		(t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) &&
//		(t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3);
//}
//
//template <class T>
//inline bool almost_equal(const Triangle<T> &t1, const Triangle<T> &t2)
//{
//	return
//		(almost_equal(t1.p1, t2.p1) || almost_equal(t1.p1, t2.p2) || almost_equal(t1.p1, t2.p3)) &&
//		(almost_equal(t1.p2, t2.p1) || almost_equal(t1.p2, t2.p2) || almost_equal(t1.p2, t2.p3)) &&
//		(almost_equal(t1.p3, t2.p1) || almost_equal(t1.p3, t2.p2) || almost_equal(t1.p3, t2.p3));
//}
