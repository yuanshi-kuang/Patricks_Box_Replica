#pragma once  
#include "Tree.h"
Tree::Tree(const string& str) : Block(str)
{
    //节点编号
    worldnum = w;
    //初始化son
    son = vector<Tree*>(0);
    //注册户籍
    map.push_back(make_pair(w++, this));
}
Tree::~Tree()
{
    //断绝我父亲和我的关系
    if (father != nullptr) { erase(father->son, this); }
    //删除户籍
    erase_if(map, [this](const auto& pair) {return pair.first == worldnum; });
    //断绝我儿子们和我的关系
    for (auto it : son) { it->father = nullptr; }
    son.clear();
}
Tree* Tree::addtree(const string& str)
{
    Tree& Tree_data = *(new Tree());
    if (Tree_data.load(str)) { return &Tree_data; }
    else { return nullptr; }
}
Tree* Tree::findblock(int num)
{
    auto it = find_if(map.begin(), map.end(), [num](const auto& pair) {return pair.first == num; });
    if (it != map.end()) { return it->second; }
    return nullptr;
}
bool Tree::LinkFatherSon(int father, int son)
{
    //验证数据有效性
    if (son < 0 || son >= w || father < 0 || father >= w) { return false; }
    Tree* fit = findblock(father);
    Tree* sit = findblock(son);
    if (fit != nullptr && sit != nullptr)
    {
        fit->son.push_back(sit);
        sit->father = fit;
        return true;
    }
    return false;
}
bool Tree::CreateFather(int father)
{
    //验证数据有效性
    if (father < 0 || father >= w) { return false; }
    Tree* it = findblock(father);
    if (it != nullptr)
    {
        this->father = it;
        it->son.push_back(this);
        return true;
    }
    return false;
}
bool Tree::CreateSon(int son)
{
    //验证数据有效性
    if (son < 0 || son >= w) { return false; }
    Tree* it = findblock(son);
    if (it != nullptr)
    {
        this->son.push_back(it);
        it->father = this;
        return true;
    }
    return false;
}
const Tree* Tree::getfather() const { return father; }
const auto& Tree::getson() const { return son; }
int Tree::w = 0;
vector<pair<int, Tree*>> Tree::map = vector<pair<int, Tree*>>(0);