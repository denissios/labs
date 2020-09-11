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
	int m = 0, n = 0, size_val = 0, size_ptr_col = 0;
                                         // to optimize work on a sparse matrix
	int* val = nullptr;                  // made an array "val", which stores all non-zero digits of the matrix.
	int* row_ptr = nullptr;              // Also made an array "row_ptr", which stores the indices of the elements from the "val" array,
	int* ptr_col = nullptr;              // with which each line of the matrix begins. Array "ptr_col" includes indices of the elements on rows.
	int* MyVector = nullptr;             // This way we don't waste time on zero matrix elements, but we work only with non-zero ones.
	int mod_3(int element);
	int mod_5(int element);
	int* val_push_back(int*& arr_val, const int element);
	int* ptr_col_push_back(int*& arr_val, const int element);
};