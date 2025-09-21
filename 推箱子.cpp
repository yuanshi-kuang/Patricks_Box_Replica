#include <iostream>
#include <string>
#include <vector>
#include <graphics.h>
#include <Windows.h>
#include "State.h"
#include "Direction.h"
#include "XY.h"
#include "XYZ.h"
#include "WXYZ.h"
#include "BlockElement.h"
#include "Block.h"
#include "Level.h"
#pragma comment(lib,"MSIMG32.LIB")
using namespace std;
//class Tree
//{
//public:
//	vector<Tree*> tree;
//	Tree* basetree;
//	Block* atblock;
//	Tree() { basetree = nullptr; atblock = nullptr; }
//	void addtree(Block* block)
//	{
//		tree.push_back(&Tree());
//		basetree = this;
//		atblock = block;
//	}
//};

inline void putimage_a(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_b(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	x = x * 80 + (80 - w) / 2;
	y = y * 80 + (80 - h) / 2;
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
void TopMessage(const std::wstring& title, const std::wstring& message)
{
	HANDLE hThread = CreateThread(NULL, 0, [](LPVOID param) -> DWORD
		{
			auto data = (std::pair<std::wstring, std::wstring>*)param;
			MessageBoxW(NULL, data->second.c_str(), data->first.c_str(),MB_OK | MB_ICONINFORMATION);
			delete data;
			return 0;
		}, new std::pair<std::wstring, std::wstring>(title, message), 0, NULL);
	Sleep(100);
	if (HWND hWnd = FindWindowW(NULL, title.c_str())){SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}
int main()
{
	//44444\n40004\n42304\n45604\n44444
	//4444444444\n4000000004\n4023560004\n400000004\n4000000004\n4000000004\n4000000004\n4000000004\n4000000004\n4444444444
	//0000000000\n0200000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000
	//试玩关//44444444\n44500044\n40303304\n46666664\n40330304\n44402444\n44444444
	vector<Level> level(1);
	level[0].addblock("44444\n40004\n42304\n45604\n44444");
	Block* block = &level[0].word[level[0].pats.w];
	initgraph(block->mapsize.x * 80, block->mapsize.y * 80);
	//initgraph(block->mapsize.x * 80, block->mapsize.y * 80, EX_SHOWCONSOLE);
	bool running = true;
	int tick = 0;
	ExMessage msg;
	IMAGE flor_, box_, wall_, pexit_, bexit_, up_, down_, right_, left_;
	loadimage(&flor_, _T("png/背景.png")    );
	loadimage(&box_,  _T("png/箱子.png")    );
	loadimage(&wall_, _T("png/墙.png")      );
	loadimage(&pexit_,_T("png/玩家终点.png"));
	loadimage(&bexit_,_T("png/箱子终点.png"));
	loadimage(&up_,   _T("png/小人/上0.png"));
	loadimage(&down_, _T("png/小人/下0.png"));
	loadimage(&left_, _T("png/小人/左0.png"));
	loadimage(&right_,_T("png/小人/右0.png"));
	BeginBatchDraw();
	while(running)
	{	
		//开始计时
		DWORD start_time = GetTickCount();
		//胜利检测//TopMessageBox(NULL, L"恭喜过关！", L"提示", MB_OK);
		if (level[0].victory) { TopMessage(L"提示", L"恭喜过关！"); return 0; }
		//数值更换
		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_UP:   level[0].up();    break;
				case VK_DOWN: level[0].down();  break;
				case VK_LEFT: level[0].left();  break;
				case VK_RIGHT:level[0].right(); break;
				default:break;
				}
			}
		}
		//清空
		cleardevice();
		//渲染
		for (int i = 0; i < block->mapsize.z; i++)
		{
			for (int j = 0; j < block->mapsize.y; j++)
			{
				for (int k = 0; k < block->mapsize.x; k++)
				{
					switch (block->maps(i, j, k)->name)
					{
					case null:  break;
					case flor:  putimage_b(k, j, &flor_);   break;
					case player:
						switch (level[0].direction)
						{
						case Direction::up:   putimage_b(k, j, &up_);     break;
						case Direction::down: putimage_b(k, j, &down_);   break;
						case Direction::left: putimage_b(k, j, &left_);   break;
						case Direction::right:putimage_b(k, j, &right_);  break;
						default:break;
						}break;
					case box:   putimage_b(k, j, &box_);    break;
					case wall:  putimage_b(k, j, &wall_);   break;
					case pexit: putimage_b(k, j, &pexit_);  break;
					case bexit: putimage_b(k, j, &bexit_);  break;
					default:    break;
					}
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
	closegraph();
	EndBatchDraw();
	return 0;
}
