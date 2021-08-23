#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

class MathAndPhysics
{
public:
	static double distance(double x1, double y1, double x2, double y2);
	static double findAngleRadians(double opposite, double adjacent);
	struct Vector
	{
		double x;
		double y;
		double angle;
		Vector(double x, double y) : x(x), y(y)
		{
			angle = findAngleRadians(y, x);
		}
		Vector()
		{
			x = 0, y = 0, angle = 0;
		}
		double getMagnitude()
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}
	};
	static Vector addVectors(Vector& v1, Vector& v2);
	static Vector addVectors(Vector& v1, Vector& v2, Vector& v3);
	static Vector subtractVectors(Vector& v1, Vector& v2);
	static Vector multiplyScalar(Vector& v, double scalar);
	static Vector randomVector(double magnitude);
	static Vector randomPositionVector(int x, int y);
	static Vector normalizeVector(Vector& v);
	static Vector setMagnitude(Vector& v, double magnitude);
};
