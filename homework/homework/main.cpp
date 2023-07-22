#include"view.h"

int main() {
	//std::cout<<"¿ªÊ¼ÓÎÏ·¿©!"<<std::endl<<std::endl;
	//menuView();

	int testflag = 0;
	// init²âÊÔ
	init();
	if (flag != 0) {
		std::cout<<"init flag error"<<std::endl;
		exit(0);
	}
	for (int i{}; i < 19; ++i) {
		for (int j{}; j < 19; ++j) {
			if (map[i][j]) {
				std::cout<<"init map error"<<std::endl;
				exit(0);
			}
		}
	}
	std::cout<<"init success"<<std::endl;
	++testflag;

	int result = 1;
	result &= playerMove(2, 2); // ºÚ£¬playMove²»¸Ä±äÑÕÉ«
	result &= playerMove(2, 3); // ºÚ£¬
	result &= playerMove(2, 4); // ºÚ£¬
	result &= playerMove(2, 5); // ºÚ£¬
	if (result != 1 || (map[2][2] && map[2][3] && map[2][4] && map[2][5]) != 1)
	{
		std::cout<<"playerMove error"<<std::endl;
		exit(0);
	}
	flag = 1;
	result &= playerMove(2, 5); // Âä×ÓÊ§°Ü£¬´ËÊ±Îª°×Æå
	if (result != 0 || map[2][5] != 1) {
		std::cout << "playerMove error" << std::endl;
		exit(0);
	}
	std::cout << "playerMove()²âÊÔ³É¹¦\n";
	testflag++;

	playerMove(2, 1); //°×Æå
	if (isWin(2, 1)) { //Î´»ñÊ¤Ôò½»»»ÑÕÉ«
		std::cout << "isWin(2,1) error\n";
		exit(0);
	}
	flag = 1;
	playerMove(1, 0); //°×Æå
	playerMove(3, 2); //°×Æå
	playerMove(4, 3); //°×Æå
	playerMove(5, 4); //°×Æå
	if (isWin(1, 0) != 2) {
		std::cout << "isWin(1,0) ´íÎó" << std::endl;
		exit(0);
	}
	std::cout << "isWin()²âÊÔ³É¹¦\n";
	testflag++;

	if (testflag == 3) {
		std::cout << "service´úÂë²âÊÔ³É¹¦\n";
	}

	return 0;
}