#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h"
#include <string>

const int WINDOW_WIDTH = 938;
const int WINDOW_HEIGHT = 896;

class Game {
public:
	/*	负责人：组长
		构造函数，设置地图的行数和列数，设置左边距和上边距(即方块初始位置距离窗口左边和顶部的距离)，设置块大小
	*/
	Game(int rows, int cols, int leftDistance, int upDistance, int blockSize);


	/*负责人：淼
	功能：初始化参数（countTime，delay，score，level，isOver等）
		设计随机数种子，初始化窗口
		读取背景图片赋予backImg
		读取各模式最高分，赋予highestScore[]
	参数：无
	返回值： void
	*/
	void init();

	/*
	* 负责人：组长
	* 功能：经典模式下的运行函数，供play()函数调用
*	init();
	nextBlock = new Block;//生成下一个方块
	curBlock = nextBlock;//赋值给当前方块
	nextBlock = new Block;//再次生成下一个方块
	while (true) {
		//if(musicFlag){
			播放音乐
		}
		//接受用户输入，根据输入进行平移，旋转和加速
		keyEvent();
		//获取时间
		countTime += getDelay();
		//将更新标志位改为true，调用方块下落函数
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		//如果更新标志位update位true
		if (update) {
			update = false;
			//渲染画面
			updateWindow();
			//清除一行判断，增加得分
			clearLine();
		}
		//isOver代表游戏是否结束
		if (isOver) {
			isOver = false;
			//游戏结束后，根据当前分数更新历史最高分
			updateHighestScore(score);
			//展示游戏结束画面
			disPlayOver();
			//再次接受用户键盘消息，选择重新开始回到主界面，选择结束游戏 exit(0)
			overKeyEvent();
		}
		//level代表不同大小的delay，5代表最低延时
		if (level > 5) {
			//展示游戏胜利画面
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void classicMode();


	/*负责人：cs
	* 功能，隐身模式下的入口函数，供play调用
	* init();
	nextBlock = new Block;//生成下一个方块
	curBlock = nextBlock;//赋值给当前方块
	nextBlock = new Block;//再次生成下一个方块
	* while (true) {
	*	//if(musicFlag){
			播放音乐
		}
		//接受用户输入，根据输入进行平移，旋转和加速
		keyEvent();
		//获取时间
		countTime += getDelay();
		//将更新标志位改为true，调用方块下落函数
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		//如果更新标志位update位true
		if (update) {
			update = false;
			//渲染画面
			updateWindowForStealth();
			//清除一行判断，增加得分
			clearLine();
		}
		//isOver代表游戏是否结束
		if (isOver) {
			isOver = false;
			//游戏结束后，根据当前分数更新历史最高分
			updateHighestScore(score);
			//展示游戏结束画面
			disPlayOver();
			//再次接受用户键盘消息，选择重新开始回到主界面，选择结束游戏 exit(0)
			overKeyEvent();
		}
		//level代表不同大小的delay，5代表最低延时
		if (level > 5) {
			//展示游戏胜利画面
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void stealthMode();

	/*负责人：cs
	* 功能：反转模式下的入口函数，供play调用
	* init();
		nextBlock = new Block（）;//生成下一个方块
		curBlock = nextBlock;//赋值给当前方块
		nextBlock = new Block（）;//再次生成下一个方块
		while (true) {
		//if(musicFlag){
			播放音乐
		}
		//接受用户输入，根据输入进行平移，旋转和加速
		reverseKeyEvent();
		//获取时间
		countTime += getDelay();
		//将更新标志位改为true，调用方块下落函数
		if (countTime > delay) {
			update = true;
			dropForReverse();//调用反转模式下的下落函数
			countTime = 0;
		}
		//如果更新标志位update位true
		if (update) {
			update = false;
			//渲染画面
			updateWindow();
			//清除一行判断，增加得分
			clearLineForReverse();
		}
		//isOver代表游戏是否结束
		if (isOver) {
			isOver = false;
			//游戏结束后，根据当前分数更新历史最高分
			updateHighestScore(score);
			//展示游戏结束画面
			disPlayOver();
			//再次接受用户键盘消息，选择重新开始回到主界面，选择结束游戏 exit(0)
			overKeyEvent();
		}
		//level代表不同大小的delay，5代表最低延时
		if (level > 5) {
			//展示游戏胜利画面
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void reverseMode();

	/*
	* 尚未完善，暂时不写
	* 功能：大方块模式下的入口函数，供play调用
	* init();
		nextBlock = new Block（）;//生成下一个方块，调用大方块模式下的构造函数
		curBlock = nextBlock;//赋值给当前方块
		nextBlock = new Block（）;//再次生成下一个方块，调用大方块模式下的构造函数
		while (true) {
		//if(musicFlag){
			播放音乐
		}
		//接受用户输入，根据输入进行平移，旋转和加速
		keyEvent();
		//获取时间
		countTime += getDelay();
		//将更新标志位改为true，调用方块下落函数
		if (countTime > delay) {
			update = true;
			drop();//调用经典模式下的下落函数
			countTime = 0;
		}
		//如果更新标志位update位true
		if (update) {
			update = false;
			//渲染画面
			updateWindow();
			//清除一行判断，增加得分
			clearLine();
		}
		//isOver代表游戏是否结束
		if (isOver) {
			isOver = false;
			//游戏结束后，根据当前分数更新历史最高分
			updateHighestScore(score);
			//展示游戏结束画面
			disPlayOver();
			//再次接受用户键盘消息，选择重新开始回到主界面，选择结束游戏 exit(0)
			overKeyEvent();
		}
		//level代表不同大小的delay，5代表最低延时
		if (level > 5) {
			//展示游戏胜利画面
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	//void bigBlockMode();

	/*负责人：cs
		功能：入口函数
		while{true}{
				展示主界面，等待用户选择（经典模式，挑战模式，游戏设置，退出游戏）
				选择退出游戏：exit(0)
				选择游戏设置：
					展示游戏设置界面：
						展示规则介绍
						小组介绍
						展示不同背景按钮，根据用户点击切换backImg的值
						展示是否播放音乐按钮，根据用户点击切换musicFlag标志位的值，true表示播放，fasle表示不播放
						展示清除历史记录选项：点击后调用clearHistory()
						展示返回按钮：点击后重新回到主界面,contiue;
				选择经典模式
					void classicMode();
				选择挑战模式：
					展示挑战模式界面，（隐身、反转）
					根据选择进入对应模式
						隐身：只渲染第一个下落的方块过一定时间之后去除。右侧需要渲染下一个方块。地图的渲染取消。其余逻辑与经典模式应该基本一致
							void stealthMode();
						反转：修改方块的初始生成位置和渲染位置和下落逻辑以及得分和失败的判定
							void reverseMode();
						大方块：使用biGposition作为方块数据
							void bigBlockMode();
		}

	*/
	void play();

