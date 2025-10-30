#include "Level.h"
Level::Level()
{
	anim = vector<Animation>(0);
}
bool Level::move(const int& x, const int& y, const Direction& dir)
{
	if (havep)
	{
		bool go = false;
		//Block* worddata = &word[pats.w];//关卡
		
		BlockElement* wordpbedata = word[pats.w].maps(pats.z, pats.y, pats.x); //pat位置的元素
		BlockElement* getnext = word[pats.w].maps(pats.z, pats.y + y, pats.x + x);//getnext
		if (getnext->push)
		{
			//基础设置
			XYZ eye = { pats.x,pats.y,pats.z };//观察位置
			int iterate = 0;//迭代次数
			BlockElement* data = nullptr;//缩短名称
			eye.XY::add(x, y);//偏移
			iterate++;//迭代层数
			//向前遍历
			while (true)
			{
				data = word[pats.w].maps(eye.z, eye.y, eye.x);
				if (data->push && data->name != null) 
				{
					eye.XY::add(x, y); 
					iterate++; 
					continue; 
				}
				else if (!data->push) 
				{
					direction = dir; 
					return false; 
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
				go = true;
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
			//标签更换

		}
		else 
		{
			direction = dir; 
		}
		return go;
	}
	return false;
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
void TopMessage(const std::wstring& title, const std::wstring& message)
{
	HANDLE hThread = CreateThread
	(
		NULL,
		0,
		[](LPVOID param) -> DWORD
		{
			auto data = (std::pair<std::wstring, std::wstring>*)param;
			MessageBoxW(NULL, data->second.c_str(), data->first.c_str(), MB_OK | MB_ICONINFORMATION);
			delete data;
			return 0;
		},
		new std::pair<std::wstring, std::wstring>(title, message),
		0,
		NULL
	);
	Sleep(100);
	if (HWND hWnd = FindWindowW(NULL, title.c_str())) { SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE); }
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}
void rendering(Level& level)
{
	bool running = true;
	int tick = 0;
	ExMessage msg{};
	IMAGES box;
	Block& block = level.word[level.pats.w];
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
					switch (block.maps(i, j, k)->name)
					{
					case State::null:  break;
					case State::flor:  putimage_b(k, j, box.getimage("flor")); break;
					case State::player:
						switch (level.direction)
						{
						case Direction::done0:putimage_b(k, j, box.getimage("done"));   break;
						case Direction::up:   putimage_b(k, j, box.getimage("up"));     break;
						case Direction::down: putimage_b(k, j, box.getimage("down"));   break;
						case Direction::left: putimage_b(k, j, box.getimage("left"));   break;
						case Direction::right:putimage_b(k, j, box.getimage("right"));  break;
						default:break;
						}break;
					case State::box:   putimage_b(k, j, box.getimage("box"));    break;
					case State::wall:  putimage_b(k, j, box.getimage("wall"));   break;
					case State::pexit: putimage_b(k, j, box.getimage("pexit"));  break;
					case State::bexit: putimage_b(k, j, box.getimage("bexit"));  break;
					default:    break;
					}
				}
			}
		}
		//第4层 tag层
		for (int i = 0; i < block.map.size(); i++)
		{
			//完成框
			for (int j = 0; j < block.map[i].tag.size(); j++)
			{
				if (block.map[i].tag[j] == "win")
				{
					XYZ& data = block.map[i].Location;
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

