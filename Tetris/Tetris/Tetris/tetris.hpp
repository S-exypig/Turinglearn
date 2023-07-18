#pragma once
#ifndef TETRIS_HPP
#define TETRIS_HPP
/*
	����һ������˹����С��Ϸ
*/
#include<SFML/Graphics.hpp>
#include<memory>
#include<vector>

class Tetris
{
	static const std::uint32_t lines{20}; // 20��
	static const std::uint32_t cols{10}; // 10��
	static const std::uint32_t squares{4}; // ÿ������4��С������
	static const std::uint32_t shapes{7}; // 7����״
	
	std::vector<std::vector<std::uint32_t>> area; // ��ʾ����ÿ��λ���Ƿ�ռ��
	std::vector<std::vector<std::uint32_t>> forms; // 7����״��4����ת״̬

	struct Coords{
		std::uint32_t x, y;
	}z[squares], k[squares]; // z��ʾ��ǰ��������꣬k��ʾ��һ�����������

	std::shared_ptr<sf::RenderWindow> window; // ��Ϸ����
	sf::Texture tiles, bg; // ����������������
	std::shared_ptr<sf::Sprite> sprite,background; // ���龫�飬��������
	sf::Clock clock; // ʱ��
	sf::Font font; // ����
	sf::Text txtScore,txtGameOver; // ��������Ϸ����

	int dirx, color, score; // ������ɫ������
	bool rotate, gameover; // �Ƿ���ת����Ϸ�Ƿ����
	float timercount, delay; // ��ʱ�����ӳ�


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
