#include "pch.h"
#include "../random_t.cpp"
#include <sstream>

TEST(Random_tConstructor, Default) {
	random_t sample;
	ASSERT_EQ(0, sample.GetLength());
}

TEST(Random_tConstructor, other) {
	random_t sample1(5);
	ASSERT_EQ(5, sample1.GetLength());

	float arr[3] = { 0.3, 0.5, 0.2 };
	random_t sample2(3, arr);
	ASSERT_EQ(3, sample2.GetLength());
	ASSERT_TRUE(0 == memcmp(arr, sample2.GetArr(), sizeof(arr)));
}

TEST(Random_tConstructor, Exception) {
	float arr[3] = { 0.3, 0.5, 0.2 };
	ASSERT_NO_THROW(random_t sample);
	ASSERT_NO_THROW(random_t sample2(5));
	ASSERT_NO_THROW(random_t sample3(3, arr));
	ASSERT_ANY_THROW(random_t sample(-1));
	ASSERT_ANY_THROW(random_t sample3(-2, arr));
}

TEST(Random_tMethods, setters) {
	random_t sample1;
	sample1.SetSampleByLength(7);
	ASSERT_EQ(7, sample1.GetLength());

	float arr[4] = { 0.3, 0.5, 0.2, 0.9};
	random_t sample2;
	sample2.SetSampleByArray(4, arr);
	ASSERT_TRUE(0 == memcmp(arr, sample2.GetArr(), sizeof(arr)));
}

TEST(Random_tMethods, UpdateNumbers) {
	float arr[4] = { 0.3, 0.5, 0.2, 0.9 };
	random_t sample(4, arr);
	ASSERT_TRUE(0 == memcmp(arr, sample.GetArr(), sizeof(arr)));
	sample.SetNewNumbers();
	ASSERT_FALSE(0 == memcmp(arr, sample.GetArr(), sizeof(arr)));
}

TEST(Random_tMethods, Print) {
	float arr[1] = { 0.3 };
	random_t sample(4, arr);
	std::stringstream ss;
	ss << sample;
	float a = 0, b = 0.3;
	ss >> a;
	ASSERT_EQ(b, a);
}

TEST(Random_tMethods, NewNumber) {
	float arr[4] = { 0.3, 0.5, 0.2, 0.9 };
	random_t sample(4, arr);
	ASSERT_TRUE(0 == memcmp(arr, sample.GetArr(), sizeof(arr)));
	sample++;
	ASSERT_EQ(5, sample.GetLength());
	ASSERT_FALSE(0 == memcmp(arr, sample.GetArr(), 20));
}

TEST(Random_tMethods, GetByIndex) {
	float arr[4] = { 0.3, 0.5, 0.2, 0.9 };
	random_t sample(4, arr);
	ASSERT_EQ(0.5, sample[1]);
	ASSERT_ANY_THROW(sample[-1]);
	ASSERT_ANY_THROW(sample[4]);
}

TEST(Random_tMethods, Average) {
	float arr[4] = { 0.3, 0.5, 0.2, 0.9 };
	random_t sample(4, arr);
	float a = 0.475;
	ASSERT_EQ(a, sample.average());
}

TEST(Random_tMethods, To10) {
	float arr1[4] = { 0.3, 0.5, 0.2, 0.9 };
	random_t sample(4, arr1);
	~sample;
	float arr2[4] = { 1, 1, 1, 1 };
	ASSERT_TRUE(0 == memcmp(arr2, sample.GetArr(), sizeof(arr2)));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}