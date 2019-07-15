#pragma once

struct Zoom
{
	int x{ 0 };
	int y{ 0 };
	double scale{ 0.0 };

public:
	Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {};

};

