#pragma once
#include <algorithm>
#include "Block.h"
using namespace std;
class Tree : public Block
{
private:
    static vector<pair<int, Tree*>> map; // 节点库  //map[0].first 
    Tree* father = nullptr; // 父节点  
    vector<Tree*> son; // 子节点  
    static int w;
public:
    int worldnum = 0;
    Tree(const string& str = "");
    ~Tree();
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    static Tree* addtree(const string& str = "");
    static Tree* findblock(int num);
    static bool LinkFatherSon(int father, int son);
    bool CreateFather(int father);
    bool CreateSon(int son);
    const Tree* getfather() const;
    const auto& getson() const;
};
