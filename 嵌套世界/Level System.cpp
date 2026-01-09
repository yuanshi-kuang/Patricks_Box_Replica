#pragma once  
#include <string>
#include <memory>
#include "Level.h"

using namespace std;
//动态关卡管理
class LevelSystem
{
private:
	unique_ptr<Level> level;
public:
	LevelSystem() = default;
	LevelSystem(const LevelSystem&) = delete;
	~LevelSystem() = default;
	LevelSystem& operator=(const LevelSystem&) = delete;
	//加载关卡
	bool load(json& json)
	{
		del();
		level = make_unique<Level>();
		return level->load(json);
	}
	//渲染
	void rendering() { level->rendering(); }
	//移除当前加载的关卡
	void del() { level.reset(); }
	Level& get() { return *level; }
};




