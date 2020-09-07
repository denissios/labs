#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int m, int n)
{
	this->m = m;
	this->n = n;
	matrix = new int* [m];
	for (size_t i = 0; i < m; i++)
		matrix[i] = new int[n];

	MyVector = new int[m];
	row_ptr = new int[m];
}

SparseMatrix::~SparseMatrix()
{
	for (size_t i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] val;
	delete[] row_ptr;
	delete[] MyVector;
}

void SparseMatrix::PrintMatrix()
{
	std::cout << "Print matrix" << std::endl;

	if (!m || !n)
	{
		return;
	}

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void SparseMatrix::PrintVector()
{
	std::cout << "Print Vector" << std::endl;

	if (!m || !n)
	{
		return;
	}

	for (size_t i = 0; i < m; i++)
	{
		std::cout << MyVector[i] << std::endl;
	}
}

void SparseMatrix::SetMatrix()
{
	if (!m || !n)
	{
		return;
	}

	for (size_t i = 0; i < m; i++)
	{
		bool flag = false, all_row_null = true;
		std::cout << "Row number " << i << ": ";
		for (size_t j = 0; j < n; j++)
		{
			matrix[i][j] = GetInt("Enter: ");
			if (matrix[i][j])
			{
				all_row_null = false;
				if (!flag)
				{
					row_ptr[i] = size_val;
					flag = true;
				}
				val = val_push_back(val, matrix[i][j]);
			}
			if (j == n - 1 && all_row_null)
				row_ptr[i] = -1;                        // -1 if all row includes 0
		}
	}
}

void SparseMatrix::CreateVector()
{
	if (!m || !n)
	{
		return;
	}

	for (size_t i = 0, j = 0, row_count = 0; i < m; i++)
	{
		int s1 = 0, s2 = 0;
		if (row_count == m - 1)
		{
			while (j != size_val)
			{
				s1 += mod_3(val[j]);
				s2 += mod_5(val[j]);
				j++;
			}
			MyVector[i] = s1 - s2;
			break;
		}

		if (row_ptr[row_count] == -1)
		{
			MyVector[i] = 0;
			row_count++;
			continue;
		}

		while (j != size_val && j != row_ptr[row_count + 1])
		{
			s1 += mod_3(val[j]);
			s2 += mod_5(val[j]);
			j++;
		}
		MyVector[i] = s1 - s2;
		row_count++;
	}
}

int SparseMatrix::mod_3(int element)
{
	return !(element % 3) ? element : 0;
}

int SparseMatrix::mod_5(int element)
{
	return !(element % 5) ? element : 0;
}

int* SparseMatrix::val_push_back(int*& arr_val, const int element)
{
	int* val = new int[size_val + 1];
	for (size_t i = 0; i < size_val; i++)
		val[i] = arr_val[i];

	val[size_val] = element;
	this->size_val++;
	delete[] arr_val;
	return val;
}