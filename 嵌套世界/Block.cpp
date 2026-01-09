#pragma once  
#include "Block.h"
Block::Block()
{
	map = vector<BlockElement>(mapsize.x * mapsize.y * mapsize.z);
}
Block::Block(const json& jsonblock)
{
	load(jsonblock); 
}
//load或构造函数 由 tree使用工厂构造函数进行创造，即使有bool返回值，也无法传递回去。
//而且file已经对文件内容做了全方位检查，这里不需要2次检查。
void Block::load(const json& jsonblock)
{
	mapsize = { jsonblock["size"]["x"].get<int>(),jsonblock["size"]["y"].get<int>(),3 };
	map = vector <BlockElement>(mapsize.x * mapsize.y * 3,null);
	for (int z = 0; z < mapsize.z; z++)
	{
		for (int y = 0; y < mapsize.y; y++)
		{
			for (int x = 0; x < mapsize.x; x++)
			{
				maps(x, y, z).Location = { x, y, z };
			}
		}
	}
	if (jsonblock["size"]["z"] == 1) { loading_a(jsonblock); }
	else if (jsonblock["size"]["z"] == 2) { loading_b(jsonblock); }
	else if (jsonblock["size"]["z"] == 3) { loading_c(jsonblock); }
}
void Block::loading_a(const json& jsonblock)
{
	const json& jsonmap = jsonblock["map"];
	for (int y = 0; y < mapsize.y; y++)
	{
		for (int x = 0; x < mapsize.x; x++)
		{
			maps(x, y, 0) = flor;
		}
	}
	for (int y = 0; y < jsonmap[0].size(); y++)
	{
		for (int x = 0; x < jsonmap[0][y].size(); x++)
		{
			const json& jsonelement = jsonmap[0][y][x];
			BlockElement& element1 = maps(x, y, 1);
			BlockElement& element2 = maps(x, y, 2);
			if (jsonelement.is_string())
			{
				string element = jsonelement.get<string>();
				if (element == "null") { continue; }
				else if (element == "flor") { continue; }
				else if (element == "player") { element2 = string("player"); pat = { x, y, 2 }; havep = true; }
				else if (element == "box")    { element2 = string("box"); }
				else if (element == "wall")   { element2 = string("wall"); }
				else if (element == "pexit")  { element1 = string("pexit"); pexitend = &element1; }
				else if (element == "bexit")  { element1 = string("bexit"); bexitend.push_back(&element1); }
				else { continue; }
			}
			else if (jsonelement.is_object()) { element2.son = jsonelement["word"].get<int>(); }
		}
	}
}
void Block::loading_b(const json& jsonmap){}
void Block::loading_c(const json& jsonblock)
{
	const json& jsonmap = jsonblock["map"];
	for (int i = 0; i < mapsize.z - 1; i++)
	{
		for (int j = 0; j < mapsize.y - 1; j++)
		{
			for (int k = 0; k < mapsize.x - 1; k++)
			{
				maps(k, j, i).Location = { k,j,i };
				const json& jsonelement = jsonmap[i][j][k];
				const string& jsonelementstring = jsonelement.get<string>();
				BlockElement& eyeelenent = maps(k, j, i);
				//实体层
				if (i == 0)
				{
					if (jsonelement.is_string())
					{
						if (jsonelement == "null") { continue; }
						else if (jsonelement == "flor") { eyeelenent = jsonelementstring; }
						else if (jsonelement == "player") { eyeelenent = jsonelementstring; pat = { j, i, 2 }; havep = true; }
						else if (jsonelement == "box")    { eyeelenent = jsonelementstring;
						}
						else if (jsonelement == "wall")   { eyeelenent = jsonelementstring;
						}
						else if (jsonelement == "pexit")  { eyeelenent = jsonelementstring;
						}
						else if (jsonelement == "bexit")  { eyeelenent = jsonelementstring;
						}
						else { continue; }
					}
					else if (jsonelement.is_array())
					{

					}
				}
				//判定层
				else if (i == 1)
				{
					if (jsonelement == "null")        { continue; }
					else if (jsonelement == "flor")   { eyeelenent = jsonelementstring;}
					else if (jsonelement == "player") { eyeelenent = jsonelementstring;}
					else if (jsonelement == "box")    { eyeelenent = jsonelementstring;}
					else if (jsonelement == "wall")   { eyeelenent = jsonelementstring;}
					else if (jsonelement == "pexit")  { eyeelenent = jsonelementstring; pexitend = &maps(j, i, 1); }
					else if (jsonelement == "bexit")  { eyeelenent = jsonelementstring; bexitend.push_back(&maps(j, i, 1)); }
					else { continue; }
				}
				//背景层
				else if (i == 2)
				{ 
					if (jsonelement == "null")        { continue; }
					else if (jsonelement == "flor")   { eyeelenent = jsonelementstring;}
					else if (jsonelement == "player") { eyeelenent = jsonelementstring;}
					else if (jsonelement == "box")    { eyeelenent = jsonelementstring;}
					else if (jsonelement == "wall")   { eyeelenent = jsonelementstring;}
					else if (jsonelement == "pexit")  { eyeelenent = jsonelementstring;}
					else if (jsonelement == "bexit")  { eyeelenent = jsonelementstring;}
					else { continue; }
				}
			}
		}
	}
}
//void Block::loading_b(const json& jsonmap)
//{
//	for (int i = 0; i < mapsize.y; i++)
//	{
//		for (int j = 0; j < mapsize.x; j++)
//		{
//			maps(j, i, 0) = flor;
//		}
//	}
//	for (int i = 0; i < jsonmap.size(); i++)
//	{
//		for (int j = 0; j < jsonmap[i].size(); j++)
//		{
//			for (int k = 0; k < jsonmap[i][j].size(); k++)
//			{
//				//实体层
//				if (i == 0)
//				{
//					if (jsonmap[i][j][k] == "null")        { continue; }
//					else if (jsonmap[i][j][k] == "flor")   { continue; }
//					else if (jsonmap[i][j][k] == "player") { maps(k, j, i) = jsonmap[i][j][k].get<string>(); pat = { j, i, 2 }; havep = true; }
//					else if (jsonmap[i][j][k] == "box")    { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "wall")   { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "pexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "bexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else { continue; }
//				}
//				//判定层
//				else if (i == 1)
//				{
//					if (jsonmap[i][j][k] == "null")        { continue; }
//					else if (jsonmap[i][j][k] == "flor")   { continue; }
//					else if (jsonmap[i][j][k] == "player") { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "box")    { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "wall")   { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "pexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); pexitend = &maps(j,i,1);}
//					else if (jsonmap[i][j][k] == "bexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); bexitend.push_back(&maps(j, i, 1));}
//					else { continue; }
//				}
//			}
//		}
//	}
//}

