#include"service.h"

int map[19][19];
int flag;
int rounds;

void init() {
	/*
	功能: 初始化游戏数据
	将棋盘的值初始化为0
	当前回合设为黑棋(flag设为1)
	参数: void
	返回值: void
*/
	// 初始化棋盘为0
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++)
			map[i][j] = 0;
	}
	// 初始化回合数
	rounds = 1;
	// 初始化当前回合为黑棋
	flag = 1;
}


int isWin(int x, int y) {
	/*
	功能: 根据传入的坐标(map对应位置)和flag值 判断落点后是否获胜 若未获胜则交替颜色
		参数:
			x: 当前回合落子的x坐标
			y: 当前回合落子的y坐标
		返回值:
			0表示没有获胜
			1表示黑子胜利
			2表示白子胜利
*/
	int i, j;
	int count = 0; // 统计连续棋子数
	int color = map[x][y];
	// 横向
	for (i = x - 4; i <= x + 4; i++) {
		if (i < 0 || i > 18)
			continue;
		// 如果连续为同一颜色,则count++,否则重新统计count
		if (map[i][y] == color)
			count++;
		else
			count = 0;
		if (count == 5)
			return color;
	}
	// 纵向
	count = 0;
	for (j = y - 4; j <= y + 4; j++) {
		if (j < 0 || j > 18)
			continue;
		if (map[x][j] == color)
			count++;
		else
			count = 0;
		if (count == 5)
			return color;
	}
	// 左上到右下
	count = 0;
	for (i = x - 4, j = y - 4; i <= x + 4 && j <= y + 4; i++, j++) {
		if (i < 0 || i > 18 || j < 0 || j > 18)
			continue;
		if (map[i][j] == color)
			count++;
		else
			count = 0;
		if (count == 5)
			return color;
	}
	// 左下到右上
	count = 0;
	for (i = x - 4, j = y + 4; i <= x + 4 && j >= y - 4; i++, j--) {
		if (i < 0 || i > 18 || j < 0 || j > 18)
			continue;
		if (map[i][j] == color)
			count++;
		else
			count = 0;
		if (count == 5)
			return color;
	}
	flag = flag % 2 + 1;
	return 0;
}

int playerMove(int x, int y) {
	/*
	功能: 在指定位置落子
	如果map[x][y]是空地 则修改map[x][y]的值:改为相应颜色(flag对应颜色)
	否则不操作
	参数:
	x: 当前回合落子的x坐标
	y: 当前回合落子的y坐标
	返回值:
	0表示落子失败 (棋盘已经有子)
	1表示落子成功
*/

	if (map[x][y] != 0)
		return 0;
	map[x][y] = flag;
	return 1;
}