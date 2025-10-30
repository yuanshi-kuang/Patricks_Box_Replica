#pragma once  
#include "Block.h"  
#include <algorithm> 
using namespace std;  
class Tree : public Block  
{  
public:  
     Tree* father = nullptr; // 父节点  
     vector<Tree*> son; // 子节点  
     static vector<pair<int, Tree*>> map; // 节点库  //map[0].first  
     static int w;  
     int worldnum = 0;  
     Tree()
     {  
         worldnum = w;  
         son = vector<Tree*>(0);  
         map.push_back(make_pair(w++, this));  
     };  
     ~Tree()
     {  
         //断绝我父亲和我的关系
         if (father != nullptr)
         {
             erase(father->son, this);
         }
         //删除户籍
         erase_if(map, [this](const auto& pair) {return pair.first == worldnum && pair.second == this; });
         //断绝我儿子们和我的关系
         for (auto it : son)  
         {  
             it->father = nullptr;  
         }  
         son.clear();  
     }  
     Tree(const Tree&) = delete;  
     Tree& operator=(const Tree&) = delete;  
     void addtree()  
     {  

     }  
};  
int Tree::w = 0;  
vector<pair<int, Tree*>> Tree::map = vector<pair<int, Tree*>>(0);