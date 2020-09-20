#include "random_t.h"
#include "menu.h"
#include "util.h"

int main()
{
	try {
		random_t sample;
		dialog(sample);
	}
	catch (std::bad_alloc& b_a) {
		std::cout << "Bad alloc" << std::endl << b_a.what() << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << "Exception" << ex.what() << std::endl;
	}
	catch (const int ex) {
		std::cout << "Error! Invalid index or length. Exit..." << std::endl;
	}
	catch (...) {
		std::cout << "Smth was wrong. Exit..." << std::endl;
	}

	return 0;
}