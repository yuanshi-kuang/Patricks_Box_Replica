#pragma once
#include "Direction.h"
#include "Block.h"
#include "WXYZ.h"
using namespace std;
class Level
{
public:
	vector<Block> word;//世界列表
	WXYZ pats = { 0,0,0,0 };//玩家所在位置的4维编号
	Direction direction = Direction::down;//玩家方向
	//Tree tier;
	WXYZ pexitend = { -1,0,0,0 };//玩家终点
	vector<WXYZ> bexitend;//箱子终点
	bool victory = false;//胜利
	bool havep = false;//有玩家
	Level()
	{
		word = vector<Block>(0);
	}
	void move(const int& x, const int& y, const Direction& dir);
	void addblock(const string& str);
	void up();
	void down();
	void left();
	void right();
};


