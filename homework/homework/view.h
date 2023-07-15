#pragma once
#ifndef VIEW_H
#define VIEW_H
#include"service.h"
#include<iostream>

/*
	功能: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或退出游戏
	进入游戏: 调用游戏界面函数gameView();
	进入设置: 敬请期待...
	退出游戏: 调用exit(0);
*/
void menuView();

/*
	功能: 根据map数组 打印游戏棋盘
	参数: void
	返回值: void
*/
void gameView_ShowMap();

/*
	功能: 根据flag的值 打印游戏胜利界面 用户可以按任意键回到主菜单
	参数 : void
	返回值 : void
*/
void winView();

/*
	*难点2
	功能: 游戏界面整合
	初始化游戏数据(调用函数init())
	while(1){
	打印游戏界面(调用函数gameView_ShowMap())
	接收玩家坐标输入
	落子(调用落子函数playerMove())
	(如果落子失败 重新开始循环)
	判断游戏是否胜利(调用胜利判断函数isWin())
	(如果游戏胜利 调用胜利界面函数 然后结束当前界面)
	切换玩家(修改flag值)
	}
	参数: void
	返回值: void
*/
void gameView();

#endif // !VIEW_H

