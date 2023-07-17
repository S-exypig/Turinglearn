#include "Game.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <graphics.h>
#include "Gif.h"
#include <locale>
#include <codecvt>
#include <windows.h>

#define MAX_LEVEL 5
const int SPEED_NORMAL[MAX_LEVEL] = { 500,400,300,200,100 };
const int SPEED_QUICK = 36;

GIF background("pik", 78, 938, 1145, (double)1 / 20);

std::string Game::musicFiles[3] = { "res/bg.mp3","res/bg1.mp3" ,"res/bg2.mp3" };

int MessageBoxTimeoutA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds) {
	typedef int(WINAPI* MSGBOXAAPI)(IN HWND, IN LPCSTR, IN LPCSTR, IN UINT, IN WORD, IN DWORD);
	typedef int(WINAPI* MSGBOXWAPI)(IN HWND, IN LPCWSTR, IN LPCWSTR, IN UINT, IN WORD, IN DWORD);

	MSGBOXAAPI MsgBoxTOA;
	MSGBOXWAPI MsgBoxTOW;

	HMODULE hUser32 = GetModuleHandleA("user32.dll");
	if (!hUser32)
		return 0;

	MsgBoxTOA = (MSGBOXAAPI)GetProcAddress(hUser32, "MessageBoxTimeoutA");
	MsgBoxTOW = (MSGBOXWAPI)GetProcAddress(hUser32, "MessageBoxTimeoutW");

	int retval = 0;

	if (MsgBoxTOA) {
		retval = MsgBoxTOA(hWnd, lpText, lpCaption, uType, wLanguageId, dwMilliseconds);
	}

	return retval;
}
Game::Game(int rows, int cols, int leftDistance, int upDistance, int blockSize)
	:rows(rows), cols(cols), leftDistance(leftDistance), upDistance(upDistance),
	blockSize(blockSize) {
}

void Game::init() {
	srand(static_cast<unsigned>(time(0)));
	map.clear();
	for (int i = 0; i < rows; i++) {
		std::vector<int> tempVec;
		for (int j = 0; j < cols; j++) {
			tempVec.push_back(0);
		}
		map.push_back(tempVec);
	}
	countTime = 0;
	level = 1;
	delay = SPEED_NORMAL[level - 1];
	update = false;
	loadimage(&backImg, _T("res/bg2.png"));
	score = 0;
	countOfLines = 0;
	//读取文件最高分
	std::ifstream inFile("bestScore.txt"); // 打开文件
	if (inFile.is_open()) { // 检查文件是否成功打开
		int index = 0;
		std::string numberString;
		while (std::getline(inFile, numberString)) {
			highestScore[index++] = std::stoi(numberString); // 将字符串转换为整数
		}
		inFile.close(); // 关闭文件
	}
	else {
		std::cout << "无法打开文件。\n";
	}
	isOver = false;

}

void Game::classicMode() {
	init();
	//initgraph(938, 896);
	//initgraph(1200, 700);
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;
	while (true) {
		keyEvent();
		if (isPaused) {
			TCHAR tempstr[50];          // 存储数字字符串的数组
			settextcolor(RGB(0, 174, 236));     // 设置文字颜色为蓝色
			setbkmode(TRANSPARENT); // 设置文字背景为透明
			// 设置文字样式
			LOGFONT f;
			gettextstyle(&f);       // 获取当前字体设置
			f.lfHeight = 35;        // 设置字体高度为25
			_tcscpy_s(f.lfFaceName, _T("Consolas"));    // 设置字体为 Consolas
			f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
			settextstyle(&f);       // 应用字体样式设置
			_stprintf_s(tempstr, _T("Game Paused. Press 'd' to Continue"));
			outtextxy(160, 80, tempstr);
			continue;
		}
		countTime += getDelay();
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		if (update) {
			update = false;
			updateWindow();
			clearLine();
		}
		if (isOver) {
			isOver = false;
			updateHighestScore(score);
			disPlayOver();
			overKeyEvent();
			break;
		}
		if (level > 5) {
			displaySuccess();
			system("pause");
			break;
		}
	}
}

