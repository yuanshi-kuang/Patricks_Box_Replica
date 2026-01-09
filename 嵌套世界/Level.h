#pragma once  
#include <graphics.h>  
#include <vector>  
#include <string>  
#include <fstream>
#include <stack>
#include "Direction.h"  
#include "Block.h"  
#include "WXYZpro.cpp"  
#include "Animation.cpp" 
#include "IMAGES.cpp"  
#include "Tree.h"
#include "TopMessage.cpp"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;  
//关卡
class Level  
{  
private:
    const int maxwindowsize = 400;
    const json i= 
    {
        {"id", -1},
        {"size",
            {
                {"x", 5},
                {"y", 5},
                {"z", 3}
            }
        },
        {"map",
            {
                {
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" }
                },
                {
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" }
                },
                {
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" },
                    { "null", "null", "null", "null", "null" }
                }
            }
        }
    };;
    IMAGES box;
    void loadimage();
    void renderblock(Tree& block, const pair<float, float>, const pair<float, float>);
    bool checkwin();
    //在当前世界否？
    bool BoundaryCheck(XY eye, XY mapsize);
    bool move(const int& x, const int& y, const Direction dir);
    pair<Tree*, BlockElement*> GetNext(const Direction direction, const WXYZ& wxyz);
    pair<Tree*, BlockElement*> GetWordEntrance(const Direction direction, Tree& tree);

public:  
	Tree tier;//层级关系
    WXYZ pats = { 0,0,0,0 }; // 玩家所在位置的4维编号  
    Direction direction = Direction::done0; // 玩家方向  
    WXYZ pexitend = { -1,0,0,0 }; // 玩家终点  
    vector<WXYZ> bexitend; // 箱子终点    
    bool havep = false; // 有玩家  
    Level();  
    Level(json& jsonlevel);
    ~Level();
    void up();
    void down();
    void left();
    void right();
    bool addblock(const json& jsonlevel);
    bool load(json& jsonlevel);
    void rendering();
};  

