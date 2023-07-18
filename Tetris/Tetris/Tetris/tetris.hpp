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
	}z[squares], k[squares]; // z表示当前方块的坐标，k表示下一个方块的坐标

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
