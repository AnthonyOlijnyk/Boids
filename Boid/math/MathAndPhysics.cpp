#include "MathAndPhysics.h"

double MathAndPhysics::distance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

double MathAndPhysics::findAngleRadians(double opposite, double adjacent)
{
	if (adjacent == 0.f)
	{
		if (opposite > 0)
		{
			return M_PI / 2;
		}
		else
		{
			return 3 * M_PI / 2;
		}
	}
	else
	{
		return (double)atan2(opposite, adjacent);
	}
}

MathAndPhysics::Vector MathAndPhysics::randomVector(double magnitude)
{
	int multFactor[] = { 1, -1 };
	double xComponent = (double)(rand() % ((int)magnitude + 1));
	double yComponent = magnitude - xComponent;
	int xComponentFactor = rand() % 2;
	int yComponentFactor = rand() % 2;
	return Vector(xComponent * multFactor[xComponentFactor], yComponent * multFactor[yComponentFactor]);
}

MathAndPhysics::Vector MathAndPhysics::randomPositionVector(int x, int y)
{
	double xPosition = (double)(rand() % x);
	double yPosition = (double)(rand() % y);
	return Vector(xPosition, yPosition);
}

MathAndPhysics::Vector MathAndPhysics::normalizeVector(Vector& v)
{
	double magnitude = v.getMagnitude();
	return Vector(v.x / magnitude, v.y / magnitude);
}

MathAndPhysics::Vector MathAndPhysics::setMagnitude(Vector& v, double magnitude)
{
	Vector normal = MathAndPhysics::normalizeVector(v);
	return normal * magnitude;
}
