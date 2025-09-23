#pragma once
#include <graphics.h>
#include <vector>
#include <string>
#include "Level.h"
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
	bool addimage(const wstring& code, const string& names);
	IMAGE* getimage(const string& names);
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
void TopMessage(const std::wstring& title, const std::wstring& message);
void rendering(Level& level);

