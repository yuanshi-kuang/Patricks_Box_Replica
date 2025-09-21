#include "Block.h"
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
