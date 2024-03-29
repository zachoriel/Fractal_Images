#include "pch.h"
#include <iostream>
#include "FractalCreator.h"
#include "Zoom.h"

using namespace std;

int main() 
{
	FractalCreator fractalCreator(800, 600);

	fractalCreator.AddRange(0.0, RGB(0, 0, 65));
	fractalCreator.AddRange(0.3, RGB(255, 150, 41));
	fractalCreator.AddRange(0.5, RGB(255, 225, 195));
	fractalCreator.AddRange(1.0, RGB(255, 255, 255));

	fractalCreator.AddZoom(Zoom(295, 202, 0.1));
	fractalCreator.AddZoom(Zoom(312, 304, 0.1));
	fractalCreator.Run("Fractal1.bmp");

	cout << "Finished." << endl;
	return 0;
}