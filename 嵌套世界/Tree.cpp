#pragma once  
#include "Tree.h"
Tree::Tree() = default;
Tree::Tree(const json& jsontree) : Block(jsontree)
{
    //节点编号
    worldnum = w;
    //初始化son
    son = vector<Tree*>(0);
    //注册户籍
    map.push_back(make_pair(w, this));
    id_pair.push_back(make_pair(jsontree["id"], w++));
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
int Tree::getmapsize()
{
    return (int)map.size();
}
Tree* Tree::addtree(const json& jsontree)
{
    return new Tree(jsontree);
}
int Tree::pairid(int id)
{
    for (auto& data : id_pair)
    {
        if (data.second == id) { return data.first; }
    }
    return -1;
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
    if (fit == nullptr || sit == nullptr) { return false; }
    for (auto& fdata : fit->Block::map)
    {
        if (fdata.son == sit->worldnum) { sit->FatherEntrance = { fdata.Location.x,fdata.Location.y }; }
    }
    fit->son.push_back(sit);
    sit->father = fit;
    return true;
}
bool Tree::CreateFather(int father)
{
    //验证数据有效性
    if (father < 0 || father >= w) { return false; }
    Tree* fit = findblock(father);
    if (fit == nullptr) { return false; }
    for (auto& fdata : fit->Block::map)
    {
        if (fdata.son == worldnum) { FatherEntrance = { fdata.Location.x,fdata.Location.y }; }
    }
    this->father = fit;
    fit->son.push_back(this);
    return true;
}
bool Tree::CreateSon(int son)
{
    //验证数据有效性
    if (son < 0 || son >= w) { return false; }
    Tree* sit = findblock(son);
    if (sit == nullptr) { return false; }
    for (auto& sdata : this->Block::map)
    {
        if (worldnum == sdata.son) { sit->FatherEntrance = { sdata.Location.x,sdata.Location.y }; }
    }
    this->son.push_back(sit);
    sit->father = this;
    return true;
}
int Tree::w = 0;
vector<pair<int, Tree*>> Tree::map = vector<pair<int, Tree*>>(0);
vector<pair<int, int>> Tree::id_pair = vector<pair<int, int>>(0);