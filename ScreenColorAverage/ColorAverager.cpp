#include "ColorAverager.h"



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
