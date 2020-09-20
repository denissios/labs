#include "random_t.h"
#include <iostream>
#include <ctime>

random_t::random_t()
{
	this->length = 0;
	this->arr = nullptr;
}

random_t::random_t(int length)
{
	this->SetSampleByLength(length);
}

random_t::random_t(int length, float*& arr)
{
	this->SetSampleByArray(length, arr);
}

random_t::random_t(random_t& other)
{
	this->length = other.length;
	this->arr = new float[other.length];
	for (size_t i = 0; i < other.length; i++) {
		this->arr[i] = other.arr[i];
	}
}

random_t::~random_t()
{
	delete[] arr;
}

void random_t::SetSampleByLength(int length)
{
	if (length < 0) {
		throw length;
	}

	this->length = length;
	this->arr = new float[length];
	srand(time(NULL));
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = (rand() % 10) / 10.0;
	}
}

void random_t::SetSampleByArray(int length, float*& arr)
{
	if (length < 0) {
		throw length;
	}

	this->length = length;
	this->arr = new float[length];
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = arr[i];
	}
}

int random_t::GetLength()
{
	return this->length;
}

float* random_t::GetArr()
{
	return this->arr;
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
	this->arr = arr_push_back(this->arr);

	srand(time(NULL));
	this->arr[length - 1] = (rand() % 10) / 10.0;
	return *this;
}

random_t& random_t::operator=(const random_t& other)
{
	if (this == &other)
		return *this;

	this->length = other.length;
	this->arr = new float[other.length];
	for (size_t i = 0; i < other.length; i++) {
		this->arr[i] = other.arr[i];
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

float* random_t::arr_push_back(float*& arr)
{
	this->length++;
	float* new_arr = new float[this->length];
	for (size_t i = 0; i < this->length - 1; i++){
		new_arr[i] = arr[i];
	}

	delete[] arr;
	return new_arr;
}

std::ostream& operator<<(std::ostream& out, const random_t& sample)
{
	for (size_t i = 0; i < sample.length; i++) {
		out << sample.arr[i] << " ";
	}
	return out;
}