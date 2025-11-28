#pragma once  
#include "Level.h"
Level::Level()
{
	anim = vector<Animation>(0);
}
Level::Level(vector<string> code)
{
	load(code);
}
Level::~Level() = default;
bool Level::move(const int& x, const int& y, const Direction& dir) 
{
	if (havep)
	{
		//移动成功标识符
		bool go = false;
		//解压玩家所在地图worddata
		Block& playerblock = *tier.findblock(pats.w);
		//解压玩家所在元素wordpbedata
		BlockElement& playerelement = playerblock.maps(pats.y, pats.x);
		//将要推的元素
		BlockElement& next =playerblock.maps(pats.y + y, pats.x + x);
		if (next.push)
		{
			//眼睛位置
			XY eye = { pats.x + x,pats.y + y };
			//迭代次数
			int iterate = 1;
			//眼睛观察的元素
			BlockElement* eyeelement = nullptr;
			//向推动方向遍历
			while (true)
			{
				//更新眼睛观察的元素
				eyeelement = &playerblock.maps(eye.y, eye.x);
				//可推且不是空
				if (eyeelement->push && eyeelement->name != null)
				{
					eye.add(x, y);
					iterate++;
					continue;
				}
				//不能推
				else if (!eyeelement->push)
				{
					direction = dir;
					return false;
				}
				//空
				else if (eyeelement->name == null)
				{
					iterate--;
					break;
				}
			}
			//执行移动
			for (int i = iterate; i >= 0; i--)
			{
				go = true;
				playerblock.maps(pats.y + y * (i + 1), pats.x + x * (i + 1)) = playerblock.maps(pats.y + y * i, pats.x + x * i).name;
				playerblock.maps(pats.y + y * i, pats.x + x * i).del();
			}
			//更新玩家位置
			pats.x += x;
			pats.y += y;
			//更新玩家方向
			direction = dir;
			//胜利判定
			//至少有一个玩家终点(-1表没有玩家终点) 或 至少有一个箱子终点
			if (pexitend.w != -1 || !bexitend.empty())
			{
				bool pwin = false;
				bool bwin = false;
				if (pexitend.w != -1) { pwin = tier.findblock(pexitend.w)->maps(pexitend.z + 1, pexitend.y, pexitend.x).name == player; }
				if (!bexitend.empty())
				{
					int boxwin = 0;
					for (const auto& data : bexitend) { boxwin += (tier.findblock(data.w)->maps(data.z + 1, data.y, data.x).name == box); }
					bwin = (boxwin == bexitend.size());
				}
				//不存在pexit和bexit同时没有的情况
				//00 00 error
				//10 00 false
				//11 00 true //有额外的pexitend.w == -1保底
				//10 10 false
				//11 11 true
				victory = (pexitend.w != -1 && pwin || pexitend.w == -1) && (!bexitend.empty() && bwin || bexitend.empty());
			}
			//标签更换

		}
		else { direction = dir; }
		return go;
	}
	return false;
}
bool Level::load(vector<string> blockbox)
{
	for (int i = 0; i < blockbox.size(); i++)
	{
		if (!addblock(blockbox[i])) { return false; }
	}
	return true;
}
vector<string> Level::apart(string& code)
{

}
bool Level::addblock(const string& str = "")
{
	//创建一个新的节点
	Tree* tree_data = Tree::addtree(str);
	if (tree_data == nullptr) { return false; }
	Tree& newtree = *tree_data;
	tree_data = nullptr;
	//集合玩家终点
	if (newtree.pexitend != nullptr)
	{
		//如果之前也存在玩家，将采用最新添加的玩家。
		XYZ& location = newtree.pexitend->Location;
		pexitend = { newtree.worldnum, location.x, location.y, location.z };
	}
	//遍历新世界，集合所有箱子终点。
	for (BlockElement* blockelement : newtree.bexitend)
	{
		if (blockelement != nullptr)
		{
			bexitend.push_back({ newtree.worldnum, blockelement->Location.x, blockelement->Location.y, blockelement->Location.z });
		}
	}
	//更新pats位置
	if (newtree.havep)
	{
		//如果之前也存在玩家，将采用最新添加的玩家。
		havep = true;
		pats = newtree.pat->Location;
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
void player_render(int x, int y, Direction direction, IMAGES& box)
{
	switch (direction)
	{
	case Direction::done0:putimage_b(x, y, box.getimage("done"));   break;
	case Direction::up:   putimage_b(x, y, box.getimage("up"));     break;
	case Direction::down: putimage_b(x, y, box.getimage("down"));   break;
	case Direction::left: putimage_b(x, y, box.getimage("left"));   break;
	case Direction::right:putimage_b(x, y, box.getimage("right"));  break;
	default:break;
	}
}
void rendering(Level& level)
{
	bool running = true;
	int tick = 0;
	ExMessage msg{};
	IMAGES box;
	//解压玩家所在的世界
	Tree& block = *Tree::findblock(level.pats.w);
	box.addimage(L"png/背景.png", "flor");
	box.addimage(L"png/箱子.png", "box");
	box.addimage(L"png/墙.png", "wall");
	box.addimage(L"png/玩家终点.png", "pexit");
	box.addimage(L"png/箱子终点.png", "bexit");
	box.addimage(L"png/小红2/done.png", "done");
	box.addimage(L"png/小红2/up.png", "up");
	box.addimage(L"png/小红2/down.png", "down");
	box.addimage(L"png/小红2/left.png", "left");
	box.addimage(L"png/小红2/right.png", "right");
	BeginBatchDraw();
	while (running)
	{
		//开始计时
		DWORD start_time = GetTickCount();
		//胜利检测//TopMessageBox(NULL, L"提示", L"恭喜过关！", MB_OK);
		if (level.victory) { TopMessage(L"提示", L"恭喜过关！"); return; }
		//数值更换
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_UP:   level.up();    break;
				case VK_DOWN: level.down();  break;
				case VK_LEFT: level.left();  break;
				case VK_RIGHT:level.right(); break;
				default:break;
				}
			}
		}
		//清空
		cleardevice();
		//渲染
		for (int i = 0; i < block.mapsize.z; i++)//第1 2 3层  背景层 判定层 实体层
		{
			for (int j = 0; j < block.mapsize.y; j++)
			{
				for (int k = 0; k < block.mapsize.x; k++)
				{
					switch (block.maps(i, j, k).name)
					{
					case State::null:  
						break;
					case State::flor:  
						putimage_b(k, j, box.getimage("flor"));  
						break;
					case State::player:
						player_render(k, j, level.direction, box); 
						break;
					case State::box:   
						putimage_b(k, j, box.getimage("box"));     
						break;
					case State::wall:  
						putimage_b(k, j, box.getimage("wall"));    
						break;
					case State::pexit: 
						putimage_b(k, j, box.getimage("pexit"));   
						break;
					case State::bexit: 
						putimage_b(k, j, box.getimage("bexit"));   
						break;
					default:    
						break;
					}
				}
			}
		}
		//第4层 tag层
		for (int i = 0; i < block.Block::map.size(); i++)
		{
			//完成框
			for (int j = 0; j < block.Block::map[i].tag.size(); j++)
			{
				if (block.Block::map[i].tag[j] == "win")
				{
					XYZ& data = block.Block::map[i].Location;
					putimage_b(data.x, data.y, box.getimage("完成框"));
				}
			}
		}
		//提交
		FlushBatchDraw();
		//等待
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) { Sleep(1000 / 60 - delta_time); }
	}
	EndBatchDraw();
};

