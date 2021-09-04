#include "ColorAverager.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

ColorAverager::ColorAverager(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	totalPixels = w * h;

	hdcSource = GetDC(NULL);
	hdcMemory = CreateCompatibleDC(hdcSource);

	bmpInfo.bmiHeader.biSize = sizeof(bmpInfo.bmiHeader);
	bmpInfo.bmiHeader.biWidth = w;
	bmpInfo.bmiHeader.biHeight = h;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;
	bmpInfo.bmiHeader.biSizeImage = w * 4 * h;
	bmpInfo.bmiHeader.biClrUsed = 0;
	bmpInfo.bmiHeader.biClrImportant = 0;

	hBitmap = CreateDIBSection(hdcSource, &bmpInfo, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, NULL);
	SelectObject(hdcMemory, hBitmap);
}


ColorAverager::~ColorAverager()
{
	DeleteDC(hdcSource);
	DeleteDC(hdcMemory);
	DeleteObject(hBitmap);
}


void ColorAverager::getAverage(Color* average)
{
	if (!average) return;

	avgR = 0;
	avgG = 0;
	avgB = 0;

	BitBlt(hdcMemory, 0, 0, w, h, hdcSource, x, y, SRCCOPY);

	for (int i = 0; i < (w * 4 * h); i += 4)
	{
		red = (int)bitPointer[i + 2];
		green = (int)bitPointer[i + 1];
		blue = (int)bitPointer[i];

		avgR += red;
		avgG += green;
		avgB += blue;
	}

	avgR /= totalPixels;
	avgG /= totalPixels;
	avgB /= totalPixels;

	average->r = (int)avgR;
	average->g = (int)avgG;
	average->b = (int)avgB;
}

PYBIND11_MODULE(screen_color_avg, handle) {
	handle.doc() = "Get average color from given screen region.";

	py::class_<ColorAverager>(
		handle, "ColorAverager"
	)
	.def(py::init<int, int, int, int>())
	.def("get_average", &ColorAverager::getAverage)
	;

	py::class_<Color>(
		handle, "Color"
	)
	.def(py::init<int, int, int>())
	.def_readwrite("r", &Color::r)
	.def_readwrite("g", &Color::g)
	.def_readwrite("b", &Color::b)
	;
}
