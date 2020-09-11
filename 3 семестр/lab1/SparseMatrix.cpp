#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(int m, int n)
{
	this->m = m;
	this->n = n;

	MyVector = new int[m];
	row_ptr = new int[m];
}

SparseMatrix::~SparseMatrix()
{
	delete[] val;
	delete[] row_ptr;
	delete[] ptr_col;
	delete[] MyVector;
}

void SparseMatrix::PrintMatrix()
{
	std::cout << "Print matrix" << std::endl;

	if (!m || !n)
	{
		return;
	}

	for (size_t i = 0, j = 0, row_count = 0; i < m; i++)
	{
		size_t k = 0;

		if (row_ptr[row_count] == -1)
		{
			for (size_t z = 0; z < n; z++)
			{
				std::cout << "0 ";
			}

			std::cout << std::endl;
			row_count++;
			continue;
		}

		if (row_count == m - 1)
		{
			while (k != ptr_col[j])
			{
				std::cout << "0 ";
				k++;
			}

			std::cout << val[j] << " ";
			k++;

			if (j + 1 == row_ptr[row_count + 1])
			{
				while (k < n)
				{
					std::cout << "0 ";
					k++;
				}
				break;
			}
			j++;
		}

		while (j != size_val && j != row_ptr[row_count + 1])
		{
			while (k != ptr_col[j])
			{
				std::cout << "0 ";
				k++;
			}

			std::cout << val[j] << " ";
			k++;

			if (j + 1 == row_ptr[row_count + 1] || j + 1 == size_val)
				while (k < n)
				{
					std::cout << "0 ";
					k++;
				}
			j++;
		}

		std::cout << std::endl;
		row_count++;
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
			int a;
			a = GetInt("Enter: ");
			if (a)
			{
				all_row_null = false;
				if (!flag)
				{
					row_ptr[i] = size_val;
					flag = true;
				}
				val = val_push_back(val, a);
				ptr_col = ptr_col_push_back(ptr_col, j);
			}
			if (j == n - 1 && all_row_null)
				row_ptr[i] = -1;                        // -1 if this all row includes 0
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

		if (row_ptr[row_count] == -1)
		{
			MyVector[i] = 0;
			row_count++;
			continue;
		}

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

int* SparseMatrix::ptr_col_push_back(int*& arr_val, const int element)
{
	int* ptr_col = new int[size_ptr_col + 1];
	for (size_t i = 0; i < size_ptr_col; i++)
		ptr_col[i] = arr_val[i];

	ptr_col[size_ptr_col] = element;
	this->size_ptr_col++;
	delete[] arr_val;
	return ptr_col;
}