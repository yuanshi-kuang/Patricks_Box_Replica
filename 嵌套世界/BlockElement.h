#pragma once
#include <vector>
#include <string>
#include "State.h"
#include "Direction.h"
#include "WXYZpro.cpp"

using namespace std;
class Tree;
class BlockElement
{
private:
    State Compatible(string code = "null");
public:
    State name = null; // 名字
    bool push = false; // 推动性
    XYZ Location = { 0, 0, 0 }; // 元素逻辑位置
    // 世界传送门id。
    // 解析block的json后为外部id。
    // 之后进行level世界链接后为内部id。
    int son = 0;
    //vector<string> tag;
    BlockElement() = default;
    BlockElement(State Element);
    BlockElement(const string Element);
    BlockElement(const State& name, const bool& push);
    ~BlockElement() = default;
    BlockElement(const BlockElement& data);
    BlockElement& operator=(const BlockElement& data);
    void load(State Element, int son = -1);
    void del();
};