void Game::stealthMode() {
	init();
	//initgraph(938, 896);
	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;
	DWORD lastTime = GetTickCount();
	while (true) {
		//接受用户输入
		keyEvent();
		if (isPaused) {
			TCHAR tempstr[50];          // 存储数字字符串的数组
			settextcolor(RGB(0, 174, 236));     // 设置文字颜色为蓝色
			setbkmode(TRANSPARENT); // 设置文字背景为透明
			// 设置文字样式
			LOGFONT f;
			gettextstyle(&f);       // 获取当前字体设置
			f.lfHeight = 35;        // 设置字体高度为25
			_tcscpy_s(f.lfFaceName, _T("Consolas"));    // 设置字体为 Consolas
			f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
			settextstyle(&f);       // 应用字体样式设置
			_stprintf_s(tempstr, _T("Game Paused. Press 'd' to Continue"));
			outtextxy(160, 80, tempstr);
			continue;
		}
		countTime += getDelay();
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		if (update) {
			update = false;
			updateWindowForStealth();
			clearLine();
		}
		DWORD current = GetTickCount();
		if (current - lastTime > 1000) {
			updateWindow();
			lastTime = current;
		}
		if (isOver) {
			isOver = false;
			updateHighestScore(score);
			disPlayOver();
			overKeyEvent();
			break;
		}
		if (level > 5) {
			displaySuccess();
			system("pause");
			break;
		}
	}
}

void Game::reverseMode() {
	init();
	nextBlock = new Block(1);
	curBlock = nextBlock;
	nextBlock = new Block(1);
	while (true) {
		//接受用户输入
		reverseKeyEvent();
		if (isPaused) {
			TCHAR tempstr[50];          // 存储数字字符串的数组
			settextcolor(RGB(0, 174, 236));     // 设置文字颜色为蓝色
			setbkmode(TRANSPARENT); // 设置文字背景为透明
			// 设置文字样式
			LOGFONT f;
			gettextstyle(&f);       // 获取当前字体设置
			f.lfHeight = 35;        // 设置字体高度为25
			_tcscpy_s(f.lfFaceName, _T("Consolas"));    // 设置字体为 Consolas
			f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
			settextstyle(&f);       // 应用字体样式设置
			_stprintf_s(tempstr, _T("Game Paused. Press Spacebar to Continue"));
			outtextxy(160, 80, tempstr);
			continue;
		}
		countTime += getDelay();
		if (countTime > delay) {
			update = true;
			dropForReverse();
			countTime = 0;
		}
		if (update) {
			update = false;
			updateWindow();
			clearLineForReverse();
		}
		if (isOver) {
			isOver = false;
			updateHighestScore(score);
			disPlayOver();
			overKeyEvent();
			break;
		}
		if (level > 5) {
			displaySuccess();
			system("pause");
			overKeyEvent();
			break;
		}
	}
}

//void Game::bigBlockMode() {
//}

