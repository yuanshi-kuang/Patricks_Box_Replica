#pragma once
#include "WXYZpro.cpp"
#include "Block.h"
using namespace std;
//动画类
class Animation
{
	XY start{ 0,0 }, end{ 0,0 };//动画开始坐标，结束坐标
	int progress = 0;//动画进度
	bool open = false;//动画播放状态
	inline XY getxy()
	{ 
		//        基础坐标+ 2点距离的绝对值 / 10 * 进度(后置自加)    
		return XY(start.x + abs(start.x - end.x) / 10 * progress, start.y + abs(start.y - end.y) / 10 * progress++);
	}
};

