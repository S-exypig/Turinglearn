#include"view.h"

int main() {
	//std::cout<<"��ʼ��Ϸ��!"<<std::endl<<std::endl;
	//menuView();

	int testflag = 0;
	// init����
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
	result &= playerMove(2, 2); // �ڣ�playMove���ı���ɫ
	result &= playerMove(2, 3); // �ڣ�
	result &= playerMove(2, 4); // �ڣ�
	result &= playerMove(2, 5); // �ڣ�
	if (result != 1 || (map[2][2] && map[2][3] && map[2][4] && map[2][5]) != 1)
	{
		std::cout<<"playerMove error"<<std::endl;
		exit(0);
	}
	flag = 1;
	result &= playerMove(2, 5); // ����ʧ�ܣ���ʱΪ����
	if (result != 0 || map[2][5] != 1) {
		std::cout << "playerMove error" << std::endl;
		exit(0);
	}
	std::cout << "playerMove()���Գɹ�\n";
	testflag++;

	playerMove(2, 1); //����
	if (isWin(2, 1)) { //δ��ʤ�򽻻���ɫ
		std::cout << "isWin(2,1) error\n";
		exit(0);
	}
	flag = 1;
	playerMove(1, 0); //����
	playerMove(3, 2); //����
	playerMove(4, 3); //����
	playerMove(5, 4); //����
	if (isWin(1, 0) != 2) {
		std::cout << "isWin(1,0) ����" << std::endl;
		exit(0);
	}
	std::cout << "isWin()���Գɹ�\n";
	testflag++;

	if (testflag == 3) {
		std::cout << "service������Գɹ�\n";
	}

	return 0;
}