void Game::play() {
	// 初始化图形窗口
	while (true) {
		if (musicFlag) {
			std::string tempString = "play " + musicFiles[musicIndex] + " repeat";
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide = converter.from_bytes(tempString);
			mciSendString(wide.c_str(), 0, 0, 0);
			if (preMusicIndex != musicIndex) {
				tempString = "stop " + musicFiles[preMusicIndex];
				wide = converter.from_bytes(tempString);
				mciSendString(wide.c_str(), NULL, 0, NULL);
				preMusicIndex = musicIndex;
			}
		}
		else {
			std::string tempString = "stop " + musicFiles[musicIndex];
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring wide = converter.from_bytes(tempString);
			//mciSendString(L"stop res/bg.mp3 repeat", NULL, 0, NULL);
			mciSendString(wide.c_str(), NULL, 0, NULL);
		}
		//initgraph(640, 480, EX_SHOWCONSOLE);

		BeginBatchDraw();
		//打印界面元素
		background.Put(0, 0);
		// 显示菜单

		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		LOGFONT f;
		gettextstyle(&f);       // 获取当前字体设置
		f.lfHeight = 40;        // 设置字体高度为25
		_tcscpy_s(f.lfFaceName, _T("MicroSoft YaHei"));    // 设置字体为 Consolas
		f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
		settextstyle(&f);       // 应用字体样式设置

		outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按1：经典模式")) / 2, 100, _T("按1：经典模式"));
		outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按1：经典模式")) / 2, 150, _T("按2：挑战模式"));
		outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按1：经典模式")) / 2, 200, _T("按3：游戏设置"));
		outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按1：经典模式")) / 2, 250, _T("按4：退出游戏"));
		EndBatchDraw();

		static clock_t start = clock() - 1000;
		if ((double)(clock() - start) / CLK_TCK < 1)
			continue;
		start = clock();

		if (GetAsyncKeyState(0x31)) {
			cleardevice();
			// 进入经典模式
			this->curMode = 0;
			classicMode();
		}
		else if (GetAsyncKeyState(0x32)) {
			clock_t start = clock();
			while (1) {
				BeginBatchDraw();
				//打印界面元素
				background.Put(0, 0);
				// 显示菜单

				settextcolor(WHITE);
				setbkmode(TRANSPARENT);
				LOGFONT f;
				gettextstyle(&f);       // 获取当前字体设置
				f.lfHeight = 40;        // 设置字体高度
				_tcscpy_s(f.lfFaceName, _T("MicroSoft YaHei"));    // 设置字体为 Consolas
				f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
				settextstyle(&f);       // 应用字体样式设置
				// 进入挑战模式

				outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按5:隐身模式")) / 2, 100, _T("按5:隐身模式"));
				outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按6:反转模式")) / 2, 150, _T("按6:反转模式"));
				outtextxy(WINDOW_WIDTH / 2 - textwidth(_T("按7:返回")) / 2, 200, _T("按7:返回"));

				EndBatchDraw();
				if ((double)(clock() - start) / CLK_TCK < 1)
					continue;

				if (GetAsyncKeyState(0x35)) {
					this->curMode = 1;
					cleardevice();
					// Option 1
					stealthMode();
				}
				else if (GetAsyncKeyState(0x36)) {
					this->curMode = 2;
					cleardevice();
					reverseMode();
				}
				else if (GetAsyncKeyState(0x37)) {
					cleardevice();
					// Back to Main Menu
					break;
				}
			}
		}
		else if (GetAsyncKeyState(0x33)) {
			// 进入游戏设置
			cleardevice();
			/*outtextxy(100, 50, _T("使用←→平移方块，↑变形，↓加速"));
			outtextxy(100, 100, _T("八个小矮人与白雪公组"));*/
			// 定义音乐按钮的坐标范围
			const int MUSIC_BUTTON_LEFT = 100;
			const int MUSIC_BUTTON_TOP = 200;
			const int MUSIC_BUTTON_RIGHT = 350;
			const int MUSIC_BUTTON_BOTTOM = 250;
			setfillcolor(RGB(9, 63, 158));
			solidrectangle(MUSIC_BUTTON_LEFT, MUSIC_BUTTON_TOP, MUSIC_BUTTON_RIGHT, MUSIC_BUTTON_BOTTOM);
			//定义清除历史记录按钮的坐标范围
			const int CLEARHISTORY_BUTTON_LEFT = 100;
			const int CLEARHISTORY_BUTTON_TOP = 300;
			const int CLEARHISTORY_BUTTON_RIGHT = 270;
			const int CLEARHISTORY_BUTTON_BOTTOM = 350;
			//定义返回按钮的坐标范围
			const int RETURN_BUTTON_LEFT = 100;
			const int RETURN_BUTTON_TOP = 400;
			const int RETURN_BUTTON_RIGHT = 200;
			const int RETURN_BUTTON_BOTTOM = 450;
			//音乐按钮1
			const int MUSIC_BUTTON_LEFT_1 = 100;
			const int MUSIC_BUTTON_TOP_1 = 100;
			const int MUSIC_BUTTON_RIGHT_1 = 200;
			const int MUSIC_BUTTON_BOTTOM_1 = 150;
			solidrectangle(MUSIC_BUTTON_LEFT_1, MUSIC_BUTTON_TOP_1, MUSIC_BUTTON_RIGHT_1, MUSIC_BUTTON_BOTTOM_1);
			//音乐按钮2
			const int MUSIC_BUTTON_LEFT_2 = 210;
			const int MUSIC_BUTTON_TOP_2 = 100;
			const int MUSIC_BUTTON_RIGHT_2 = 310;
			const int MUSIC_BUTTON_BOTTOM_2 = 150;
			solidrectangle(MUSIC_BUTTON_LEFT_2, MUSIC_BUTTON_TOP_2, MUSIC_BUTTON_RIGHT_2, MUSIC_BUTTON_BOTTOM_2);
			//音乐按钮3
			const int MUSIC_BUTTON_LEFT_3 = 320;
			const int MUSIC_BUTTON_TOP_3 = 100;
			const int MUSIC_BUTTON_RIGHT_3 = 420;
			const int MUSIC_BUTTON_BOTTOM_3 = 150;
			solidrectangle(MUSIC_BUTTON_LEFT_3, MUSIC_BUTTON_TOP_3, MUSIC_BUTTON_RIGHT_3, MUSIC_BUTTON_BOTTOM_3);


			while (true) {
				BeginBatchDraw();
				background.Put(0, 0);

				//TCHAR tempstr[20];          // 存储数字字符串的数组
				settextcolor(RGB(0, 174, 236));     // 设置文字颜色为蓝色
				setbkmode(TRANSPARENT); // 设置文字背景为透明
				// 设置文字样式
				LOGFONT f;
				gettextstyle(&f);       // 获取当前字体设置
				f.lfHeight = 40;        // 设置字体高度为25
				_tcscpy_s(f.lfFaceName, _T("MicroSoft YaHei"));    // 设置字体为 Consolas
				f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
				settextstyle(&f);       // 应用字体样式设置
				//_stprintf_s(tempstr, _T("音乐开关,点击后请返回"));
				outtextxy(100, 210, _T("音乐开关,点击后请返回"));
				//_stprintf_s(tempstr, _T("清除历史记录"));
				outtextxy(100, 310, _T("清除历史记录"));
				//_stprintf_s(tempstr, _T("返回"));
				outtextxy(100, 410, _T("返回"));

				outtextxy(110, 110, _T("音乐1"));

				outtextxy(220, 110, _T("音乐2"));

				outtextxy(330, 110, _T("音乐3"));
				EndBatchDraw();
				MOUSEMSG m; // 定义鼠标消息
				if (MouseHit()) {
					m = GetMouseMsg(); // 获取一条鼠标消息
					if (m.uMsg == WM_LBUTTONDOWN) {
						if (m.x > MUSIC_BUTTON_LEFT && m.x < MUSIC_BUTTON_RIGHT && m.y > MUSIC_BUTTON_TOP && m.y < MUSIC_BUTTON_BOTTOM) {
							// 如果鼠标左键按下的位置在按钮区域内，那么就改变标志变量的值
							std::cout << "music" << std::endl;
							this->musicFlag = !this->musicFlag;
							std::cout << this->musicFlag << std::endl;
							if (musicFlag) {
								MessageBoxTimeoutA(NULL, "音乐已经开启，请按返回键", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
							}
							else {
								MessageBoxTimeoutA(NULL, "音乐已经关闭，请按返回键", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
							}
						}
						else if (m.x > CLEARHISTORY_BUTTON_LEFT && m.x < CLEARHISTORY_BUTTON_RIGHT && m.y > CLEARHISTORY_BUTTON_TOP && m.y < CLEARHISTORY_BUTTON_BOTTOM) {
							std::cout << "clearhistory" << std::endl;
							clearHistory();
							MessageBoxTimeoutA(NULL, "记录已经清除", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
						}
						else if (m.x > RETURN_BUTTON_LEFT && m.x < RETURN_BUTTON_RIGHT && m.y > RETURN_BUTTON_TOP && m.y < RETURN_BUTTON_BOTTOM) {
							std::cout << "fanhui" << std::endl;
							break;
						}
						else if (m.x > MUSIC_BUTTON_LEFT_1 && m.x < MUSIC_BUTTON_RIGHT_1 && m.y > MUSIC_BUTTON_TOP_1 && m.y < MUSIC_BUTTON_BOTTOM_1) {
							MessageBoxTimeoutA(NULL, "当前音乐为音乐1", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
							musicIndex = 0;
						}
						else if (m.x > MUSIC_BUTTON_LEFT_2 && m.x < MUSIC_BUTTON_RIGHT_2 && m.y > MUSIC_BUTTON_TOP_2 && m.y < MUSIC_BUTTON_BOTTOM_2) {
							MessageBoxTimeoutA(NULL, "当前音乐为音乐2", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
							musicIndex = 1;
						}
						else if (m.x > MUSIC_BUTTON_LEFT_3 && m.x < MUSIC_BUTTON_RIGHT_3 && m.y > MUSIC_BUTTON_TOP_3 && m.y < MUSIC_BUTTON_BOTTOM_3) {
							MessageBoxTimeoutA(NULL, "当前音乐为音乐3", "Notice", MB_OK | MB_SYSTEMMODAL, 0, 1000);
							musicIndex = 2;
						}
					}
				}
			}
			cleardevice();
		}
		else if (GetAsyncKeyState(0x34)) {
			// 退出游戏
			exit(0);
		}
	}

	// 关闭图形窗口
	closegraph();
}

void Game::reverseKeyEvent() {
	unsigned char ch;
	int dx = 0;
	if (_kbhit()) {
		ch = _getch();
		if (ch == 'd') {
			isPaused = !isPaused;
		}
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 80:
				rotate();
				update = true;
				break;
			case 72:
				delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (dx != 0) {
		moveLeftOrRight(dx);
		update = true;
	}
}

int Game::getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Game::keyEvent() {
	unsigned char ch;
	int dx = 0;
	if (_kbhit()) {
		ch = _getch();
		if (ch == 'd') {
			isPaused = !isPaused;
		}
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				rotate();
				update = true;
				break;
			case 80:
				delay = SPEED_QUICK;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}
	if (dx != 0) {
		moveLeftOrRight(dx);
		update = true;
	}
}

void Game::updateWindow() {
	putimage(0, 0, &backImg);
	BeginBatchDraw();
	if (curMode != 2) {
		nextBlock->draw(leftDistance + 500, upDistance);
	}
	else {
		nextBlock->drawForReverse(leftDistance + 500, upDistance);
	}
	curBlock->draw(leftDistance, upDistance);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) {
				continue;
			}
			int x = leftDistance + j * blockSize;
			int y = upDistance + i * blockSize;
			putimage(x, y, Block::getImgs()[map[i][j] - 1]);
		}
	}
	drwaScore();
	EndBatchDraw();
}

void Game::updateWindowForStealth() {
	putimage(0, 0, &backImg);
	BeginBatchDraw();
	if (curMode != 2) {
		nextBlock->draw(leftDistance + 500, upDistance);
	}
	else {
		nextBlock->drawForReverse(leftDistance + 500, upDistance);
	}
	curBlock->draw(leftDistance, upDistance);
	drwaScore();
	EndBatchDraw();
}

void Game::drop() {
	preBlock = *curBlock;
	curBlock->drop();
	if (!curBlock->checkPositionIsValid(map)) {
		preBlock.solidy(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
		if (!curBlock->checkPositionIsValid(map)) {
			isOver = true;
		}
	}
	delay = SPEED_NORMAL[level - 1];
}

void Game::dropForReverse() {
	preBlock = *curBlock;
	curBlock->dropForReverse();
	if (!curBlock->checkPositionIsValid(map)) {
		preBlock.solidy(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block(1);
		if (!curBlock->checkPositionIsValid(map)) {
			isOver = true;
		}
	}
	delay = SPEED_NORMAL[level - 1];
}

void Game::clearLine() {
	int k = rows - 1;
	int lines = 0;
	int count = 0;
	for (int i = rows - 1; i >= 0; i--) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] != 0) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < cols) {
			k--;
		}
		else {
			lines++;
		}
		count = 0;
	}
	if (lines > 0) {
		int scores[4] = { 10,30,60,80 };
		score += scores[lines - 1];
		update = true;
		//sndPlaySound(L"res/xc0fb-l492x.wav", SND_ASYNC | SND_NODEFAULT);
		if (musicFlag) {
			mciSendString(L"play res/xiaochu1.mp3", 0, 0, 0);
		}

		level = (score + 99) / 100;
		countOfLines += lines;
	}
}

void Game::clearLineForReverse() {
	int k = 0;
	int lines = 0;
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] != 0) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < cols) {
			k++;
		}
		else {
			lines++;
		}
		count = 0;
	}
	if (lines > 0) {
		int scores[4] = { 10,30,60,80 };
		score += scores[lines - 1];
		update = true;
		if (musicFlag) {
			mciSendString(L"play res/xiaochu1.mp3", 0, 0, 0);
		}
		level = (score + 99) / 100;
		countOfLines += lines;
	}
}

