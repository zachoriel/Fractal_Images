#pragma once

#include <vector>
#include <utility>
#include "Zoom.h"

using namespace std;

class ZoomList
{
private:
	double m_xCenter{ 0 };
	double m_yCenter{ 0 };
	double m_Scale{ 1.0 };

	int m_Width{ 0 };
	int m_Height{ 0 };
	vector<Zoom> zooms;

public:
	ZoomList(int width, int height);
	void Add(const Zoom& zoom);
	pair<double, double> DoZoom(int x, int y);
};

