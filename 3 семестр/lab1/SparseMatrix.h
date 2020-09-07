#pragma once
#include <iostream>
#include "util.h"

class SparseMatrix
{
public:
	SparseMatrix(int m, int n);
	~SparseMatrix();
	void PrintMatrix();
	void PrintVector();
	void SetMatrix();
	void CreateVector();

private:
	int m = 0, n = 0, size_val = 0;
	int** matrix = nullptr;
	int* val = nullptr;
	int* row_ptr = nullptr;
	int* MyVector = nullptr;

	int mod_3(int element);
	int mod_5(int element);
	bool NullMatrix(int m, int n);
	int* val_push_back(int*& arr_val, const int element);
};