#pragma once
#include "XY.h"
class XYZ
{
public:
	int x = 0, 
		y = 0, 
		z = 0;
	void add(int ix = 0, int iy = 0, int iz = 0);
	XYZ() 
	{}
	XYZ(int x, int y) 
		:x(x), y(y)
	{}
	XYZ(int x, int y, int z) 
		:x(x), y(y), z(z) 
	{}
	XYZ(XY xy) 
		:x(xy.x), y(xy.y) 
	{}
};

