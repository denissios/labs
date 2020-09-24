#pragma once
#include <iosfwd>

class random_t
{
public:
	random_t();
	random_t(const int length);
	random_t(float*& arr);
	random_t(const random_t& other);
	random_t(random_t&& other) noexcept;
	~random_t();
	void SetSampleByLength(const int length);
	void SetSampleByArray(float*& arr);
	const int GetLength();
	const float* GetArr();
	void SetNewNumbers();
	random_t& operator++(int a);
	random_t& operator=(const random_t& other);
	random_t& operator=(random_t&& other) noexcept;
	const float& operator[](const int index);
	const float average();
	random_t& operator~();
	const random_t operator()(const float a, const float b);
	friend std::ostream& operator<<(std::ostream& out, const random_t& sample);

private:
	float* arr;
	size_t length;
	void arr_push_back(const float element);
	void swap(random_t& other);
};