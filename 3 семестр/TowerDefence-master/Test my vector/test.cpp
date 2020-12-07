#include "pch.h"
#include <vector>
#include "../src/MyVector.hpp"

TEST(MyVectorConstructor, Default) {
	MyVector<int> v;
	ASSERT_EQ(0, v.size());
	ASSERT_EQ(1, v.capacity());
}

TEST(MyVectorConstructor, Length) {
	MyVector<int> v(5);
	ASSERT_EQ(5, v.size());
	ASSERT_EQ(10, v.capacity());
	ASSERT_ANY_THROW(MyVector<int> v(-1));
}

TEST(MyVectorConstructor, initializer_list) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(4, v.size());
	ASSERT_EQ(1, v[0]);
	ASSERT_EQ(2, v[1]);
	ASSERT_EQ(3, v[2]);
	ASSERT_EQ(4, v[3]);
}

TEST(Operators, equal_op) {
	MyVector<int> v1{ 1, 2, 3, 4 };
	MyVector<int> v2{ 1, 2, 3, 4 };
	ASSERT_EQ(1, v1 == v2);
}

TEST(Operators, compare_op) {
	MyVector<int> v1{ 1, 2, 3, 4 };
	MyVector<int> v2{ 1, 3, 3, 4 };
	ASSERT_EQ(1, v1 < v2);
}

TEST(Functions, at) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(4, v.at(3));
	ASSERT_EQ(2, v.at(1));
	ASSERT_ANY_THROW(v.at(6));
}

TEST(Functions, front) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(1, v.front());
}

TEST(Functions, back) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(4, v.back());
}

TEST(Functions, push_back) {
	MyVector<int> v{ 1, 2, 3, 4 };
	v.push_back(10);
	ASSERT_EQ(10, v.at(4));
	ASSERT_EQ(5, v.size());
}

TEST(Functions, pop_back) {
	MyVector<int> v{ 1, 2, 3, 4 };
	v.pop_back();
	ASSERT_ANY_THROW(v.at(4));
	ASSERT_EQ(3, v.size());
}

TEST(Functions, clear) {
	MyVector<int> v{ 1, 2, 3, 4 };
	v.clear();
	ASSERT_EQ(1, v.capacity());
	ASSERT_EQ(0, v.size());
}

TEST(Functions, emplace) {
	MyVector<int> v1{ 1, 2, 3, 4 };
	v1.emplace(v1.begin() + 1, 1);
	v1.emplace(v1.begin() + 1, 1);
	v1.emplace(v1.begin() + 1, 1);
	MyVector<int> v2{ 1, 1, 1, 1, 2, 3, 4 };
	ASSERT_EQ(7, v1.size());
	ASSERT_EQ(1, v1 == v2);
}

TEST(Functions, emplace_back) {
	MyVector<int> v1{ 1, 2, 3, 4 };
	v1.emplace_back(1);
	v1.emplace_back(1);
	v1.emplace_back(1);
	MyVector<int> v2{ 1, 2, 3, 4, 1, 1, 1 };
	ASSERT_EQ(7, v1.size());
	ASSERT_EQ(1, v1 == v2);
}

TEST(Functions, begin) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(&v[0], v.begin());
}

TEST(Functions, end) {
	MyVector<int> v{ 1, 2, 3, 4 };
	ASSERT_EQ(&v[3] + 1, v.end());
}


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}