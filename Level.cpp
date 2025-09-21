#include "Level.h"
void Level::move(const int& x, const int& y, const Direction& dir)
{
	if (havep)
	{
		Block* worddata = &word[pats.w];//关卡
		BlockElement* wordpbedata = word[pats.w].maps(pats.z, pats.y, pats.x); //pat位置的元素
		BlockElement* getnext = word[pats.w].maps(pats.z, pats.y + y, pats.x + x);//getnext
		if (getnext->push)
		{
			//基础设置
			XYZ eye = { pats.x,pats.y,pats.z };//观察位置
			int iterate = 0;//迭代次数
			BlockElement* data = nullptr;//缩短名称
			eye.add(x, y);//偏移
			iterate++;//迭代层数

			//向前遍历
			while (true)
			{
				data = word[pats.w].maps(eye.z, eye.y, eye.x);
				if (data->push && data->name != null) 
				{
					eye.add(x, y); 
					iterate++; 
					continue; 
				}
				else if (!data->push) 
				{
					direction = dir; 
					return; 
				}
				else if (data->name == null) 
				{
					iterate--; 
					break; 
				}
			}

			//执行移动
			for (int i = iterate; i >= 0; i--)
			{
				//State name = worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->name;
				//worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->del();
				//*worddata->maps(pats.z, pats.y + y * (i + 1), pats.x + x * (i + 1)) = name;
				*worddata->maps(pats.z, pats.y + y * (i + 1), pats.x + x * (i + 1)) = worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->name;
				worddata->maps(pats.z, pats.y + y * i, pats.x + x * i)->del();
			}
			pats.x += x;//更新玩家位置
			pats.y += y;
			direction = dir;//更新玩家方向
			
			//胜利判定
			if (pexitend.w != -1 || !bexitend.empty())
			{
				bool pwin = false;
				bool bwin = false;
				if (pexitend.w != -1)
				{
					BlockElement* pdata = word[pexitend.w].maps(pexitend.z + 1, pexitend.y, pexitend.x);
					if (pdata->name == player) 
					{
						pwin = true; 
					}
				}
				if (!bexitend.empty())
				{
					int boxwin = 0;
					for (const auto& deta : bexitend)
					{
						BlockElement* bdata = word[deta.w].maps(deta.z + 1, deta.y, deta.x);
						if (bdata->name == box) 
						{
							boxwin++; 
						}
					}
					bwin = (boxwin == bexitend.size());
				}
				//不存在pexit和bexit同时没有的情况
				//00 00 error
				//10 00 false
				//11 00 true //有额外的pexitend.w == -1保底
				//10 10 false
				//11 11 true
				if ((pexitend.w != -1 && pwin || pexitend.w == -1) && (!bexitend.empty() && bwin || bexitend.empty())) 
				{
					victory = true; 
				}
			}
		}
		else 
		{
			direction = dir; 
		}
	}
}
void Level::addblock(const string& str)
{
	word.push_back(str);
	//集合玩家终点
	if (word.back().pexitend != nullptr)
	{
		XYZ* location = &word.back().pexitend->Location;
		pexitend = { int(word.size()) - 1, location->x, location->y, location->z };
	}
	//遍历所有世界，集合所有箱子终点。
	for (BlockElement* data : word.back().bexitend)
	{
		if (data != nullptr)
		{
			bexitend.push_back({ int(word.size()) - 1, data->Location.x, data->Location.y, data->Location.z });
		}
	}
	//更新pats位置
	if (word.back().havep)
	{
		havep = true;
		pats = word.back().pat->Location;
	}
}
void Level::up() 
{
	move(0, -1, Direction::up); 
}
void Level::down() 
{
	move(0, 1, Direction::down); 
}
void Level::left() 
{
	move(-1, 0, Direction::left); 
}
void Level::right() 
{
	move(1, 0, Direction::right); 
}
