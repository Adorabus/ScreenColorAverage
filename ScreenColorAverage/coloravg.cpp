#pragma once

#include <iostream>
#include "ColorAverager.h"


using namespace std;


int main(int argc, char* argv[])
{
	ColorAverager* ca = new ColorAverager(0, 0, 1920, 1080);
	Color c;

	while (true)
	{
		ca->getAverage(&c);

		cout
			<< c.r << ", "
			<< c.g << ", "
			<< c.b << endl;
	}

	delete ca;
}
