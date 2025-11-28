#pragma once
#include <graphics.h>
#include <vector>
#include <string>
#pragma comment(lib,"MSIMG32.LIB")
using namespace std;
class IMAGES
{
public:
	vector<IMAGE> image;
	vector<string> name;
	IMAGES()
	{
		image = vector<IMAGE>(0);
		name = vector<string>(0);
	}
	bool addimage(const wstring& code, const string& names)
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
	IMAGE* getimage(const string& names)
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
};
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


