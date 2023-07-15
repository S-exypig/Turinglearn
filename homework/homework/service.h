#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include<iostream>

// 完成简单控制台五子棋游戏

/*
	棋盘:
	map[i][j]表示坐标(i,j)的值
	0表示空地
	1表示黑子
	2表示白子
	如: map[3][6] = 1 表示(3,6)的位置是黑子
*/
extern int map[19][19];
// 表示当前回合数 偶数表示黑棋落子 奇数表示白棋落子
// 如: flag = 20 表示当前是第[20]次落子 由黑方落子
extern int flag;
extern int rounds;
/*
	功能: 初始化游戏数据
	将棋盘的值初始化为0
	当前回合设为黑棋(flag设为0)
	参数: void
	返回值: void
*/
void init();

/*
	功能: 根据传入的坐标(map对应位置)和flag值 判断落点后是否获胜
		参数:
			x: 当前回合落子的x坐标
			y: 当前回合落子的y坐标
		返回值:
			0表示没有获胜
			1表示黑子胜利
			2表示白子胜利
*/
int isWin(int x, int y);

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
int playerMove(int x, int y);

#endif // !SERVICE_H

