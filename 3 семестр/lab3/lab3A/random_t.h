#pragma once
#include <iosfwd>

class random_t
{
public:
	random_t();
	random_t(int length);
	random_t(int length, float* arr);
	void SetSampleByLength(int length);
	void SetSampleByArray(int length, float* arr);
	int GetLength();
	void SetNewNumbers();
	random_t& operator++(int a);
	float& operator[](int index);
	float average();
	random_t& operator~();
	void operator()(float a, float b);
	friend std::ostream& operator<<(std::ostream& out, const random_t& sample);

private:
	float arr[100] = { 0 };
	size_t length;
};