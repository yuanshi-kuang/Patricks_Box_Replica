#pragma once
#include "XY.h"
#include "XYZ.h"
class WXYZ
{
public:
	int w = 0, 
		x = 0, 
		y = 0, 
		z = 0;
	void add(int ix = 0, int iy = 0, int iz = 0);
	WXYZ() 
	{}
	WXYZ(int x, int y)               
		:x(x), y(y) 
	{}
	WXYZ(int x, int y, int z)        
		:x(x), y(y), z(z) 
	{}
	WXYZ(int w, int x, int y, int z) 
		:w(w), x(x), y(y), z(z) 
	{}
	WXYZ(XY xy) 
		:x(xy.x), y(xy.y) 
	{}
	WXYZ(XYZ xyz) 
		:x(xyz.x), y(xyz.y), z(xyz.z) 
	{}
};

