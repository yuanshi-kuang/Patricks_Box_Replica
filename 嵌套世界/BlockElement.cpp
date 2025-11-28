#pragma once
#include <vector>
#include <string>
#include "State.cpp"
#include "Direction.cpp"
#include "WXYZpro.cpp"
using namespace std;
class BlockElement
{
public:
    State name = null; // 名字
    bool push = false; // 推动性
    XYZ Location = {0, 0, 0}; // 元素逻辑位置
    vector<string> tag; // 修复了类型说明符问题

    BlockElement()
    {
        tag = vector<string>(0);
    }
    BlockElement(State Element)
    {
        name = Element;
        switch (Element)
        {
        case null:
            push = true;
            break;
        case flor:
            push = false;
            break;
        case player:
            push = false;
            break;
        case box:
            push = true;
            break;
        case wall:
            push = false;
            break;
        case pexit:
            push = false;
            break;
        case bexit:
            push = false;
            break;
        default:
            break;
        }
    }
    BlockElement(const State &name, const bool &push)
        : name(name), push(push)
    {
    }
    ~BlockElement()
    {
    }
    BlockElement(const BlockElement &data)
    {
        name = data.name;
        push = data.push;
    }
    inline void del()
    {
        *this = BlockElement(null);
    }
};