	/*
	* 负责人：颂衡
	* 功能：与keyevent相反，按上为加速，按下为变形
	*/
	void reverseKeyEvent();
private:
	/*负责人：cs
	功能：根据程序自启动以来的时间（ms）控制延时
	参数：无
	返回值：得到countTime的值
	*/
	int getDelay();

	/*负责人：淼
	功能：获取键盘消息输入，←→代表横移，↑代表旋转，↓代表加速。根据消息调用对应的旋转函数rotate()，平移函数moveLeftOrRight(int dx)
		  加速键就降低delay的值。
	*/
	void keyEvent();

	/*负责人：柚子
	功能：重新绘制界面，包括绘制背景图片，当前方块的绘制，下一个方块的绘制，游戏分数，游戏当前等级，游戏最高分的绘制。
		还有已经固化方块的绘制
	*/
	void updateWindow();

	/*负责人：柚子
	* 功能：渲染隐身模式下的界面，只要渲染第一个方块，下落一定时间后去除。右侧渲染下一个方块，地图渲染取消。
	*/
	void updateWindowForStealth();

	/*负责人：副组长
	功能：实现方块的下落以及方块生成时游戏是否结束标志位的更新
		实现案例：
		//首先保存当前方块的位置
		preBlock = *curBlock;
		//调用方块本身的下落函数
		curBlock->drop();
		//检查下落后的方块位置是否合法
		if (!curBlock->checkPositionIsValid(map)) {
			//不合法，方块固化到地图上
			preBlock.solidy(map);
			//删除当前方块
			delete curBlock;
			//将下一个方块赋值给当前方块
			curBlock = nextBlock;
			//生成下一个方块
			nextBlock = new Block;
			//生成下一个方块时，立刻进行位置合法判断，若不合格，则说明游戏结束
			if (!curBlock->checkPositionIsValid(map)) {
				isOver = true;
			}
		}
		//按下下加速键之后，延时变短，为了防止方块一直加速，这里需要换回原本的延时
		delay = SPEED_NORMAL[level - 1];
	*/
	void drop();//下落

