#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

void print_vector(const int* vector, const size_t size);
void print_matrix(const int** matrix, const size_t size, const size_t* sizes);
int find_max_occurence(const int* vector, const size_t size);
int UgetInt(const int* a);
int getInt(const int* a);

int main(void)
{
	printf("Enter m\n> ");
	size_t m = 0;
	if (!UgetInt(&m))
	{
		printf("Error!");
		return 0;
	}

	size_t* sizes = (size_t*)malloc(m * sizeof(size_t));
	int** matrix = (int**)malloc(m * sizeof(int*));
	int* ptr_sizes = sizes;
	int** ptr_row = matrix;	
	for (size_t i = 0; i < m; i++, ptr_sizes++, ptr_row++)
	{
		printf("Enter n_%zu\n> ", i);
		if (!UgetInt(ptr_sizes))
		{
			printf("Error!");
			return 0;
		}
		*ptr_row = (int*)malloc(*ptr_sizes * sizeof(int));

		int* ptr_column = *ptr_row;
		for (size_t j = 0; j < sizes[i]; j++, ptr_column++)
			if (!getInt(ptr_column))
			{
				printf("Error!");
				return 0;
			}
	}
	ptr_sizes = sizes;
	ptr_row = matrix;
	int* vector = (int*)malloc(m * sizeof(int));
	int* ptr_vector = vector;

	for (size_t i = 0; i < m; i++, ptr_vector++, ptr_sizes++, ptr_row++)
		*ptr_vector = find_max_occurence(*ptr_row, *ptr_sizes);
	ptr_sizes = sizes;
	ptr_row = matrix;
	ptr_vector = vector;

	printf("Matrix\n");
	print_matrix(matrix, m, sizes);
	
	printf("Vector\n");
	print_vector(vector, m);

	size_t max_count = 0;
	for (size_t i = 0; i < m; i++)
		for (size_t j = 0; j < sizes[i]; j++)
		{
			size_t count = 0;
			for (size_t k = 0; k < m; k++)
				for (size_t z = 0; z < sizes[k]; z++)
					if (matrix[i][j] == matrix[k][z])
						count++;
			max_count = MAX(max_count, count);
		}

	printf("Number of the same: %d", max_count);

	free(vector);
	free(sizes);
	for (size_t i = 0; i < m; i++, ptr_row++)
		free(*ptr_row);
	free(matrix);

	return 0;
}

void print_vector(const int* vector, const size_t size)
{
	int* ptr_vector = vector;
	for (size_t i = 0; i < size; i++, ptr_vector++)
		printf("%d ", *ptr_vector);

	printf("\n");
}

void print_matrix(const int** matrix, const size_t size, const size_t* sizes)
{
	int* ptr_sizes = sizes;
	int** ptr_row = matrix;
	for (size_t i = 0; i < size; i++, ptr_sizes++, ptr_row++)
		print_vector(*ptr_row, *ptr_sizes);
}

int find_max_occurence(const int* vector, const size_t size)
{
	int* ptr_vector_i = vector;
	size_t max_cnt = 0;
	for (size_t i = 0; i < size; i++, ptr_vector_i++)
	{
		size_t cnt = 0;
		int* ptr_vector_j = vector;
		for (size_t j = 0; j < size; j++, ptr_vector_j++)
			if (*ptr_vector_i == *ptr_vector_j)
				cnt++;

		max_cnt = MAX(max_cnt, cnt);
	}

	return max_cnt;
}

int UgetInt(const int* a)
{
	int n;
	do {
		n = scanf_s("%d", a);
		if (n < 0)
		{
			printf("Error!");
			return 0;
		}
		if (!n || *a <= 0)
		{
			printf("Error! Enter Integer type > 0.\n");
			scanf_s("%*[^\n]");
			n = 0;
		}
	} while (!n);
	return n < 0 ? 0 : 1;
}

int getInt(const int* a)
{
	int n;
	do {
		n = scanf_s("%d", a);
		if (n < 0)
		{
			printf("Error!");
			return 0;
		}
		if (!n)
		{
			printf("Error! Enter Integer type > 0.\n");
			scanf_s("%*[^\n]");
			n = 0;
		}
	} while (!n);
	return n < 0 ? 0 : 1;
}