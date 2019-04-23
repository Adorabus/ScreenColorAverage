#pragma once

#include <Ole2.h>
#include <OleCtl.h>

struct Color {
	int r, g, b;
};

class ColorAverager
{
	int x, y, w, h,
		red, green, blue;

	long avgR, avgG, avgB, totalPixels;

	HDC hdcSource, hdcMemory;
	BYTE* bitPointer;
	BITMAPINFO bmpInfo;
	HBITMAP hBitmap;

public:
	ColorAverager(int x, int y, int w, int h);
	~ColorAverager();

	void getAverage(Color* average);
};

