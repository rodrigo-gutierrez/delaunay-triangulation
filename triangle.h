#pragma once

#include "Point.h"
#include "Line.h"
#include "Numeric.h"

template <class T>
class Triangle
{
public:
	using EdgeType = Line<T>;
	using Vector3 = Point<T>;

	Triangle(const Vector3 &_p1, const Vector3 &_p2, const Vector3 &_p3) : p1(_p1), p2(_p2), p3(_p3), e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), isBad(false)
	{
		calculateNormal();
	}

	bool containsVertex(const Vector3 &v) const
	{
		// return p1 == v || p2 == v || p3 == v;
		return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v);
	}

	//bool circumCircleContains(const Vector3 &v) const
	//{
	//	Vector3 a = p2 - p1;
	//	Vector3 b = p3 - p1;

	//	Vector3 planeNormal = cross(b, a);

	//	if (!almost_equal(dot(planeNormal, a), (T)0))
	//		std::cerr << "ERROR: a is not orthogonal to planeNormal: " << dot(planeNormal, a) << std::endl;
	//	if (!almost_equal(dot(planeNormal, b), (T)0))
	//		std::cerr << "ERROR: b is not orthogonal to planeNormal: " << dot(planeNormal, b) << std::endl;

	//	Vector3 origin = p1;
	//	Vector3 yAxis = normalize(a);

	//	//std::cout << "yAxis: " << yAxis << std::endl;

	//	Vector3 xAxis = -normalize(cross(planeNormal, a));

	//	//std::cout << "xAxis: " << xAxis << std::endl;

	//	T xCheck = dot(planeNormal, xAxis);
	//	T yCheck = dot(planeNormal, yAxis);
	//	T aCheck = dot(xAxis, yAxis);

	//	if (!almost_equal(xCheck, (T)0))
	//		std::cerr << "ERROR: xAxis is not orthogonal to planeNormal: " << xCheck << std::endl;
	//	if (!almost_equal(yCheck, (T)0))
	//		std::cerr << "ERROR: yAxis is not orthogonal to planeNormal: " << yCheck << std::endl;
	//	if (!almost_equal(aCheck, (T)0))
	//		std::cerr << "ERROR: xAxis is not orthogonal to yAxis: " << aCheck << std::endl;

	//	Vector3 p1_2d = Vector3(dot(xAxis, p1 - origin), dot(yAxis, p1 - origin), 0.0f);
	//	Vector3 p2_2d = Vector3(dot(xAxis, p2 - origin), dot(yAxis, p2 - origin), 0.0f);
	//	Vector3 p3_2d = Vector3(dot(xAxis, p3 - origin), dot(yAxis, p3 - origin), 0.0f);

	//	const T ab = p1_2d.norm2();
	//	const T cd = p2_2d.norm2();
	//	const T ef = p3_2d.norm2();

	//	const T circum_x = (ab * (p3_2d.y - p2_2d.y) + cd * (p1_2d.y - p3_2d.y) + ef * (p2_2d.y - p1_2d.y)) / (p1_2d.x * (p3_2d.y - p2_2d.y) + p2_2d.x * (p1_2d.y - p3_2d.y) + p3_2d.x * (p2_2d.y - p1_2d.y));
	//	const T circum_y = (ab * (p3_2d.x - p2_2d.x) + cd * (p1_2d.x - p3_2d.x) + ef * (p2_2d.x - p1_2d.x)) / (p1_2d.y * (p3_2d.x - p2_2d.x) + p2_2d.y * (p1_2d.x - p3_2d.x) + p3_2d.y * (p2_2d.x - p1_2d.x));

	//	const Vector3 circum(half(circum_x), half(circum_y), 0.0f);
	//	const T radius = p1_2d.distance(circum);

	//	//std::cout << "radius: " << radius << std::endl;

	//	const T dist = v.distance(circum);

	//	//std::cout << "dist: " << dist << std::endl;

	//	bool test = dist <= radius;

	//	std::cout << "test: " << test << std::endl;

	//	return test;
	//}

	void calculateNormal()
	{
		normal = cross(p3 - p1, p2 - p1).normalize;
	}

	void flip()
	{
		Vector3 temp = p3;
		p3 = p2;
		p2 = temp;
		e1 = EdgeType(p1, p2);
		e2 = EdgeType(p2, p3);
		e3 = EdgeType(p3, p1);
		calculateNormal();
	}

	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 normal;
	EdgeType e1;
	EdgeType e2;
	EdgeType e3;
	bool isBad;
};

template <class T>
inline std::ostream &operator << (std::ostream &str, const Triangle<T> & t)
{
	return str << "Triangle:" << std::endl << "\t" << t.p1 << std::endl << "\t" << t.p2 << std::endl << "\t" << t.p3 << std::endl << "\t" << t.e1 << std::endl << "\t" << t.e2 << std::endl << "\t" << t.e3 << std::endl;
}

template <class T>
inline bool operator == (const Triangle<T> &t1, const Triangle<T> &t2)
{
	return
		(t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) &&
		(t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) &&
		(t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3);
}

template <class T>
inline bool almost_equal(const Triangle<T> &t1, const Triangle<T> &t2)
{
	return
		(almost_equal(t1.p1, t2.p1) || almost_equal(t1.p1, t2.p2) || almost_equal(t1.p1, t2.p3)) &&
		(almost_equal(t1.p2, t2.p1) || almost_equal(t1.p2, t2.p2) || almost_equal(t1.p2, t2.p3)) &&
		(almost_equal(t1.p3, t2.p1) || almost_equal(t1.p3, t2.p2) || almost_equal(t1.p3, t2.p3));
}
