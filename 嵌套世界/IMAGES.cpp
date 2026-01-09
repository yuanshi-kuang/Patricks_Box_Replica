#pragma once
#include <graphics.h>
#include <vector>
#include <string>
#include "WXYZpro.cpp"
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
inline void putimage_b(int x, int y, int zoomx, int zoomy, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	x = x * zoomx + (zoomx - w) / 2;
	y = y * zoomy + (zoomy - h) / 2;
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void putimage_c(pair<float, float> drowpoint, pair<float, float> zoom, IMAGE* img)
{
	int srcWidth = img->getwidth();
	int srcHeight = img->getheight();
	AlphaBlend(
		GetImageHDC(NULL),                                                         // 目标DC（画布）
		(int)(drowpoint.first), (int)(drowpoint.second),      // 目标位置
		(int)(zoom.first), (int)(zoom.second),               // 目标尺寸（这里设置拉伸大小）
		GetImageHDC(img),                                                          // 源图像DC
		0, 0,                                                                      // 源图像起始位置
		srcWidth, srcHeight,                                                       // 要绘制的源图像区域大小
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }                                      // 使用Alpha通道
	);
}


