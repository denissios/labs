#include "random_t.h"
#include <iostream>
#include <ctime>

random_t::random_t()
{
	this->length = 0;
	this->arr = nullptr;
}

random_t::random_t(const int length)
{
	this->SetSampleByLength(length);
}

random_t::random_t(float*& arr)
{
	this->SetSampleByArray(arr);
}

random_t::random_t(const random_t& other)
{
	this->length = other.length;
	if (!length) {
		this->arr = nullptr;
		return;
	}
	this->arr = new float[other.length];
	for (size_t i = 0; i < other.length; i++) {
		this->arr[i] = other.arr[i];
	}
}

random_t::random_t(random_t&& other) noexcept : random_t()
{
	swap(other);
}

random_t::~random_t()
{
	delete[] arr;
}

void random_t::SetSampleByLength(const int length)
{
	if (length < 0) {
		throw std::out_of_range("Invalid length");
	}

	this->length = length;
	this->arr = new float[length];
	srand(time(NULL));
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = (rand() % 10) / 10.0;
	}
}

void random_t::SetSampleByArray(float*& arr)
{
	if (arr) {
		length = _msize(arr) / sizeof(arr[0]);
	}
	else {
		length = 0;
		this->arr = nullptr;
		return;
	}

	this->arr = new float[length];
	for (size_t i = 0; i < length; i++) {
		this->arr[i] = arr[i];
	}
}

int random_t::GetLength() const noexcept
{
	return this->length;
}

float* random_t::GetArr() const
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
	srand(time(NULL));
	arr_push_back((rand() % 10) / 10.0);
	return *this;
}

random_t& random_t::operator=(const random_t& other)
{
	if (this == &other)
		return *this;
	
	if (arr)
		delete[] arr;

	this->length = other.length;
	if (!length) {
		this->arr = nullptr;
		return *this;
	}
	this->arr = new float[other.length];
	for (size_t i = 0; i < other.length; i++) {
		this->arr[i] = other.arr[i];
	}

	return *this;
}

random_t& random_t::operator=(random_t&& other) noexcept
{
	if (this != &other) {
		swap(other);
	}

	return *this;
}

const float& random_t::operator[](const int index) const
{
	if (index < 0 || index > this->length - 1) {
		throw std::out_of_range("Invalid index");
	}
	return this->arr[index];
}

float random_t::average() const
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
		this->arr[i] = 1.0 - this->arr[i];
	}
	return *this;
}

random_t random_t::operator()(const float a, const float b) const
{
	random_t tmp;
	for (size_t i = 0, j = 0; i < this->length; i++) {
		if (this->arr[i] > a && this->arr[i] < b) {
			tmp.arr_push_back(this->arr[i]);
		}
	}

	return tmp;
}

void random_t::arr_push_back(const float element)
{
	float* new_arr = new float[length + 1];
	std::memcpy(new_arr, arr, length * sizeof(float));
	length++;
	new_arr[length - 1] = element;
	delete[] arr;
	arr = new_arr;
}

void random_t::swap(random_t& other)
{
	std::swap(arr, other.arr);
	std::swap(length, other.length);
}

std::ostream& operator<<(std::ostream& out, const random_t& sample)
{
	for (size_t i = 0; i < sample.length; i++) {
		out << sample.arr[i] << " ";
	}
	return out;
}