#include "pch.h"
#include "MathAndPhysics.h"
#include "math.h"

using namespace MathAndPhysics;
TEST(DistanceTest, HandlesCommonCases) {
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	EXPECT_NEAR(distance(x1, y1, x2, y2), 0.0, 0.5);
	x1 = 2, y1 = -2, x2 = 3, y2 = -2;
	EXPECT_NEAR(distance(x1, y1, x2, y2), 1, 0.5);

}

TEST(AngleTest, HandlesCommonCases) {
	double opposite = 30;
	double adjacent = 0;
	EXPECT_NEAR(findAngleRadians(30, 0), M_PI / 2, 0.5);
	opposite = -90;
	EXPECT_NEAR(findAngleRadians(30, 0), 1.5707963267948966, 0.6);
}

TEST(AddVectors, HandlesCommonCases) {
	Vector v1(3, 4);
	Vector v2(2, 2);
	Vector v3 = addVectors(v1, v2);
	EXPECT_NEAR(v3.x, 5, 0.01);
	EXPECT_NEAR(v3.y, 6, 0.01);

	v1.x = -9;
	v2.y = 0;

	v3 = addVectors(v1, v2);
	EXPECT_NEAR(v3.x, -7, 0.01);
	EXPECT_NEAR(v3.y, 4, 0.01);
}

TEST(SubtractVectors, HandlesCommonCases) {
	Vector v1(3, 4);
	Vector v2(2, 2);
	Vector v3 = subtractVectors(v1, v2);
	EXPECT_NEAR(v3.x, 1, 0.01);
	EXPECT_NEAR(v3.y, 2, 0.01);

	v1.x = -9;
	v2.y = 0;

	v3 = subtractVectors(v1, v2);
	EXPECT_NEAR(v3.x, -11, 0.01);
	EXPECT_NEAR(v3.y, 4, 0.01);
}

TEST(MultiplyScalar, HandlesCommonCases) {
	Vector v1(3, 4);
	double scalar = 2;
	Vector v2 = multiplyScalar(v1, scalar);
	EXPECT_NEAR(v2.x, 6, 0.01);
	EXPECT_NEAR(v2.y, 8, 0.01);
	
	scalar = -3;
	Vector v3 = multiplyScalar(v1, scalar);
	EXPECT_NEAR(v3.x, -9, 0.01);
	EXPECT_NEAR(v3.y, -12, 0.01);
}

TEST(RandomVector, HandlesCommonCases) {
	Vector v = randomVector(10);
	EXPECT_NEAR(v.getMagnitude(), 10, 0.01);
	v = randomVector(0);
	EXPECT_NEAR(v.getMagnitude(), 0, 0.01);
}

TEST(RandomPositionVector, HandlesCommonCases) {
	Vector v = randomPositionVector(2, 2);
	EXPECT_TRUE(v.getMagnitude() <= sqrt(8));
}

TEST(NormalizeVector, HandlesCommonCases) {
	Vector v1(10, 10);
	Vector v2 = normalizeVector(v1);
	EXPECT_NEAR(v2.getMagnitude(), 1, 0.01);
}

TEST(SetMagnitude, HandlesCommonCases) {
	Vector v1(10, 10);
	Vector v2 = setMagnitude(v1, 5);
	EXPECT_NEAR(v2.getMagnitude(), 5, 0.01);
}