#include "nefroid.h"

nefroid::nefroid()
{
	this->a = 0;
}

nefroid::nefroid(double a)
{
	this->a = a;
}

void nefroid::SetRadius(double a)
{
	this->a = a;
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

const char* nefroid::GetEquation()
{
	if (!this->a)
		return "(x ^ 2 + y ^ 2) ^ 3 = 0";

	const char* s1 = "(x ^ 2 + y ^ 2 - ) ^ 3 =  * y ^ 2";
	size_t length = strlen(s1) + 1;

	double a1 = 4 * pow(this->a, 2);
	double a2 = 108 * pow(this->a, 4);

	char num[20];

	sprintf_s(num, 20, "%.2f", a1);
	length += strlen(num);
	sprintf_s(num, 20, "%.2f", a2);
	length += strlen(num);

	char* s = new char[length];

	sprintf_s(s, length, "(x ^ 2 + y ^ 2 - %.2f) ^ 3 = %.2f * y ^ 2", a1, a2);

	return s;
}