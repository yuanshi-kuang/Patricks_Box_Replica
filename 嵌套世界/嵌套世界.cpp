#include <iostream>
#include <fstream>
#include <graphics.h>
#include <vector>
#include <string>
#include <filesystem>
#include "File.cpp"
#include "Level System.cpp"
#include "Level.h"
#include <conio.h>
using namespace std;
namespace fs = std::filesystem;
void abc(Level& level)
{
    //解压玩家所在的世界
    Tree* block = Tree::findblock(level.pats.w);
    while (true)
    {

        // 使用控制台输入
        if (_kbhit())  // 检查是否有按键
        {
            int ch = _getch();
            if (ch == 224)  // 特殊键（方向键）
            {
                ch = _getch();  // 获取第二个字节
                switch (ch)
                {
                case 72:  // 上箭头
                    level.up();
                    break;
                case 80:  // 下箭头
                    level.down();
                    break;
                case 75:  // 左箭头
                    level.left();
                    break;
                case 77:  // 右箭头
                    level.right();
                    break;
                default:break;
                }
            }
            else if (ch == 27)  // ESC键退出
            {
                break;
            }
        }

        // 清屏并打印地图
        system("cls");
        block->printmapstruct();

        // 打印玩家位置信息
        cout << "玩家位置: (" << level.pats.x << ", " << level.pats.y << ", " << level.pats.z << ")" << endl;
        cout << "玩家方向: " << level.direction << endl;
        cout << "胜利状态: " << "?" << endl;
        cout << "玩家终点: " << level.pexitend.w << ", " << level.pexitend.x << ", " << level.pexitend.y << ", " << level.pexitend.z << endl;
        cout << "箱子终点数量: " << level.bexitend.size() << endl;
        cout << "箱子终点列表: " << endl;
        for (auto& data : level.bexitend)
        {
            cout << data.x << ", " << data.y << ", " << data.z << endl;
        }
        cout << endl;
        cout << "箱子符合数：";
        int boxwin = 0;
        for (const auto& data : level.bexitend)
        {
            Tree* targetBlock = Tree::findblock(data.w);
            if (targetBlock != nullptr &&
                targetBlock->maps(data.x, data.y, 2).name == box)
            {
                boxwin++;
            }
        }
        cout << (boxwin == level.bexitend.size()) << endl;
        cout <<"玩家位置：" << level.pats.w << level.pats.x << level.pats.y << level.pats.z << endl;
        //刷新渲染世界
        cout << "pats.w：" << level.pats.w << endl;
        block = Tree::findblock(level.pats.w);
       

        Sleep(50);
        //getchar();
    }
}
int main()
{
    LevelSystem ls;
    File file;
    file.refresh_all_level();
    file.checkall();
    ls.load(file.map[0].two);
    ls.rendering();
	
	//Level ll;
	//ls.rendering(&ll);

    //abc(ls.get());
	
	//Tree& block = *Tree::findblock(1);
	//auto& json = file.map[0].two["word"][0]["map"][0];
	//for (int j = 0; j < json.size(); j++)
	//{
	//	for (int k = 0; k < json[j].size(); k++)
	//	{
	//		cout << json[j][k].get<string>() << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//block.printmapstruct();
	//for (int i = 0; i < block.mapsize.z; i++)
	//{
	//	for (int j = 0; j < block.mapsize.y; j++)
	//	{
	//		for (int k = 0; k < block.mapsize.x; k++)
	//		{
	//			cout << block.maps(k, j, i).Location.x << "-"
	//				<< block.maps(k, j, i).Location.y << "-"
	//				<< block.maps(k, j, i).Location.z <<" ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
    return 0;
}


