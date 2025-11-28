#include <iostream>
#include <fstream>
#include <graphics.h>
#include <vector>
#include <string>
#include <filesystem>
#include "File.cpp"
using namespace std;
namespace fs = std::filesystem;
int main()
{
    //string path = ".\\levels";  // 你要遍历的文件夹路径
    //cout << "在所有子文件夹中搜索txt文件：" << endl;
    //int count = 0;
    //// recursive_directory_iterator 会递归搜索所有子文件夹
    //for (const auto& entry : fs::recursive_directory_iterator(path)) 
    //{
    //    if (entry.is_regular_file() && entry.path().extension() == ".level")
    //    {
    //        count++;
    //        cout << count << ". " << entry.path() << endl;
    //    }
    //}
    //cout << "总共找到 " << count << " 个level文件" << endl;
    //return 0;
    //======================================================================================
    //string folder_path = "./levels";  // 你要搜索的文件夹
    //vector<string> txt_files;  // 用来保存所有txt文件路径
    //// 搜索并记录所有txt文件
    //for (const auto& entry : fs::recursive_directory_iterator(folder_path))
    //{
    //    if (entry.is_regular_file() && entry.path().extension() == ".level") 
    //    {
    //        // 把完整路径保存到向量中
    //        txt_files.push_back(entry.path().generic_string());
    //    }
    //}
    //// 打印找到的所有文件路径
    //cout << "找到的level文件路径：" << endl;
    //for (const auto& file_path : txt_files) 
    //{
    //    cout << file_path << endl;
    //}
    //// 以后想使用这些路径，直接访问 txt_files 向量即可
    //cout << "\n以后可以这样使用：" << endl;
    //for (int i = 0; i < txt_files.size(); i++)
    //{
    //    cout << "文件" << i + 1 << ": " << txt_files[i] << endl;
    //}

    return 0;
}

