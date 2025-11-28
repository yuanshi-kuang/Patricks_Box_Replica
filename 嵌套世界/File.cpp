#pragma once  
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "Triple.cpp"
#include "json.hpp"
#include "Level.h"
namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;
//文件状态
enum Check
{
	//文件不存在
	FileNotFound,
	//文件是空的
	FileEmpty,
	//缺少必要元素
	MissingElements,
	//必要元素中存在空元素
	EmptyElements, 
	//必要元素中存在类型错误
	TypeMismatch,
	//标注地图大小和实际地图大小不同
	SizeMismatch,
	//地图尺寸错误或枚举元素错误
	NumericalError,
	//解析错误
	ParseError,
	//未检测
	NotChecked, 
	//文件完整
	FileComplete,
	//内容合格
	LevelComplete
};
class File
{
private:
	//基础路径
	const string path = "./levels";
	bool findelement(vector<string> code, json& jsondata )
	{
		for (auto& data : code)
		{
			if (!jsondata.contains(data)) { return false; }
		}
		return true;
	}
	bool findnum(vector<int> wordnum, int number)
	{
		for (auto& num : wordnum)
		{
			if (num == number) { return true; }
		}
		return false;
	}
	bool check_contains(Triple<string, json, Check>& file)
	{
		if (!findelement({ "id","name","word" }, file.two)) {return false; }
		for (auto& word : file.two["word"])
		{
			if (!findelement({ "id","size","map" }, word)) { return false; }
			else if (!findelement({ "x","y","z" }, word["size"])) { return false; }
		}
		if (file.two.contains("link"))
		{
			if (file.two["link"].empty()) { return false; }
			for (auto& link : file.two["link"])
			{
				if (!findelement({ "father","son" }, link)) { return false; }
			}
		}
		return true;
	}
	bool check_empty(Triple<string, json, Check>& file)
	{
		if (file.two["id"].empty() ||
			file.two["name"].empty() ||
			file.two["word"].empty())
		{ return false; }
		for (auto& word : file.two["word"])
		{
			if (word["id"].empty() || 
				word["size"].empty() ||
				word["map"].empty() ||
				word["size"]["x"].empty() ||
				word["size"]["y"].empty() ||
				word["size"]["z"].empty())
			{ return false;}
			for (auto& y : word["map"])
			{
				for (auto& x : y)
				{
					if (x.empty()) { return false; }
				}
			}
		}
		if (file.two.contains("link"))
		{
			if (file.two["link"].empty()) { return false; }
			for (auto& link : file.two["link"])
			{
				if (link["father"].empty() || link["son"].empty()) { return false; }
			}
		}
		return true;
	}
	bool check_type(Triple<string, json, Check>& file)
	{
		if (!file.two["id"].is_number() ||
			!file.two["name"].is_string() || 
			!file.two["word"].is_array()) 
		{ return false; }
		for (auto& word : file.two["word"])
		{
			if (!word["id"].is_number() || 
				!word["size"].is_object() || 
				!word["map"].is_array() || 
				!word["size"]["x"].is_number() || 
				!word["size"]["y"].is_number() || 
				!word["size"]["z"].is_number()) 
			{ return false; }
			for (auto& y : word["map"])
			{
				for (auto& x : y)
				{
					if (!x.is_string()) { return false; }
				}
			}
		}
		if (file.two.contains("link"))
		{
			if (!file.two["link"].is_array()) { return false; }
			for (auto& link : file.two["link"])
			{
				if (!link["father"].is_number() || !link["son"].is_number()) { return false; }
			}
		}
		return true;
	}
	bool check_num(Triple<string, json, Check>& file)
	{
		vector<int> wordnum;
		for (auto& word : file.two["word"])
		{
			wordnum.push_back(word["id"]);
			if (word["size"]["x"] <= 0 ||
				word["size"]["y"] <= 0 ||
				word["size"]["z"] <= 0 || 
				word["size"]["x"] > 100 ||
				word["size"]["y"] > 100 ||
				word["size"]["z"] > 100)
			{ return false; }
			if (word["map"].size() != word["size"]["y"]) { return false; }
			for (auto& y : word["map"])
			{
				if (y.size() != word["size"]["x"]) { return false; }
				for (auto& x : y)
				{
					if (x != "null" &&
						x != "flor" &&
						x != "player" &&
						x != "box" &&
						x != "wall" &&
						x != "pexit" &&
						x != "bexit")
					{ return false; }
				}
			}
		}
		if (file.two.contains("link"))
		{
			for (auto& link : file.two["link"])
			{
				if(!findnum(wordnum,link["father"])){ return false; }
				else if(!findnum(wordnum, link["son"])){ return false; }
			}
		}
		return true;
	}
public:
	vector<Triple<string, json, Check>> map;
	File() :map(0) {}
	File(const string& code) :path(code), map(0) {}
	File(const File&) = delete;
	~File() = default;
	File& operator=(const File&) = delete;
	//获取(刷新) 文件夹 及 所有子文件夹 下的 所有关卡文件
	void refresh_all_level()
	{
		//遍历目录(包括子文件夹)
		for (const auto& file : fs::recursive_directory_iterator(File::path))
		{
			// 是普通文件，且变量-路径-扩展名为.json
			if (file.is_regular_file() && file.path().extension() == ".json") 
			{
				//将(路径,未检测)添加到map里
				map.push_back({ file.path().generic_string(), NULL, Check::NotChecked });
			}
		}
	}
	//(重新)检测map里所有文件合格性
	void check_all_file()
	{
		for (auto& filepair : map)
		{
			ifstream file(filepair.one);
			if (!file.is_open())
			{
				filepair.three = FileNotFound; 
				continue;
			}
			file.seekg(0, ios::end);
			int file_size = file.tellg();
			file.seekg(0, ios::beg);  
			if (file_size == 0)
			{
				filepair.three = Check::FileEmpty;
				file.close();
				continue;
			}
			file.close();
			filepair.three = FileComplete;
		}
	}
	//(重新)检测map里所有文件的内容合格性
	void check_all_level()
	{
		for (auto& file : map)
		{
			if (file.three != FileComplete) { continue; }
			try
			{
				ifstream ifile(file.one);
				file.two = json::parse(ifile);
				ifile.close();

				if (!check_contains(file)) { file.three = MissingElements; continue; }
				if (!check_empty(file)) { file.three = Check::EmptyElements; continue; }
				if (!check_type(file)) { file.three = TypeMismatch; continue; }
				if (!check_num(file)) { file.three = NumericalError; continue; }
				file.three = LevelComplete;
			}
			catch (const json::parse_error& e) { file.three = ParseError; }
			catch (const exception& e) { file.three = TypeMismatch; }
		}
	}
	//整合所有检测的一键式检测函数
	void checkall()
	{
		check_all_file();
		check_all_level();
	}
};





