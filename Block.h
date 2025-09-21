#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "XYZ.h"
#include "BlockElement.h"
using namespace std;
class Block
{
public:
	vector<BlockElement> map;
	XYZ mapsize = { 1,1,3 };//地图大小
	BlockElement* pexitend = nullptr;//玩家终点
	vector<BlockElement*> bexitend;//箱子终点
	BlockElement* pat = nullptr;//临时玩家指针
	bool havep = false;
	Block() 
	{
		map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z); 
	}
	Block(const string& code)
	{
		XYZ num{0,1,1};
		bool Yes = true;
		mapsize = { 0,1,3 };
		for (int i = 0; i < code.size(); i++)
		{
			if (code[i] != '|')
			{
				if (code[i] != '\n') { num.x++; }
				else
				{
					if (mapsize.x == 0) 
					{
						mapsize.x = num.x; 
					}
					else if (mapsize.x != 0 && mapsize.x != num.x) 
					{
						std::cout << "X错误！\n"; 
						mapsize = { 0,1,3 };
						Yes = false; 
						break; 
					}
					num.x = 0; 
					num.y++;
				}
			}
			else
			{
				if (mapsize.y == 1) 
				{
					mapsize.y = num.y; 
				}
				else if (mapsize.y != 1 && mapsize.y != num.y) 
				{
					std::cout << "Y错误！\n"; 
					mapsize = { 0,1,3 };
					Yes = false; 
					break; 
				}
				num = { 0,1,num.z++ };
			}
		}
		if (mapsize.x != 0 && mapsize.x != num.x) 
		{
			std::cout << "X错误！\n"; 
			mapsize = { 0,1,3 }; 
			Yes = false;
		}
		else if (mapsize.y != 1 && mapsize.y != num.y) 
		{
			std::cout << "Y错误！\n"; 
			mapsize = { 0,1,3 }; 
			Yes = false;
		}
		else if (num.z > 3) 
		{
			std::cout << "Z错误！\n"; 
			mapsize = { 0,1,3 }; 
			Yes = false;
		}
		mapsize.x = num.x, 
		mapsize.y = num.y;
		//全初始化为null
		map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z, null);
		if (Yes)
		{
			switch (num.z)
			{
			case 1:loading_a(code); break;
			case 2:loading_b(code); break;
			case 3:loading_c(code); break;
			default:break;
			}
		}
		else 
		{
			mapsize.x = 0, 
			mapsize.y = 0; 
		}
	}
	void loading_a(const string& code);
	void loading_b(const string& code);
	void loading_c(const string& code);
	BlockElement* maps(const int& z, const int& y, const int& x);
};

