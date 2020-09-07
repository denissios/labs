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

int UGetInt(const char* msg)
{
	std::cout << msg;
	int a;
	while (!(std::cin >> a) || a < 0)
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');

		std::cout << "Enter unsigned int!" << std::endl << msg;
	}
	std::cin.ignore(32767, '\n');

	return a;
}