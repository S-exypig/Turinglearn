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
	}z[squares], k[squares]; // z��ʾ��һ��������꣬k��ʾ��ǰ���������

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

//Tetris() - ���캯�������ڳ�ʼ�� Tetris ��Ķ����ڹ��캯���У����ʼ���������������������顢��ʱ���������Լ�����������
//
//void run() - ��Ϸ���к��������ڿ�����Ϸ���������й��̡��� run() �����У��᲻��ѭ��ִ���¼��������ơ���������Ȳ�����ֱ����Ϸ������
//
//void events() - �¼������������ڴ����û�������¼����� events() �����У������û����µļ��̰��������ݰ��������Ʒ�����ƶ�����ת�Ȳ�����
//
//void draw() - ���ƺ��������ڽ���Ϸ������Ƶ������ϡ��� draw() �����У�����Ʊ��������顢������Ԫ�أ�����������ʾ�ڴ����ϡ�
//
//void moveToDown() - �������亯�������ڿ��Ʒ�����Զ����䡣�� moveToDown() �����У�����ݼ�ʱ�����ӳ�ֵ�����Ʒ���������ٶȣ����ڷ��鵽��ײ���������������ʱ������Ӧ�Ĵ���
//
//void setRotate() - ������ת�������������÷������ת���� setRotate() �����У����ⷽ���Ƿ������ת�����ڿ�����תʱ������ת������
//
//void resetValues() - ������ֵ����������������Ϸ�������ֵ���� resetValues() �����У������÷����λ�á���ɫ����������ֵ���Ա㿪ʼ�µ���Ϸ��
//
//void changePosition() - �ı�λ�ú��������ڸı䷽���λ�á��� changePosition() �����У�����ݷ�������ı䷽���ˮƽλ�ã�������ײ���ʱ������Ӧ�Ĵ���
//
//bool maxLimit() - �߽��⺯�������ڼ�ⷽ���Ƿ�ﵽ�߽硣�� maxLimit() �����У����ⷽ���Ƿ񳬳�����Ϸ����ı߽磬��������Ӧ�Ĳ���ֵ��
//
//void setScore() - ���÷�������������������Ϸ�ķ������� setScore() �����У����������������������÷֣���������Ϸ��������ʾ�ķ�����
//
//��Щ������ͬЭ����ʵ���� Tetris ��Ϸ�ĸ��ֹ��ܣ�����������ƶ�����ת�����䣬��ײ��⣬�����������ʾ�ȡ