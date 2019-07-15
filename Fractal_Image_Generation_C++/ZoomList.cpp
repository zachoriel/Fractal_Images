#include "pch.h"
#include "ZoomList.h"

using namespace std;


ZoomList::ZoomList(int width, int height) : m_Width(width), m_Height(height)
{

}

void ZoomList::Add(const Zoom& zoom)
{
	zooms.push_back(zoom);

	m_xCenter += (zoom.x - m_Width / 2) * m_Scale;
	m_yCenter += -(zoom.y - m_Height / 2) * m_Scale;

	m_Scale *= zoom.scale;
}

pair<double, double> ZoomList::DoZoom(int x, int y)
{
	double xFractal = (x - m_Width / 2) * m_Scale + m_xCenter;
	double yFractal = (y - m_Height / 2) * m_Scale + m_yCenter;

	return pair<double, double>(xFractal, yFractal);
}
