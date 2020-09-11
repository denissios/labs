#include "util.h"

int GetInt(const char* msg)
{
	std::cout << msg;
	int a;
	while (!(std::cin >> a))
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');

		std::cout << "Enter int!" << std::endl << msg;
	}

	return a;
}
