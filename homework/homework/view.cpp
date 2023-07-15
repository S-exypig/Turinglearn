#include"view.h"

void menuView() {
	/*
		功能: 展示选项, 玩家可以在这里选择进入游戏, 进入设置或退出游戏
		进入游戏: 调用游戏界面函数gameView();
		进入设置: 敬请期待...
		退出游戏: 调用exit(0);
	*/
	int choice;
	while (true)
	{
		std::cout << "请选择操作:" << std::endl;
		std::cout << "1. 进入游戏" << std::endl;
		std::cout << "2. 进入设置" << std::endl;
		std::cout << "3. 退出游戏" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			gameView();
			break;
		case 2:
			std::cout << "尽请期待..." << std::endl;
			break;
		case 3:
			std::cout << "正在退出..." << std::endl;
			std::cout << "游戏结束！" << std::endl;
			exit(0);
		default:
			std::cout<< "输入错误,请重新输入!" << std::endl;
		}
	}
}


void gameView_ShowMap() {
	/*
	功能: 根据map数组 打印游戏棋盘
	参数: void
	返回值: void
*/
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++)
			std::cout << map[i][j] << " ";
		std::cout << std::endl;
	}
}


void winView() {
	/*
	功能: 根据flag的值 打印游戏胜利界面 用户可以按任意键回到主菜单
	参数 : void
	返回值 : void
*/
	gameView_ShowMap(); // 胜利前打印最后一次棋盘
	if (flag == 1) {
		std::cout << "黑棋胜利!" << std::endl;
	}
	else {
		std::cout << "白棋胜利!" << std::endl;
	}
	std::cout << "按任意键回到主菜单..." << std::endl;
	system("pause");
	system("cls");
}


void gameView() {
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
	init();
	while (true)
	{
		std::cout << "---------------------------------" << std::endl;
		std::cout<< "第 " << rounds << " 手  "<<"当前为: "<< ((flag==1)?"黑":"白") << "棋" << std::endl;
		gameView_ShowMap();
		int x, y;
		std::cout << "请输入落子坐标(以空格分隔):" << std::endl;
		std::cin >> x >> y;
		if (x < 0 || x>18 || y < 0 || y>18) {
			std::cout << "坐标输入错误,请重新输入!" << std::endl;
			continue;
		}
		if (playerMove(x,y)) {
			std::cout << "落子成功!" << std::endl;
		}
		else {
			std::cout << "落子失败!" << std::endl;
			continue;
		}
		if (isWin(x,y)) {
			winView();
			break;
		}
		++rounds;
	}
}