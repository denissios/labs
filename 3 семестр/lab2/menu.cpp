#include "menu.h"

#define OPTS_NUM 7

typedef void (*opt_t)(nefroid&);

static const opt_t OPTS[OPTS_NUM] =
{
	&SetRadius,
	&GetRadius,
	&GetLength,
	&GetRadiusCurvature,
	&GetSquare,
	&Get_XY,
	&GetEquation
};

void dialog(nefroid &Nefroid)
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
			OPTS[choice - 1](Nefroid);
	}
}

void menu()
{
	std::cout <<
		"0. Exit" << std::endl <<
		"1. Set Radius" << std::endl <<
		"2. Get Radius" << std::endl <<
		"3. Get Length" << std::endl <<
		"4. Get Radius Curvature" << std::endl <<
		"5. Get Square" << std::endl <<
		"6. Get XY" << std::endl <<
		"7. Get Equation" << std::endl;
}

void SetRadius(nefroid &Nefroid)
{
	double radius = 0;
	radius = GetNumber<double>("Enter radius: ");
	if (radius < 0)
	{
		std::cout << "Radius must be > 0!" << std::endl << std::endl;
		return;
	}
	Nefroid.SetRadius(radius);
	std::cout << std::endl;
}

void GetRadius(nefroid &Nefroid)
{
	std::cout << "Radius = " << Nefroid.GetRadius() << std::endl << std::endl;
}

void GetLength(nefroid &Nefroid)
{
	std::cout << "Length = " << Nefroid.GetLength() << std::endl << std::endl;
}

void GetRadiusCurvature(nefroid &Nefroid)
{
	double t = 0;
	t = GetNumber<double>("Enter t: ");
	std::cout << "Radius curveture = " << Nefroid.GetRadiusCurvature(t) << std::endl << std::endl;
}

void GetSquare(nefroid &Nefroid)
{
	std::cout << "Square = " << Nefroid.GetSquare() << std::endl << std::endl;
}

void Get_XY(nefroid &Nefroid)
{
	double t = 0;
	t = GetNumber<double>("Enter t: ");
	std::cout << "X: " << Nefroid.Get_X(t) << std::endl << "Y: " << Nefroid.Get_Y(t) << std::endl << std::endl;
}

void GetEquation(nefroid &Nefroid)
{
	const char* s = Nefroid.GetEquation();
	std::cout << s << std::endl << std::endl;
	if (!Nefroid.GetRadius())
		return;
	delete[] s;
}
