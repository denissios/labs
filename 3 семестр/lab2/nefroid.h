#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <sstream>

class nefroid
{
public:
	nefroid();
	nefroid(double a);
	bool SetRadius(double a);
	double GetRadius();
	double GetLength();
	double GetRadiusCurvature(double t);
	double GetSquare();
	double Get_X(double t);
	double Get_Y(double t);
	std::string GetEquation();

private:
	double a;
};