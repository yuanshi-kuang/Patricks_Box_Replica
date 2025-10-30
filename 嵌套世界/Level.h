#pragma once  
#include <graphics.h>  
#include <vector>  
#include <string>  
#include "Direction.cpp"  
#include "Block.h"  
#include "WXYZpro.cpp"  
#include "Animation.cpp" // Ensure the correct header file for Animation is included  
#include "IMAGES.cpp"  
#include "Tree.cpp"
using namespace std;  

class Level  
{  
public:  
	Tree tier;//层级关系
    WXYZ pats = { 0,0,0,0 }; // 玩家所在位置的4维编号  
    Direction direction = Direction::done0; // 玩家方向  
    vector<Animation> anim; // 动画列表  
    WXYZ pexitend = { -1,0,0,0 }; // 玩家终点  
    vector<WXYZ> bexitend; // 箱子终点  
    bool victory = false; // 胜利  
    bool havep = false; // 有玩家  
    Level();  
    bool move(const int& x, const int& y, const Direction& dir);  
    void addblock(const string& str);  
    void up();  
    void down();  
    void left();  
    void right();  
};  

void TopMessage(const std::wstring& title, const std::wstring& message);  
void rendering(Level& level);
