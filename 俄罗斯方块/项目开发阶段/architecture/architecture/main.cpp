#include "Game.h"
#include "Gif.h"
#include <iostream>
/*
������ƣ�
	��Ҫ����Ϊ���֣���ͼ�ͷ���
		1����ͼ���ݣ�map����������Game�У���һ��vector<vector<int>>�������ɣ�map[i][j]==0
		��ʾ��ǰλ���޷��飬map[i][j]==��1-7���ֱ��Ӧ���ַ���
		2���������ݣ���������Block�У�block����ÿһ�д���һ����״�ķ���
		int blocks[7][4] = {
			1,3,5,7, //I
			2,4,5,7, //Z
			3,5,4,6, //Z
			3,5,4,7, //T
			2,3,5,7, //L
			3,5,7,6, //j
			2,3,4,5, //��
		};
		һ��position����һ��С���飬row��col�������ʼʱ��λ������
		struct Position {
			int row, col;
		};
		ÿ���������ĸ�С������ɣ�����Ҫһ��Position[4]����洢

*/



int main() {
	initgraph(938, 896);
	Game game(20, 10, 263, 133, 36);
	game.play();
	cleardevice();
	return 0;
}