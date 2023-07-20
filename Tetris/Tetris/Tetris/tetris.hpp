#pragma once
#ifndef TETRIS_HPP
#define TETRIS_HPP
/*
	制作一个俄罗斯方块小游戏
*/
#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>

class Tetris
{
	static const std::uint32_t lines{20}; // 20行
	static const std::uint32_t cols{10}; // 10列
	static const std::uint32_t squares{4}; // 每个方块4个小正方形
	static const std::uint32_t shapes{7}; // 7种形状
	
	std::vector<std::vector<std::uint32_t>> area; // 表示棋盘每个位置是否被占用
	std::vector<std::vector<std::uint32_t>> forms; // 7种形状的4种旋转状态

	struct Coords{
		std::uint32_t x, y;
	}z[squares], k[squares]; // z表示下一方块的坐标，k表示当前方块的坐标

	std::shared_ptr<sf::RenderWindow> window; // 游戏窗口
	sf::Texture tiles, bg; // 方块纹理，背景纹理
	std::shared_ptr<sf::Sprite> sprite,background; // 方块精灵，背景精灵
	sf::Clock clock; // 时钟
	sf::Font font; // 字体
	sf::Text txtScore,txtGameOver; // 分数，游戏结束

	int dirx, color, score; // 方向，颜色，分数
	bool rotate, gameover; // 是否旋转，游戏是否结束
	float timercount, delay; // 计时器，延迟


public:
	Tetris();
	void run();

private:
	void events();
	void draw();
	void moveToDown();
	void setRotate();
	void resetValues();
	void changePosition();
	bool maxLimit();
	void setScore();
};


#endif // !TETRIS_HPP

//Tetris() - 构造函数，用于初始化 Tetris 类的对象。在构造函数中，会初始化方块纹理、背景纹理、精灵、计时器、字体以及其他变量。
//
//void run() - 游戏运行函数，用于控制游戏的整个运行过程。在 run() 函数中，会不断循环执行事件处理、绘制、方块下落等操作，直到游戏结束。
//
//void events() - 事件处理函数，用于处理用户输入的事件。在 events() 函数中，会检测用户按下的键盘按键，根据按键来控制方块的移动、旋转等操作。
//
//void draw() - 绘制函数，用于将游戏界面绘制到窗口上。在 draw() 函数中，会绘制背景、方块、分数等元素，并将它们显示在窗口上。
//
//void moveToDown() - 方块下落函数，用于控制方块的自动下落。在 moveToDown() 函数中，会根据计时器和延迟值来控制方块的下落速度，并在方块到达底部或碰到其他方块时进行相应的处理。
//
//void setRotate() - 设置旋转函数，用于设置方块的旋转。在 setRotate() 函数中，会检测方块是否可以旋转，并在可以旋转时进行旋转操作。
//
//void resetValues() - 重置数值函数，用于重置游戏的相关数值。在 resetValues() 函数中，会重置方块的位置、颜色、分数等数值，以便开始新的游戏。
//
//void changePosition() - 改变位置函数，用于改变方块的位置。在 changePosition() 函数中，会根据方向键来改变方块的水平位置，并在碰撞检测时进行相应的处理。
//
//bool maxLimit() - 边界检测函数，用于检测方块是否达到边界。在 maxLimit() 函数中，会检测方块是否超出了游戏界面的边界，并返回相应的布尔值。
//
//void setScore() - 设置分数函数，用于设置游戏的分数。在 setScore() 函数中，会根据消除的行数来计算得分，并更新游戏界面上显示的分数。
//
//这些函数共同协作，实现了 Tetris 游戏的各种功能，包括方块的移动、旋转、下落，碰撞检测，分数计算和显示等。