void Game::moveLeftOrRight(int dx) {
	preBlock = *curBlock;
	curBlock->move(dx);
	if (!curBlock->checkPositionIsValid(map)) {
		*curBlock = preBlock;
	}
}

void Game::rotate() {
	preBlock = *curBlock;
	curBlock->rotate();
	if (!curBlock->checkPositionIsValid(map)) {
		*curBlock = preBlock;
	}
}

void Game::drwaScore() {
	TCHAR str[20];          // 存储数字字符串的数组
	settextcolor(RGB(180, 180, 180));     // 设置文字颜色
	setbkmode(TRANSPARENT); // 设置文字背景为透明
	// 设置文字样式
	LOGFONT f;
	gettextstyle(&f);       // 获取当前字体设置
	f.lfHeight = 35;        // 设置字体高度为25
	_tcscpy_s(f.lfFaceName, _T("Consolas"));    // 设置字体为 Consolas
	f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
	settextstyle(&f);       // 应用字体样式设置
	_stprintf_s(str, _T("%d"), score);
	outtextxy(670, 727, str);
	_stprintf_s(str, _T("%d"), level);
	outtextxy(182, 730, str);
	_stprintf_s(str, _T("%d"), countOfLines);
	outtextxy(182, 830, str);
	_stprintf_s(str, _T("%d"), highestScore[curMode]);
	outtextxy(670, 832, str);
}

