#pragma once
#include <graphics.h>
#include <vector>

/*
每个方块的四个小方块的位置坐标，见main.cpp
*/
struct Position {
	int row, col;
};
/*
	方块类
*/
class Block {
public:
	/*负责人：柚子
		功能：方块初始化，随机选择一种颜色（即形状）赋值给blockType，初始化该方块每个小方块的坐标position[4],读取该小方块对应的图像文件赋值给img
	*/
	Block();


	/*负责人：新一
	* 功能：反转模式下的方块初始化，主要改变方块的初始位置
	*/
	Block(int reverse);

	///*
	//* 功能：大方块模式下的方块初始化
	//*/
	//Block(double bigMode);

	/*负责人：佳佳
	功能：方块下落，让position中四个小方块的row坐标加一，供Game类的drop()函数调用
	*/
	void drop();

	/*负责人：佳佳
	* 功能：反转模式下的方块下落,让position中四个小方块的row坐标减一，供Game类的drop()函数调用
	*/
	void dropForReverse();

	/*负责人：佳佳
	* 功能：移动函数，根据偏移值对每个小方块中col进行改变，供Game类的moveLeftOrRight()调用
	* 参数：偏移值，由输入键盘消息确定为1或-1
	*/
	void move(int dx);

	/*负责人：佳佳
	* 功能：根据公式对方块进行旋转，供Game的roate()函数调用
	*    实现思路：
	*	Position p = position[1];
		for (int i = 0; i < 4; i++) {
			Position tmp = position[i];
			position[i].col = p.col - tmp.row + p.row;
			position[i].row = p.row + tmp.col - p.col;
		}
	*/
	void rotate();

	/*负责人：新一
		功能：将方块绘制到界面上
		参数：leftMargin为游戏地图中，方块初始位置距离窗口左边界的距离
			  topMargin为游戏地图中，方块初始位置距离窗口上边界的距离
	*/
	void draw(int leftMargin, int topMargin);

	/*
	功能：返回imgs成员
	*/
	static IMAGE** getImgs();

	/*负责人：新一
	功能：重载运算符=，用于拷贝复制blockType与position
	*/
	Block& operator=(const Block& other);

	/*负责人：宅猫
	* 功能：检查方块是否处于合法位置，合法位置指position中的四个坐标皆处于边界内，且没有map中不为0的值重合
	* 参数：传入地图数据，用于判断
	* 返回值：返回true，合法，返回false，不合法
	*/
	bool checkPositionIsValid(const std::vector<std::vector<int>>& map);

	/*负责人：宅猫
	* 功能：根据position四个小方块的坐标，将其对应的值赋值到map的对应位置
	* 参数：传入地图数据map，用于修改地图的数据
	*/
	void solidy(std::vector<std::vector<int>>& map);

	/*
	* 在隐身模式下的方块绘制
	*/
	void drawForReverse(int leftMargin, int upMargin);


private:
	//方块类型（对应7种颜色）取值为1-7
	int blockType;
	//方块的四个小方块的坐标
	Position position[4];
	//大方块模式下的8个小方块的坐标
	Position bigPosition[8];
	//方块每个小方块的图片文件，四个小方块都是同一种颜色，所以共用一个img文件即可
	IMAGE* img;
	//静态变量，所有的形状共有的7个颜色文件。例如blockType==1，则取出imgs中的第0个颜色文件赋值给img文件
	static IMAGE* imgs[7];
	//方块的渲染尺寸
	static int size;
};