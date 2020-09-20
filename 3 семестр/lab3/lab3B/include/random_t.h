#pragma once
#include <iosfwd>

class random_t
{
public:
	random_t();
	random_t(int length);
	random_t(int length, float*& arr);
	random_t(random_t& other);
	~random_t();
	void SetSampleByLength(int length);
	void SetSampleByArray(int length, float*& arr);
	int GetLength();
	float* GetArr();
	void SetNewNumbers();
	random_t& operator++(int a);
	random_t& operator=(const random_t& other);
	float& operator[](int index);
	float average();
	random_t& operator~();
	void operator()(float a, float b);
	friend std::ostream& operator<<(std::ostream& out, const random_t& sample);

private:
	float* arr;
	size_t length;
	float* arr_push_back(float*& arr);
};