#include <iostream>
#include "nefroid.h"
#include "util.h"
#include "menu.h"

int main()
{
	try {
		nefroid Nefroid;
		dialog(Nefroid);
	}
	catch (std::bad_alloc& b_a)
	{
		std::cout << "Bad alloc" << std::endl << b_a.what() << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << "Exception" << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Smth was wrong" << std::endl;
	}

	return 0;
}