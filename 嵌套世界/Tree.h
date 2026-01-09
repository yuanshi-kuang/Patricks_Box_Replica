#pragma once
#include <algorithm>
#include "Block.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class Tree : public Block
{
private:
    static vector<pair<int, Tree*>> map; // 节点库  
    static vector<pair<int, int>> id_pair;//外部id与内部id的键值对
    static int w;
public:
    XY FatherEntrance = { -1,-1 };//父节点入口
    Tree* father = nullptr; // 父节点  
    vector<Tree*> son; // 子节点  
    int worldnum = 0;
    Tree();
    Tree(const json& str);
    ~Tree();
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    static int getmapsize();
    static Tree* addtree(const json& jsontree);
    //将外部id转为内部id
    static int pairid(int id);
    //内部id
    static Tree* findblock(int num);
    static bool LinkFatherSon(int father, int son);
    bool CreateFather(int father);
    bool CreateSon(int son);
};
