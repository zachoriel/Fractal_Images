#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <math.h>
#include <vector>
#include "Zoom.h"
#include "Bitmap.h"
#include "ZoomList.h"
#include "RGB.h"

using namespace std;

class FractalCreator
{
private:
	int m_Width;
	int m_Height;
	unique_ptr<int[]> m_Histogram;
	unique_ptr<int[]> m_Fractal;
	Bitmap m_Bitmap;
	ZoomList m_ZoomList;
	int m_Total{ 0 };

	vector<int> m_Ranges;
	vector<RGB> m_Colors;
	vector<int> m_RangeTotals;

	bool m_bGotFirstRange{ false };

private:
	void CalculateIteration();
	void CalculateTotalIterations();
	void CalculateRangeTotals();
	void DrawFractal();
	void WriteBitmap(string name);
	int GetRange(int iterations) const;

public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();
	void AddRange(double rangeEnd, const RGB& rgb);
	void Run(string name);
	void AddZoom(const Zoom& zoom);
};

