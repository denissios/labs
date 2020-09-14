#include "pch.h"
#include "../nefroid.cpp"
#define _USE_MATH_DEFINES
#include <math.h>

TEST(nefroid_constructor, default_constructor) {
	nefroid Nefroid;
	ASSERT_EQ(0, Nefroid.GetRadius());
}

TEST(nefroid_constructor, other_constructor) {
	nefroid Nefroid1(5);
	ASSERT_EQ(5, Nefroid1.GetRadius());

	nefroid Nefroid2(-1);
	ASSERT_EQ(0, Nefroid2.GetRadius());
}

TEST(nefroid_constructor, Exception) {
	ASSERT_NO_THROW(nefroid Nefroid1);
	ASSERT_NO_THROW(nefroid Nefroid2(100));
}

TEST(nefroid_methods, setters) {
	nefroid Nefroid;
	Nefroid.SetRadius(-10);
	ASSERT_EQ(0, Nefroid.GetRadius());
	Nefroid.SetRadius(10);
	ASSERT_EQ(10, Nefroid.GetRadius());
	Nefroid.SetRadius(15);
	ASSERT_EQ(15, Nefroid.GetRadius());
	Nefroid.SetRadius(-5);
	ASSERT_EQ(15, Nefroid.GetRadius());
}

TEST(nefroid_methods, length) {
	nefroid Nefroid(6);
	ASSERT_EQ(144, Nefroid.GetLength());
}

TEST(nefroid_methods, radius_curvature) {
	nefroid Nefroid(3);
	ASSERT_EQ(fabs(9 * sin(M_PI / 3)), Nefroid.GetRadiusCurvature(60));
}

TEST(nefroid_methods, radius_square) {
	nefroid Nefroid(15);
	ASSERT_EQ(2700 * M_PI, Nefroid.GetSquare());
}

TEST(nefroid_methods, get_xy) {
	nefroid Nefroid(20);
	ASSERT_EQ((120 * cos(M_PI / 3) - 80 * pow(cos(M_PI / 3), 3)), Nefroid.Get_X(60));
	ASSERT_EQ((80 * pow(sin(M_PI / 3), 3)), Nefroid.Get_Y(60));
}

TEST(nefroid_methods, equation_null) {
	nefroid Nefroid;
	ASSERT_EQ("(x ^ 2 + y ^ 2) ^ 3 = 0", Nefroid.GetEquation());
}

TEST(nefroid_methods, equation_not_null) {
	nefroid Nefroid(2);
	ASSERT_EQ("(x ^ 2 + y ^ 2 - 16) ^ 3 = 1728 * y ^ 2", Nefroid.GetEquation());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}