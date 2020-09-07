#include <iostream>
#include "SparseMatrix.h"
#include "util.h"


int main()
{
	int m = 0, n = 0;

	m = UGetInt("Enter m: ");
	n = UGetInt("Enter n: ");

	SparseMatrix MyMatrix(m, n);

	try
	{
		MyMatrix.SetMatrix();
		MyMatrix.CreateVector();

		std::cout << std::endl;
		MyMatrix.PrintMatrix();
		std::cout << std::endl;
		MyMatrix.PrintVector();
	}
	catch(std::bad_alloc &b_a)
	{
		std::cout << "Bad alloc" << std::endl << b_a.what() << std::endl;
	}
	catch (std::exception &ex)
	{
		std::cout << "Exception" << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Sth was wrong" << std::endl;
	}

	return 0;
}

