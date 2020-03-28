#include <stdio.h>

void minmax(int a, int* res)
{
	int max = -1, max1 = -1, min = 10, min1 = 10;
	while (a > 0)
	{
		if (a % 10 == max)
			max1 *= max;

		if (a % 10 == min)
			min1 *= min;

		if (a % 10 < min)
		{
			min = a % 10;
			min1 = min;
		}

		if (a % 10 > max) \
		{
			max = a % 10;
			max1 = max;
		}

		a /= 10;
	}
	*res = max1 * min1;
}

int getInt(int* a)
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

int main()
{
	int n = 0, i = 0, j = 0, k = 0, result = 0, first = 0, tmp = 0;
	int arr[100], arr1[100];

	printf("Enter the count of numbers: ");
	if (!getInt(&n))
	{
		printf("Error!");
		return 0;
	}

	for (i = 0; i < n; i++)
	{
		if (!getInt(arr + i))
		{
			printf("Error!");
			return 0;
		}
		minmax(arr[i], &result);
		if (i == 0)
			first = result;
		printf("The multiplication of %d number: %d\n", i + 1, result);

		//add new array with deleting elemets from first array
		if (result <= first)
		{
			arr1[j] = arr[i];
			j++;
		}
		//add new array with deleting elemets from first array

	}

	printf("After deleting elements\n");
	for (i = 0; i < j; i++)
		printf("%d \n", arr1[i]);

	//Sort
	for (i = 1; i < j; i++)
		for (k = i; k >= 0 && arr1[k - 1] < arr1[k]; k--)
		{
			tmp = arr1[k - 1];
			arr1[k - 1] = arr1[k];
			arr1[k] = tmp;
		}
	//Sort

	printf("After sorting elements\n");
	for (i = 0; i < j; i++)
		printf("%d \n", arr1[i]);

	return 0;
}