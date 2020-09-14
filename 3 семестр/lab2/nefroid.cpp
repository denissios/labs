#include "nefroid.h"

nefroid::nefroid()
{
	this->a = 0;
}

nefroid::nefroid(double a)
{
	if (a < 0)
	{
		this->a = 0;
		return;
	}
	this->a = a;
}

bool nefroid::SetRadius(double a)
{
	if (a < 0)
		return false;
	this->a = a;
	return true;
}

double nefroid::GetRadius()
{
	return this->a;
}

double nefroid::GetLength()
{
	return 24 * this->a;
}

double nefroid::GetRadiusCurvature(double t)
{
	return fabs(3 * this->a * sin(t * M_PI / 180));
}

double nefroid::GetSquare()
{
	return 12 * M_PI * pow(this->a, 2);
}

double nefroid::Get_X(double t)
{
	return (6 * this->a * cos(t * M_PI / 180) - 4 * this->a * pow(cos(t * M_PI / 180), 3));
}

double nefroid::Get_Y(double t)
{
	return (4 * this->a * pow(sin(t * M_PI / 180), 3));
}

std::string nefroid::GetEquation()
{
	if (!this->a)
		return "(x ^ 2 + y ^ 2) ^ 3 = 0";

	std::stringstream ss;
	ss << "(x ^ 2 + y ^ 2 - " << 4 * pow(this->a, 2) << ") ^ 3 = " << 108 * pow(this->a, 4) << " * y ^ 2";
	return ss.str();
}