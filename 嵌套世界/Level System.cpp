#pragma once  
#include <string>
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
	bool loadlevel(string& code)
	{
		deletelevel();
		level = make_unique<Level>();
		return level->load(code);
	}
	//移除当前加载的关卡
	void deletelevel() { level.reset(); }
};




