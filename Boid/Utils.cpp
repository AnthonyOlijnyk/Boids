#include "Utils.h"
#define _USE_MATH_DEFINES
#include <cmath>

float Utils::distance(float x1, float y1, float x2, float y2)
{
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

double Utils::findAngleRadians(float opposite, float adjacent)
{
	if (adjacent == 0.f)
	{
		return M_PI / 2;
	}
	else
	{
		return (double) atan2(opposite, adjacent);
	}
}