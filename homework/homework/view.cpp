#include"view.h"

void menuView() {
	/*
		����: չʾѡ��, ��ҿ���������ѡ�������Ϸ, �������û��˳���Ϸ
		������Ϸ: ������Ϸ���溯��gameView();
		��������: �����ڴ�...
		�˳���Ϸ: ����exit(0);
	*/
	int choice;
	while (true)
	{
		std::cout << "��ѡ�����:" << std::endl;
		std::cout << "1. ������Ϸ" << std::endl;
		std::cout << "2. ��������" << std::endl;
		std::cout << "3. �˳���Ϸ" << std::endl;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			gameView();
			break;
		case 2:
			std::cout << "�����ڴ�..." << std::endl;
			break;
		case 3:
			std::cout << "�����˳�..." << std::endl;
			std::cout << "��Ϸ������" << std::endl;
			exit(0);
		default:
			std::cout<< "�������,����������!" << std::endl;
		}
	}
}


void gameView_ShowMap() {
	/*
	����: ����map���� ��ӡ��Ϸ����
	����: void
	����ֵ: void
*/
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++)
			std::cout << map[i][j] << " ";
		std::cout << std::endl;
	}
}


void winView() {
	/*
	����: ����flag��ֵ ��ӡ��Ϸʤ������ �û����԰�������ص����˵�
	���� : void
	����ֵ : void
*/
	gameView_ShowMap(); // ʤ��ǰ��ӡ���һ������
	if (flag == 1) {
		std::cout << "����ʤ��!" << std::endl;
	}
	else {
		std::cout << "����ʤ��!" << std::endl;
	}
	std::cout << "��������ص����˵�..." << std::endl;
	system("pause");
	system("cls");
}


void gameView() {
	/*
	*�ѵ�2
	����: ��Ϸ��������
	��ʼ����Ϸ����(���ú���init())
	while(1){
	��ӡ��Ϸ����(���ú���gameView_ShowMap())
	���������������
	����(�������Ӻ���playerMove())
	(�������ʧ�� ���¿�ʼѭ��)
	�ж���Ϸ�Ƿ�ʤ��(����ʤ���жϺ���isWin())
	(�����Ϸʤ�� ����ʤ�����溯�� Ȼ�������ǰ����)
	�л����(�޸�flagֵ)
	}
	����: void
	����ֵ: void
*/
	init();
	while (true)
	{
		std::cout << "---------------------------------" << std::endl;
		std::cout<< "�� " << rounds << " ��  "<<"��ǰΪ: "<< ((flag==1)?"��":"��") << "��" << std::endl;
		gameView_ShowMap();
		int x, y;
		std::cout << "��������������(�Կո�ָ�):" << std::endl;
		std::cin >> x >> y;
		if (x < 0 || x>18 || y < 0 || y>18) {
			std::cout << "�����������,����������!" << std::endl;
			continue;
		}
		if (playerMove(x,y)) {
			std::cout << "���ӳɹ�!" << std::endl;
		}
		else {
			std::cout << "����ʧ��!" << std::endl;
			continue;
		}
		if (isWin(x,y)) {
			winView();
			break;
		}
		++rounds;
	}
}