	/*负责人：副组长
	* 功能：实现反转模式下的下落
	*/
	void dropForReverse();


	/*
	* 负责人：组长
	功能：清除一行，计算得分，消除时添加消除音效
	*/
	void clearLine();

	/*
	* 负责人：副组长
	* 功能：反转模式下的清除一行计算得分
	*/
	void clearLineForReverse();

	/*负责人：淼
	功能：实现方块的平移（实现模式与方块下落drop()类似）
	参数：dx为偏移量，向左为-1，向右为+1
	*/
	void moveLeftOrRight(int dx);

	/*负责人：柚子
	功能：实现方块的旋转（实现模式与方块下落drop()类似）
	*/
	void rotate();//旋转

	/*
	* 负责人：宅猫
	功能：在背景图片的指定位置将当前的得分，等级，最高分等信息绘制在界面上，供updateWindow()与updateWindowForStealth()函数调用
	*/
	void drwaScore();//显示得分

	/*负责人：cs
	功能：根据本次得分与文件中保存的分数进行比较，若大于就更新文件，否则不变
	参数： 本次得分
	*/
	void updateHighestScore(int curScores);

	/*负责人：副组长
	功能：打印游戏结束界面
	*/
	void disPlayOver();

	/*
	* 负责人：颂衡
	*功能：打印游戏获胜界面
	*/
	void displaySuccess();

	/*
	* 负责人：颂衡
	* 功能：清除历史记录
	*/
	void clearHistory();

	/*
	* 游戏结束后，等待用户输入键盘数据，输入1表示重新回到主界面。输入2表示结束游戏exit(0)
	*/
	void overKeyEvent();
public:
	static std::string musicFiles[3];//存放背景音乐的文件名
private:
	int countTime;//统计时间，用于判定是否更新界面
	int delay;//延时
	bool update;//画面是否更新标志位
	std::vector<std::vector<int>> map;//地图数据
	int rows, cols, leftDistance, upDistance, blockSize;//地图的函数，列数，地图距离窗口的左距离和上距离
	IMAGE backImg;//背景图片（使用数组，因为会有多张背景图片）
	Block* nextBlock;//下一个生成的方块
	Block* curBlock;//当前方块
	Block preBlock;//临时方块，用于返回方块上一种状态
	int score;//当前分数
	int countOfLines;//当前已经消除多少行
	int level;//当前处于第几关
	int highestScore[3];//当前最高分（考虑使用数组，因为有多种模式）
	bool isOver;//游戏是否结束标志位
	bool musicFlag;//是否播放音乐标志位
	int curMode;//当前处于什么游戏模式，0代表经典，1代表隐身，2代表反转
	bool isPaused;//游戏当前是否处于暂停状态
	int musicIndex;//音乐文件索引
	int preMusicIndex;//上一个播放的音乐
};

