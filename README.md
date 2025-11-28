# 嵌套世界推箱子 | Nested Worlds Sokoban

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Version](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

一个支持多层嵌套世界的创新推箱子游戏，突破传统二维平面的限制，在三维甚至四维空间中解谜。

> 🚧 **项目状态**: 当前版本为**架构原型阶段**，正在进行底层重构。游戏核心功能尚在开发中。

## ✨ 项目特色

### 🌍 嵌套世界系统
- **多层世界嵌套**: 支持世界中的世界，创造"套娃"式谜题
- **4D坐标系统**: 使用WXYZ坐标管理嵌套世界关系
- **动态世界切换**: 在不同世界间穿梭解谜

### 🎮 创新游戏机制
- **传统推箱子**: 保留经典推箱子的核心玩法
- **维度扩展**: 在三维空间中移动和推箱子
- **世界互动**: 不同世界间的物体可以相互影响

### 🛠 技术架构
- **现代化C++**: 使用C++17标准，确保代码质量
- **模块化设计**: 清晰的类结构和职责分离
- **JSON关卡格式**: 易于编辑和扩展的关卡系统
- **EasyX图形库**: 简洁的2D图形渲染

## 📥 下载与安装

### 系统要求
- **操作系统**: Windows 7/10/11
- **编译器**: 支持C++17的编译器 (推荐Visual Studio 2019+)
- **依赖库**: EasyX图形库

### 快速开始
1. **下载最新版本**
   ```bash
   git clone https://github.com/yuanshi-kuang/Patricks_Box_Replica.git
   cd Patricks_Box_Replica
2. **配置开发环境**
   - 安装Visual Studio 2019或更高版本
   - 下载并安装[EasyX图形库](https://easyx.cn/)

3. **编译运行**
   - 使用Visual Studio打开项目文件
   - 编译并运行程序

## 🎯 游戏玩法

### 基本操作
- **方向键**: 控制角色移动
- **推箱子**: 将箱子推到指定位置
- **世界切换**: 在不同嵌套世界间穿梭 (开发中)

### 游戏元素
- 🧍 **玩家**: 你在游戏中的角色
- 📦 **箱子**: 需要推动的物体
- 🎯 **目标点**: 箱子需要到达的位置
- 🧱 **墙壁**: 不可穿越的障碍物
- 🌐 **世界入口**: 通往其他世界的通道
