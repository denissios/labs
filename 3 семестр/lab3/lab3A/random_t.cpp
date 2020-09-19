#include "random_t.h"
#include <iostream>
#include <ctime>

random_t::random_t()
{
	this->length = 0;
}

random_t::random_t(int length)
{
	this->SetSampleByLength(length);
}

random_t::random_t(int length, float* arr)
{
	this->SetSampleByArray(length, arr);
}

void random_t::SetSampleByLength(int length)
{
	if (length < 0 || length > 100) {
		throw length;
	}
	srand(time(NULL));
	this->length = length;
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = (rand() % 10) / 10.0;
	}
}

void random_t::SetSampleByArray(int length, float* arr)
{
	if (length < 0 || length > 100) {
		throw length;
	}
	this->length = length;
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = arr[i];
	}
}

int random_t::GetLength()
{
	return this->length;
}

void random_t::SetNewNumbers()
{
	srand(time(NULL));
	for (size_t i = 0; i < this->length; i++) {
		this->arr[i] = (rand() % 10) / 10.0;
	}
}

random_t& random_t::operator++(int a)
{
	if (length < 100) {
		this->length++;
		srand(time(NULL));
		this->arr[length - 1] = (rand() % 10) / 10.0;
		return *this;
	}

	return *this;
}

float& random_t::operator[](int index)
{
	if (index < 0 || index > this->length - 1) {
		throw index;
	}
	return this->arr[index];
}

float random_t::average()
{
	float sum = 0;
	for (size_t i = 0; i < this->length; i++) {
		sum += this->arr[i];
	}

	return (sum / this->length);
}

random_t& random_t::operator~()
{
	for (size_t i = 0; i < this->length; i++) {
		this->arr[i] = 1.0;
	}
	return *this;
}

void random_t::operator()(float a, float b)
{
	for (size_t i = 0; i < this->length; i++) {
		if (this->arr[i] > a && this->arr[i] < b) {
			std::cout << this->arr[i] << " ";
		}
	}
}

std::ostream& operator<<(std::ostream& out, const random_t& sample)
{
	for (size_t i = 0; i < sample.length; i++) {
		out << sample.arr[i] << " ";
	}
	return out;
}