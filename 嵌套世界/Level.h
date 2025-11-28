#pragma once  
#include <graphics.h>  
#include <vector>  
#include <string>  
#include <fstream>
#include <stack>
#include "Direction.cpp"  
#include "Block.h"  
#include "WXYZpro.cpp"  
#include "Animation.cpp" // Ensure the correct header file for Animation is included  
#include "IMAGES.cpp"  
#include "Tree.h"
#include "TopMessage.cpp"
using namespace std;  
//关卡
class Level  
{  
private:
    //拆解每个block区块
    vector<string> apart(string& code);
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
    Level(vector<string> code);
    ~Level();
    //移动
    bool move(const int& x, const int& y, const Direction& dir);  
    bool addblock(const string& str);  
    //加载关卡
    bool load(vector<string> blockbox);
    void up();  
    void down();  
    void left();  
    void right();  
};  
void rendering(Level& level);
