#include "IMAGES.h"
bool IMAGES::addimage(const wstring& code, const string& names)
{
	IMAGE data;
	loadimage(&data, code.c_str());
	if (data.getheight() == 0 && data.getwidth() == 0) 
	{
		return false; 
	}
	image.resize(image.size() + 1);
	image.back() = data;
	name.push_back(names);
	return true;
}
IMAGE* IMAGES::getimage(const string& names)
{
	for (int i = 0; i < name.size(); i++) 
	{
		if (name[i] == names) 
		{
			return &image[i]; 
		}
	}
	return nullptr;
};
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
	box.addimage(L"png/����.png"    , "flor" );
	box.addimage(L"png/����.png"    , "box"  );
	box.addimage(L"png/ǽ.png"      , "wall" );
	box.addimage(L"png/����յ�.png", "pexit");
	box.addimage(L"png/�����յ�.png", "bexit");
	box.addimage(L"png/С��/��0.png", "up"   );
	box.addimage(L"png/С��/��0.png", "down" );
	box.addimage(L"png/С��/��0.png", "left" );
	box.addimage(L"png/С��/��0.png", "right");
	BeginBatchDraw();
	while (running)
	{
		//��ʼ��ʱ
		DWORD start_time = GetTickCount();
		//ʤ�����//TopMessageBox(NULL, L"��ʾ", L"��ϲ���أ�", MB_OK);
		if (level.victory) { TopMessage(L"��ʾ", L"��ϲ���أ�"); return; }
		//��ֵ����
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
		//���
		cleardevice();
		//��Ⱦ
		for (int i = 0; i < block.mapsize.z; i++)
		{
			for (int j = 0; j < block.mapsize.y; j++)
			{
				for (int k = 0; k < block.mapsize.x; k++)
				{
					switch (block.maps(i, j, k)->name)
					{
					case State::null:  break;
					case State::flor:  putimage_b(k, j, box.getimage("flor"));   break;
					case State::player:
						switch (level.direction)
						{
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
		//�ύ
		FlushBatchDraw();
		//�ȴ�
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60) { Sleep(1000 / 60 - delta_time); }
	}
	EndBatchDraw();
};

