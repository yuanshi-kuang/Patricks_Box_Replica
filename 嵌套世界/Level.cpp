#pragma once  
#include "Level.h"
Level::Level()
{
	addblock(i);
}
Level::Level(json& jsonlevel)
{
	addblock(i);
	load(jsonlevel);
}
Level::~Level() = default;
bool Level::checkwin()
{
	// 检查是否存在任何终点
	bool hasPexit = (pexitend.w != -1);
	bool hasbexit = !bexitend.empty();
	// 情况1: 没有任何终点，永远无法胜利
	if (!hasPexit && !hasbexit) { return false; }
	// 情况2: 只存在玩家终点，只检查玩家终点
	if (hasPexit && !hasbexit)
	{
		Tree* targetBlock = Tree::findblock(pexitend.w);
		return targetBlock != nullptr && targetBlock->maps(pexitend.x, pexitend.y, 2).name == player;
	}
	// 情况3: 只存在箱子终点，只检查箱子终点
	else if (!hasPexit && hasbexit)
	{
		int boxwin = 0;
		for (const auto& data : bexitend)
		{
			Tree* targetBlock = Tree::findblock(data.w);
			if (targetBlock != nullptr && targetBlock->maps(data.x, data.y, 2).name == State::box) { boxwin++; }
		}
		return boxwin == bexitend.size();
	}
	// 情况4: 两种终点都存在，两者都必须满足
	// 检查玩家终点
	bool pwin = false;
	Tree* playerBlock = Tree::findblock(pexitend.w);
	if (playerBlock != nullptr) { pwin = (playerBlock->maps(pexitend.x, pexitend.y, 2).name == player); }
	// 检查箱子终点
	bool bwin = false;
	int boxwin = 0;
	for (const auto& data : bexitend)
	{
		Tree* boxBlock = Tree::findblock(data.w);
		if (boxBlock != nullptr && boxBlock->maps(data.x, data.y, 2).name == State::box) { boxwin++; }
	}
	bwin = (boxwin == bexitend.size());
	// 两种终点都必须满足
	return pwin && bwin;
}
pair<Tree*, BlockElement*> Level::GetNext(const Direction direction, const WXYZ& wxyz)
{
	bool io = false;
	XY OffsetXY, NextXY;
	switch (direction)
	{
	case Direction::up: { OffsetXY = { 0,-1 }; break; }
	case Direction::down: { OffsetXY = { 0,1 };  break; }
	case Direction::left: { OffsetXY = { -1,0 }; break; }
	case Direction::right: { OffsetXY = { 1,0 };  break; }
	default:break;
	}
	NextXY = { wxyz.x + OffsetXY.x ,wxyz.y + OffsetXY.y };
	Tree* blocktree = Tree::findblock(wxyz.w);
	pair<Tree*, BlockElement*> error = { nullptr, nullptr };
	if (blocktree == nullptr) { return error; }
	pair<Tree*, BlockElement*>  next = error;
	io = BoundaryCheck(NextXY, blocktree->mapsize);
	if (io) { next = { blocktree,&blocktree->maps(NextXY.x, NextXY.y, 2) }; }
	//父
	if (!io)
	{
		Tree* fathertree = blocktree->father;
		if (fathertree == nullptr)
		{
			Tree* i = Tree::findblock(0);
			return { i, &i->maps(i->mapsize.x / 2 + OffsetXY.x, i->mapsize.y / 2 + OffsetXY.y, 2) };
		}
		XYZ& FatherEntranceLocation = fathertree->maps(blocktree->FatherEntrance.x, blocktree->FatherEntrance.y).Location;
		return { fathertree,&fathertree->maps(FatherEntranceLocation.x + OffsetXY.x, FatherEntranceLocation.y + OffsetXY.y, 2) };
	}
	//子 子的获取由move决定,使用GetWordEntrance获取入口
	else if (next.second->name == word) { return next; }
	//本
	else { return next; }
}
pair<Tree*, BlockElement*> Level::GetWordEntrance(const Direction direction, Tree& tree)
{
	XY nextxy, halfmapsize = { tree.mapsize.x / 2 ,tree.mapsize.y / 2 };
	switch (direction)
	{
	case Direction::up: { nextxy = { halfmapsize.x,tree.mapsize.y - 1 }; break; }
	case Direction::down: { nextxy = { halfmapsize.x,0 };  break; }
	case Direction::left: { nextxy = { tree.mapsize.x - 1,halfmapsize.y }; break; }
	case Direction::right: { nextxy = { 0, halfmapsize.y };  break; }
	default:break;
	};
	return { &tree, &tree.Block::maps(nextxy.x, nextxy.y, 2) };
}
bool Level::BoundaryCheck(XY eye, XY mapsize)
{
	if (eye.x >= mapsize.x || eye.y >= mapsize.y || eye.x < 0 || eye.y < 0) { return false; }
	else { return true; }
}
bool Level::move(const int& x, const int& y, const Direction dir) 
{
	bool go = false;
	if (!havep) { return go; }
	Tree& playerblock = *Tree::findblock(pats.w);
	BlockElement& playerelement = playerblock.maps(pats.x, pats.y);
	pair<Tree*, BlockElement*> next = GetNext(dir, pats);
	pair<Tree*, BlockElement*> eye = { Tree::findblock(pats.w), &Tree::findblock(pats.w)->Block::maps(pats.x,pats.y,2) };
	vector<BlockElement*> pushlink;
	WXYZ NextPats = { next.first->worldnum,next.second->Location };
	pushlink.push_back(eye.second);
	//可能是1.指定的世界不存在2.目标方向的子世界不存在
	if (next.first == nullptr || !next.second->push) { direction = dir; return go; }
	while (true)
	{
		next = GetNext(dir, { eye.first->worldnum,eye.second->Location });
		if (next.first == nullptr) { direction = dir; return go; };
		pushlink.push_back(next.second);
		//世界不同
		if (next.first->worldnum != eye.first->worldnum) { eye.first = next.first; }
		//元素推动性
		if (next.second->push && next.second->name != null) { eye.second = next.second; continue; }
		else if (!next.second->push){ direction = dir; return go; }
		else if (next.second->name == null) { break; }
	}
	for (size_t i = pushlink.size() - 1; i > 0; i--)
	{
		*pushlink[i] = *pushlink[i - 1];
		pushlink[i - 1]->del();
	}
	go = true;
	pats = NextPats;
	direction = dir;
	return go;
}
bool Level::load(json& jsonlevel)
{
	for (auto& word : jsonlevel["word"])
	{
		addblock(word);
	}
	//进行父子链接
	for (int i = 1; i < Tree::getmapsize(); i++)
	{
		Tree& treeblock = *Tree::findblock(i);
		for (auto& x : treeblock.Block::map)
		{
			if (x.son == 0) { continue; }
			x.son = Tree::pairid(x.son);
			if (Tree::LinkFatherSon(i, x.son)) { return false; }
		}
	}
	return true;
}
bool Level::addblock(const json& jsonlevel)
{
	//创建一个新的节点
	Tree* newtree = Tree::addtree(jsonlevel);
	if (newtree == nullptr) { return false; }
	//集合玩家终点
	if (newtree->pexitend != nullptr)
	{
		//如果之前也存在玩家，将采用最新添加的玩家。
		XYZ& location = newtree->pexitend->Location;
		pexitend = { newtree->worldnum, location.x, location.y, location.z };
	}
	//遍历新世界，集合所有箱子终点。
	for (BlockElement* blockelement : newtree->bexitend)
	{
		if (blockelement != nullptr)
		{
			bexitend.push_back({ newtree->worldnum, blockelement->Location.x, blockelement->Location.y, blockelement->Location.z });
		}
	}
	//更新pats位置
	if (newtree->havep)
	{
		//如果之前也存在玩家，将采用最新添加的玩家。
		havep = true;
		pats.w = newtree->worldnum;
		pats = newtree->pat;
	}
	
	return true;
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
void Level::loadimage()
{
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
}
void Level::renderblock(Tree& block, const pair<float, float> drawpoint, const pair<float, float> zoom)
{
	for (auto& data : block.Block::map)
	{
		pair<float, float> xy = { data.Location.x * zoom.first + drawpoint.first+1, data.Location.y * zoom.second + drawpoint.second+1 };
		switch (data.name)
		{
		case State::null:break;
		case State::flor:  putimage_c(xy, zoom, box.getimage("flor")); break;
		case State::player:
			switch (direction)
			{
			case Direction::done0:putimage_c(xy, zoom, box.getimage("done")); break;
			case Direction::up:   putimage_c(xy, zoom, box.getimage("up")); break;
			case Direction::down: putimage_c(xy, zoom, box.getimage("down")); break;
			case Direction::left: putimage_c(xy, zoom, box.getimage("left")); break;
			case Direction::right:putimage_c(xy, zoom, box.getimage("right")); break;
			default:break;
			}break;
		case State::box:   putimage_c(xy, zoom, box.getimage("box")); break;
		case State::wall:  putimage_c(xy, zoom, box.getimage("wall")); break;
		case State::pexit: putimage_c(xy, zoom, box.getimage("pexit"));break;
		case State::bexit: putimage_c(xy, zoom, box.getimage("bexit"));break;
		default:break;
		}
	}
}
void Level::rendering()
{
	bool running = true;
	int tick = 0;
	ExMessage msg{};
	//cout << "pats.w：" << level.pats.w << endl;
	//解压玩家所在的世界，即使无玩家也会搜索到世界0
	Tree* block = Tree::findblock(pats.w);
	const float win80 = 0.8f; //窗口大小 
	const float win10 = 0.1f; //边距
	const float mewindowsize = maxwindowsize * win80;
	const pair<float,float> mezoom = { mewindowsize / block->mapsize.x ,mewindowsize / block->mapsize.y };
	const pair<float, float> medrawpoint = { maxwindowsize / 10 ,maxwindowsize / 10 };

	//getchar();

	loadimage();
	initgraph(maxwindowsize, maxwindowsize);
	BeginBatchDraw();
	while (running)
	{
		//开始计时
		DWORD start_time = GetTickCount();
		//胜利检测//TopMessageBox(NULL, L"提示", L"恭喜过关！", MB_OK);
		if (checkwin()) { TopMessage(L"提示", L"恭喜过关！"); return; }
		//数值更换
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_UP:   up();    break;
				case VK_DOWN: down();  break;
				case VK_LEFT: left();  break;
				case VK_RIGHT:right(); break;
				default:break;
				}
			}
		}
		//清空
		cleardevice();
		//渲染
		//父方块

		//主方块
		renderblock(*block, medrawpoint, mezoom);
		
		//子方块
		
		//第4层 tag层
		
		//for (int i = 0; i < block.Block::map.size(); i++)
		//{
		//	//完成框
		//	for (int j = 0; j < block.Block::map[i].tag.size(); j++)
		//	{
		//		if (block.Block::map[i].tag[j] == "win")
		//		{
		//			XYZ& data = block.Block::map[i].Location;
		//			putimage_b(drawPoint.x+data.x, drawPoint.y+data.y, box.getimage("完成框"));
		//		}
		//	}
		//}
		//提交
		FlushBatchDraw();
		//刷新渲染世界
		block = Tree::findblock(pats.w);
		//等待
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) { Sleep(1000 / 60 - delta_time); }
	}
	EndBatchDraw();
};




