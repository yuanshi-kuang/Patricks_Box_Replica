#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "WXYZpro.cpp"
#include "BlockElement.cpp"
using namespace std;
class Block
{
public:
	vector<BlockElement> map;
	XYZ mapsize = { 0,1,3 };//地图大小
	BlockElement* pexitend = nullptr;//玩家终点
	vector<BlockElement*> bexitend;//箱子终点
	BlockElement* pat = nullptr;//临时玩家指针
	bool Animation = false;//动画播放状态
	bool havep = false;//有玩家
	Block();
	Block(const string& code);
	bool load(const string& code);
	void loading_a(const string& code);
	void loading_b(const string& code);
	void loading_c(const string& code);
	BlockElement& maps(const int& z, const int& y, const int& x);
	BlockElement& maps(const int& y, const int& x);
};

