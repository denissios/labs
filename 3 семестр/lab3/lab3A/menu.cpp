#include "menu.h"

#define OPTS_NUM 9

typedef void (*opt_t)(random_t&);

static const opt_t OPTS[OPTS_NUM] =
{
	&SetByLength,
	&SetByArray,
	&UpdateNumbers,
	&Print,
	&NewNumber,
	&GetByIndex,
	&Average,
	&To10,
	&Interval
};

void dialog(random_t& sample)
{
	while (true) {
		menu();

		int choice = 0;
		choice = GetNumber<int>("Your choice: ");
		std::cout << std::endl;

		if (!choice)
			break;

		else if (choice < 0 || choice > OPTS_NUM)
			std::cout << "[WARNING] Wrong option" << std::endl << std::endl;

		else
			OPTS[choice - 1](sample);
	}
}

void menu()
{
	std::cout <<
		"0. Exit" << std::endl <<
		"1. Set sample by length" << std::endl <<
		"2. Set sample by array" << std::endl <<
		"3. Update numbers" << std::endl <<
		"4. Print" << std::endl <<
		"5. New number" << std::endl <<
		"6. Get by index" << std::endl <<
		"7. Average" << std::endl <<
		"8. To 1.0" << std::endl <<
		"9. Get interval" << std::endl;
}

void SetByLength(random_t& sample)
{
	int length = -1;
	while (length < 0 || length > 100) {
		length = GetNumber<int>("Enter length of array: ");
		if (length < 0 || length > 100) {
			std::cout << "Invalid length. Try again" << std::endl;
		}
	}
	std::cout << std::endl;
	sample.SetSampleByLength(length);
}

void SetByArray(random_t& sample)
{
	int length = -1;
	while (length < 0 || length > 100) {
		length = GetNumber<int>("Enter length of array: ");
		if (length < 0 || length > 100) {
			std::cout << "Invalid length. Try again" << std::endl;
		}
	}

	float arr[100];
	for (size_t i = 0; i < length; i++) {
		arr[i] = (rand() % 10) / 10.0;
	}
	std::cout << std::endl;
	sample.SetSampleByArray(length, arr);
}

void UpdateNumbers(random_t &sample)
{
	sample.SetNewNumbers();
}

void Print(random_t& sample)
{
	std::cout << sample << std::endl << std::endl;
}

void NewNumber(random_t& sample)
{
	sample++;
}

void GetByIndex(random_t& sample)
{
	int index;
	index = GetNumber<int>("Enter index: ");
	if (index < 0 || index > sample.GetLength() - 1) {
		std::cout << "Index must be >= 0 and < " << sample.GetLength() << "!" << std::endl << std::endl;
		return;
	}
	std::cout << sample[index] << std::endl << std::endl;
}

void Average(random_t& sample)
{
	std::cout << "Average: " << sample.average() << std::endl << std::endl;
}

void To10(random_t& sample)
{
	~sample;
}

void Interval(random_t& sample)
{
	float down = 0, top = 0;
	down = GetNumber<float>("Enter down number: ");
	top = GetNumber<float>("Enter up number: ");
	std::cout << "Numbers in this interval: ";
	sample(down, top);
	std::cout << std::endl << std::endl;
}
