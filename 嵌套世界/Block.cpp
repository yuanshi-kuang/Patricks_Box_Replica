#include "Block.h"
Block::Block()
{
	map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z);
}
Block::Block(const string& code)
{
	XYZ num{ 0,1,1 };
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
void Block::loading_a(const string & code)
{
	//字符索引
	int data = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//第0层修改为背景
				if (i == 0)
				{
					*maps(i, j, k) = flor;
					maps(i, j, k)->Location = { k,j,i };
				}
				//第1,2层按照地图代码进行更新。
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':break;
					case '1':break;
					case '2':break;
					case '3':break;
					case '4':break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				else if (i == 2)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':break;
					case '6':break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
void Block::loading_b(const string& code)
{
	//字符索引
	int data = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//第0层
				if (i == 0)
				{
					*maps(i, j, k) = flor;
					maps(i, j, k)->Location = { k,j,i };
				}
				//第1层
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//第2层
				else if (i == 2)
				{
					if (j == 0 && k == 0) { data = 0; }
					if (code[data] == '\n') { data++; }
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
void Block::loading_c(const string& code)
{
	//字符索引
	int data = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { data = 0; }
				if (code[data] == '\n') { data++; }
				//第0层
				if (i == 0)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//第1层
				else if (i == 1)
				{
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit; pexitend = maps(i, j, k);          break;
					case '6':*maps(i, j, k) = bexit; bexitend.push_back(maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
				//第2层
				else if (i == 2)
				{
					if (j == 0 && k == 0) { data = 0; }
					if (code[data] == '\n') { data++; }
					switch (code[data])
					{
					case '\n':break;
					case '0':*maps(i, j, k) = null;   break;
					case '1':*maps(i, j, k) = flor;   break;
					case '2':*maps(i, j, k) = player; havep = true; pat = maps(i, j, k); break;
					case '3':*maps(i, j, k) = box;    break;
					case '4':*maps(i, j, k) = wall;   break;
					case '5':*maps(i, j, k) = pexit;  break;
					case '6':*maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k)->Location = { k,j,i };
					data++;
				}
			}
		}
	}
}
BlockElement* Block::maps(const int& z, const int& y, const int& x) 
{
	return &map[z * (mapsize.y * mapsize.x) + y * mapsize.x + x]; 
}