void Game::updateHighestScore(int curScores) {
	if (curScores > highestScore[curMode]) {
		highestScore[curMode] = score;
		std::ofstream outFile("bestScore.txt"); // 打开文件，如果文件不存在则创建
		if (outFile.is_open()) { // 检查文件是否成功打开
			for (int i = 0; i < 3; i++) {
				outFile << std::to_string(highestScore[i]) << '\n';
			}
			outFile.close(); // 关闭文件
		}
		else {
			std::cout << "无法打开文件。\n";
		}
	}
}

void Game::disPlayOver() {
	cleardevice();
	IMAGE img;
	loadimage(&img, L"res/over.png");
	putimage(280, 426, &img);
	outtextxy(300, 600, L"按1返回");
	outtextxy(300, 700, L"按2退出游戏");
}

void Game::displaySuccess() {
	IMAGE img;
	loadimage(&img, L"res/win.png");
	putimage(300, 426, &img);
}

void Game::clearHistory() {
	std::ofstream outFile("bestScore.txt"); // 打开文件，如果文件不存在则创建
	if (outFile.is_open()) { // 检查文件是否成功打开
		for (int i = 0; i < 3; i++) {
			outFile << std::to_string(0) << '\n';
		}
		outFile.close(); // 关闭文件
	}
	else {
		std::cout << "无法打开文件。\n";
	}
}

void Game::overKeyEvent() {
	IMAGE img;
	IMAGE img2;
	loadimage(&img, L"res/over.png");
	loadimage(&img2, L"res/over2.png");
	while (true) {
		BeginBatchDraw();
		//打印界面元素
		background.Put(0, 0);
		// 显示菜单

		putimage(280, 326, &img2, SRCAND);
		putimage(280, 326, &img, SRCPAINT);

		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		LOGFONT f;
		gettextstyle(&f);       // 获取当前字体设置
		f.lfHeight = 40;        // 设置字体高度为25
		_tcscpy_s(f.lfFaceName, _T("MicroSoft YaHei"));    // 设置字体为 Consolas
		f.lfQuality = ANTIALIASED_QUALITY;          // 设置输出效果为抗锯齿 
		settextstyle(&f);       // 应用字体样式设置

		outtextxy(300, 600, L"按空格返回");
		outtextxy(300, 700, L"按2退出游戏");

		EndBatchDraw();
		if (GetAsyncKeyState(0x32)) {
			exit(0);
		}
		else if (GetAsyncKeyState(0x20)) {
			return;
		}
	}
}
