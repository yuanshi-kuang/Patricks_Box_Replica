#include <iostream>
#include <string>
#include <vector>
#include <graphics.h>
#include <Windows.h>
#include "State.h"
#include "Direction.h"
#include "XY.h"
#include "XYZ.h"
#include "WXYZ.h"
#include "BlockElement.h"
#include "Block.h"
#include "Level.h"
#include "IMAGES.h"
using namespace std;
//class Tree
//{
//public:
//	vector<Tree*> tree;
//	Tree* basetree;
//	Block* atblock;
//	Tree() { basetree = nullptr; atblock = nullptr; }
//	void addtree(Block* block)
//	{
//		tree.push_back(&Tree());
//		basetree = this;
//		atblock = block;
//	}
//};


int main()
{
	//44444\n40004\n42304\n45604\n44444
	//4444444444\n4000000004\n4023560004\n400000004\n4000000004\n4000000004\n4000000004\n4000000004\n4000000004\n4444444444
	//0000000000\n0200000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000\n0000000000
	//试玩关//44444444\n44500044\n40303304\n46666664\n40330304\n44402444\n44444444
	vector<Level> level(1);
	level[0].addblock("44444\n40004\n42304\n45604\n44444");
	Block &block = level[0].word[level[0].pats.w];
	initgraph(block.mapsize.x * 80, block.mapsize.y * 80);
	//initgraph(block->mapsize.x * 80, block->mapsize.y * 80, EX_SHOWCONSOLE);
	rendering(level[0]);
	closegraph();
	return 0;
}