//void Block::loading_c(const json& jsonmap)
//{
//	for (int i = 0; i < jsonmap.size(); i++)
//	{
//		for (int j = 0; j < jsonmap[i].size(); j++)
//		{
//			for (int k = 0; k < jsonmap[i][j].size(); k++)
//			{
//				maps(k, j, i).Location = { k,j,i };
//				//实体层
//				if (i == 0)
//				{
//					if (jsonmap[i][j][k] == "null")        { continue; }
//					else if (jsonmap[i][j][k] == "flor")   { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "player") { maps(k, j, i) = jsonmap[i][j][k].get<string>(); pat = { j, i, 2 }; havep = true; }
//					else if (jsonmap[i][j][k] == "box")    { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "wall")   { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "pexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "bexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); }
//					else { continue; }
//				}
//				//判定层
//				else if (i == 1)
//				{
//					if (jsonmap[i][j][k] == "null")        { continue; }
//					else if (jsonmap[i][j][k] == "flor")   { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "player") { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "box")    { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "wall")   { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "pexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); pexitend = &maps(j, i, 1); }
//					else if (jsonmap[i][j][k] == "bexit")  { maps(k, j, i) = jsonmap[i][j][k].get<string>(); bexitend.push_back(&maps(j, i, 1)); }
//					else { continue; }
//				}
//				//背景层
//				else if (i == 2)
//				{ 
//					if (jsonmap[i][j][k] == "null")        { continue; }
//					else if (jsonmap[i][j][k] == "flor")   { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "player") { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "box")    { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "wall")   { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "pexit")  { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else if (jsonmap[i][j][k] == "bexit")  { maps(i, j, k) = jsonmap[i][j][k].get<string>(); }
//					else { continue; }
//				}
//			}
//		}
//	}
//}
void Block::printmapstruct()
{
	for (int i = 0; i < mapsize.z; i++)
	{
		for (int j = 0; j < mapsize.y; j++)
		{
			for (int k = 0; k < mapsize.x; k++)
			{
				if (maps(k, j, i).name == null)        { cout << "null   "; }
				else if (maps(k, j, i).name == flor)   { cout << "flor   "; }
				else if (maps(k, j, i).name == player) { cout << "player "; }
				else if (maps(k, j, i).name == box)    { cout << "box    "; }
				else if (maps(k, j, i).name == wall)   { cout << "wall   "; }
				else if (maps(k, j, i).name == pexit)  { cout << "pexit  "; }
				else if (maps(k, j, i).name == bexit)  { cout << "bexit  "; }
				else { continue; }
			}
			cout << endl;
		}
		cout << endl;
	}
}
BlockElement& Block::maps(const int& x, const int& y, const int& z) 
{
	return map[z * (mapsize.y * mapsize.x) + y * mapsize.x + x]; 
}
BlockElement& Block::maps(const int& x, const int& y)
{
	return map[2 * (mapsize.y * mapsize.x) + y * mapsize.x + x];
}

