#pragma once
#include "Direction.h"
#include "Block.h"
#include "WXYZ.h"
using namespace std;
class Level
{
public:
	vector<Block> word;//�����б�
	WXYZ pats = { 0,0,0,0 };//�������λ�õ�4ά���
	Direction direction = Direction::down;//��ҷ���
	//Tree tier;
	WXYZ pexitend = { -1,0,0,0 };//����յ�
	vector<WXYZ> bexitend;//�����յ�
	bool victory = false;//ʤ��
	bool havep = false;//�����
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


