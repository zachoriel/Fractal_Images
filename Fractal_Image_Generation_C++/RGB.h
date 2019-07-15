#pragma once
struct RGB
{
	double r;
	double g;
	double b;

	RGB(double r, double g, double b);
};

RGB operator-(const RGB& first, const RGB& second);

