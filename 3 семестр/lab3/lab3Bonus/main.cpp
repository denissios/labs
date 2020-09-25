// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "menu.hpp"

#include <iostream>

int main()
{
	DiceGroup Dice;
	try {
		dialog(Dice);
	}
	catch (const std::bad_alloc& b_a) {
		std::cerr << "Bad alloc" << std::endl << b_a.what() << std::endl;
		return 1;
	}
	catch (const std::out_of_range& ex) {
		std::cerr << "Bad alloc" << std::endl << ex.what() << std::endl;
		return 1;
	}
	catch (const std::exception& ex) {
		std::cerr << "Exception" << ex.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "Smth was wrong. Exit..." << std::endl;
		return 1;
	}

	return 0;
}