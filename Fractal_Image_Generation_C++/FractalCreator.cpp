#include "pch.h"
#include "FractalCreator.h"
#include "Mandelbrot.h"
#include <assert.h>


void FractalCreator::Run(string name)
{
	CalculateIteration();
	CalculateTotalIterations();
	CalculateRangeTotals();
	DrawFractal();
	WriteBitmap("test.bmp");
}

void FractalCreator::AddRange(double rangeEnd, const RGB& rgb)
{
	m_Ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
	m_Colors.push_back(rgb);

	if (m_bGotFirstRange)
	{
		m_RangeTotals.push_back(0);
	}

	m_bGotFirstRange = true;
}

int FractalCreator::GetRange(int iterations) const
{
	int range = 0;

	for (int i = 1; i < m_Ranges.size(); i++)
	{
		range = i;

		if (m_Ranges[i] > iterations)
		{
			break;
		}
	}

	range--;

	assert(range > -1);
	assert(range < m_Ranges.size());

	return range;
}

void FractalCreator::AddZoom(const Zoom& zoom)
{
	m_ZoomList.Add(zoom);
}

FractalCreator::FractalCreator(int width, int height) : m_Width(width), m_Height(height),
m_Histogram(new int[Mandelbrot::MAX_ITERATIONS]), m_Fractal(new int[m_Width * m_Height]),
m_Bitmap(m_Width, m_Height), m_ZoomList(m_Width, m_Height)
{
	// fill arrays with 0
	fill(m_Histogram.get(), m_Histogram.get() + Mandelbrot::MAX_ITERATIONS, 0);
	fill(m_Fractal.get(), m_Fractal.get() + m_Width * m_Height, 0);

	m_ZoomList.Add(Zoom(m_Width / 2, m_Height / 2, 4.0 / m_Width));
}


FractalCreator::~FractalCreator()
{

}

void FractalCreator::CalculateIteration()
{
	// Stores the data
	for (int y = 0; y < m_Height; y++) 
	{
		for (int x = 0; x < m_Width; x++) 
		{
			pair<double, double> coords = m_ZoomList.DoZoom(x, y);

			int iterations = Mandelbrot::getIterations(coords.first, coords.second);

			m_Fractal[y * m_Width + x] = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS) {
				m_Histogram[iterations]++;
			}

		}
	}
}

void FractalCreator::CalculateRangeTotals()
{
	int rangeIndex = 0;

	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
	{
		int pixels = m_Histogram[i];

		if (i >= m_Ranges[rangeIndex + 1])
		{
			rangeIndex++;
		}

		m_RangeTotals[rangeIndex] += pixels;
	}
}

void FractalCreator::CalculateTotalIterations()
{
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) 
	{
		m_Total += m_Histogram[i];
	}
}

void FractalCreator::DrawFractal()
{
	// Draws the image
	for (int y = 0; y < m_Height; y++) 
	{
		for (int x = 0; x < m_Width; x++) 
		{
			int iterations = m_Fractal[y * m_Width + x];

			int range = GetRange(iterations);
			int rangeTotal = m_RangeTotals[range];
			int rangeStart = m_Ranges[range];

			RGB& startColor = m_Colors[range];
			RGB& endColor = m_Colors[range + 1];
			RGB colorDiff = endColor - startColor;

			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			if (iterations != Mandelbrot::MAX_ITERATIONS)
			{
				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++) {
					totalPixels += m_Histogram[i];
				}

				red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
			}

			m_Bitmap.setPixel(x, y, red, green, blue);

		}
	}
}

void FractalCreator::WriteBitmap(string name)
{
	m_Bitmap.write(name);
}
