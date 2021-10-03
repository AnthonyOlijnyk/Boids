#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

namespace MathAndPhysics
{
	double distance(double x1, double y1, double x2, double y2);
	double findAngleRadians(double opposite, double adjacent);
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
		Vector operator+(const Vector& v) const
		{
			return Vector(this->x + v.x, this->y + v.y);
		}
		Vector operator-(const Vector& v) const
		{
			return Vector(this->x - v.x, this->y - v.y);
		}
		Vector operator*(const double val) const
		{
			return Vector(this->x * val, this->y * val);
		}
	};
	Vector randomVector(double magnitude);
	Vector randomPositionVector(int x, int y);
	Vector normalizeVector(Vector& v);
	Vector setMagnitude(Vector& v, double magnitude);
}
