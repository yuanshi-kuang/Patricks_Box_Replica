#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "WXYZpro.cpp"
#include "BlockElement.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Block
{
private:
	void loading_a(const json& jsonmap);
	void loading_b(const json& jsonmap);
	void loading_c(const json& jsonmap);
public:
	vector<BlockElement> map;
	XYZ mapsize = { 0,1,3 };//地图大小
	BlockElement* pexitend = nullptr;//玩家终点
	vector<BlockElement*> bexitend;//箱子终点
	XYZ pat = { 2,-1,-1 };//临时玩家坐标
	bool Animation = false;//动画播放状态
	bool havep = false;//有玩家
	Block();
	Block(const json& jsonblock);
	void load(const json& jsonblock);
	void printmapstruct();
	BlockElement& maps(const int& x, const int& y, const int& z);
	BlockElement& maps(const int& x, const int& y);
};

