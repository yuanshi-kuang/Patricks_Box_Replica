#pragma once  
#include "Block.h"
Block::Block()
{
	map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z);
}
Block::Block(const string& code)
{
	load(code);
}
bool Block::load(const string& code)
{
	XYZ eye{ 0,1,1 };
	XYZ mapsize_data = { 0,1,3 };
	if (!code.empty())
	{
		for (int i = 0; i < code.size(); i++)
		{
			if (code[i] == '\n') { continue; }
			if (code[i] != '|')
			{
				//如果没到结尾就将当前的 x 长度 +1
				if (code[i] != ';') { eye.x++; }
				else
				{
					//如果 mapsize 为第一行，则将当前 x 长度赋值
					if (mapsize_data.x == 0) { mapsize_data.x = eye.x; }
					//如果 mapsize 不为第一行，且上一行的长度和这行不同，就加载失败。
					else if (mapsize_data.x != 0 && mapsize_data.x != eye.x) { return false; }
					eye = { 0,eye.y++,eye.z };
				}
			}
			else
			{
				if (mapsize_data.y == 1) { mapsize_data.y = eye.y; }
				else if (mapsize_data.y != 1 && mapsize_data.y != eye.y) { return false; }
				eye = { 0,1,eye.z++ };
			}
		}
		if (mapsize_data.x != 0 && mapsize_data.x != eye.x || mapsize_data.y != 1 && mapsize_data.y != eye.y || eye.z > 3) { return false; }
		mapsize_data.x = eye.x;
		mapsize_data.y = eye.y;
	}
	else { return false; }
	mapsize = mapsize_data;
	//全初始化为null
	map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z, null);
	switch (eye.z)
	{
	case 1:loading_a(code); break;
	case 2:loading_b(code); break;
	case 3:loading_c(code); break;
	default:break;
	}
	return true;
}
void Block::loading_a(const string & code)
{
	//字符索引
	int eye = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { eye = 0; }
				if (code[eye] == ';') { eye++; }
				//第0层修改为背景
				if (i == 0)
				{
					maps(i, j, k) = flor;
					maps(i, j, k).Location = { k,j,i };
				}
				//第1,2层按照地图代码进行更新。
				else if (i == 1)
				{
					switch (code[eye])
					{
					case ';':break;
					case '0':break;
					case '1':break;
					case '2':break;
					case '3':break;
					case '4':break;
					case '5':maps(i, j, k) = pexit; pexitend = &maps(i, j, k);          break;
					case '6':maps(i, j, k) = bexit; bexitend.push_back(&maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
				else if (i == 2)
				{
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; havep = true; pat = &maps(i, j, k); break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':break;
					case '6':break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
			}
		}
	}
}
void Block::loading_b(const string& code)
{
	//字符索引
	int eye = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { eye = 0; }
				if (code[eye] == ';') { eye++; }
				//第0层
				if (i == 0)
				{
					maps(i, j, k) = flor;
					maps(i, j, k).Location = { k,j,i };
				}
				//第1层
				else if (i == 1)
				{
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':maps(i, j, k) = pexit; pexitend = &maps(i, j, k);          break;
					case '6':maps(i, j, k) = bexit; bexitend.push_back(&maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
				//第2层
				else if (i == 2)
				{
					if (j == 0 && k == 0) { eye = 0; }
					if (code[eye] == ';') { eye++; }
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; havep = true; pat = &maps(i, j, k); break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':maps(i, j, k) = pexit;  break;
					case '6':maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
			}
		}
	}
}
void Block::loading_c(const string& code)
{
	//字符索引
	int eye = 0;
	//初始化每个元素
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				//重置地图代码索引，跳过换行
				if (j == 0 && k == 0) { eye = 0; }
				if (code[eye] == ';') { eye++; }
				//第0层
				if (i == 0)
				{
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':maps(i, j, k) = pexit;  break;
					case '6':maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
				//第1层
				else if (i == 1)
				{
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':maps(i, j, k) = pexit; pexitend = &maps(i, j, k);          break;
					case '6':maps(i, j, k) = bexit; bexitend.push_back(&maps(i, j, k)); break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
				//第2层
				else if (i == 2)
				{
					if (j == 0 && k == 0) { eye = 0; }
					if (code[eye] == ';') { eye++; }
					switch (code[eye])
					{
					case ';':break;
					case '0':maps(i, j, k) = null;   break;
					case '1':maps(i, j, k) = flor;   break;
					case '2':maps(i, j, k) = player; havep = true; pat = &maps(i, j, k); break;
					case '3':maps(i, j, k) = box;    break;
					case '4':maps(i, j, k) = wall;   break;
					case '5':maps(i, j, k) = pexit;  break;
					case '6':maps(i, j, k) = bexit;  break;
					default:break;
					}
					maps(i, j, k).Location = { k,j,i };
					eye++;
				}
			}
		}
	}
}
BlockElement& Block::maps(const int& z, const int& y, const int& x) 
{
	return map[z * (mapsize.y * mapsize.x) + y * mapsize.x + x]; 
}
BlockElement& Block::maps(const int& y, const int& x)
{
	return map[2 * (mapsize.y * mapsize.x) + y * mapsize.x + x];
}
