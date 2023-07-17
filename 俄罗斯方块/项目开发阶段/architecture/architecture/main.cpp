#include "Game.h"
#include "Gif.h"
#include <iostream>
/*
数据设计：
	主要数据为两种：地图和方块
		1、地图数据（map）存在于类Game中，由一个vector<vector<int>>容器构成，map[i][j]==0
		表示当前位置无方块，map[i][j]==【1-7】分别对应七种方块
		2、方块数据：存在于类Block中，block数组每一行代表一种形状的方块
		int blocks[7][4] = {
			1,3,5,7, //I
			2,4,5,7, //Z
			3,5,4,6, //Z
			3,5,4,7, //T
			2,3,5,7, //L
			3,5,7,6, //j
			2,3,4,5, //田
		};
		一个position代表一个小方块，row，col代表其初始时的位置坐标
		struct Position {
			int row, col;
		};
		每个方块由四个小方块组成，故需要一个Position[4]数组存储

*/



int main() {
	initgraph(938, 896);
	Game game(20, 10, 263, 133, 36);
	game.play();
	cleardevice();
	return 0;
}