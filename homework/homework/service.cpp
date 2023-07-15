#include"service.h"

int map[19][19];
int flag;
int rounds;

void init() {
	/*
	����: ��ʼ����Ϸ����
	�����̵�ֵ��ʼ��Ϊ0
	��ǰ�غ���Ϊ����(flag��Ϊ1)
	����: void
	����ֵ: void
*/
	// ��ʼ������Ϊ0
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++)
			map[i][j] = 0;
	}
	// ��ʼ���غ���
	rounds = 1;
	// ��ʼ����ǰ�غ�Ϊ����
	flag = 1;
}


int isWin(int x, int y) {
	/*
	����: ���ݴ��������(map��Ӧλ��)��flagֵ �ж������Ƿ��ʤ ��δ��ʤ������ɫ
		����:
			x: ��ǰ�غ����ӵ�x����
			y: ��ǰ�غ����ӵ�y����
		����ֵ:
			0��ʾû�л�ʤ
			1��ʾ����ʤ��
			2��ʾ����ʤ��
*/
	int i, j;
	int count = 0; // ͳ������������
	int color = map[x][y];
	// ����
	for (i = x - 4; i <= x + 4; i++) {
		if (i < 0 || i > 18)
			continue;
		// �������Ϊͬһ��ɫ,��count++,��������ͳ��count
		if (map[i][y] == color)
			count++;
		else
			count = 0;
		if (count == 5)
			return color;
	}
	// ����
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
	// ���ϵ�����
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
	// ���µ�����
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
	����: ��ָ��λ������
	���map[x][y]�ǿյ� ���޸�map[x][y]��ֵ:��Ϊ��Ӧ��ɫ(flag��Ӧ��ɫ)
	���򲻲���
	����:
	x: ��ǰ�غ����ӵ�x����
	y: ��ǰ�غ����ӵ�y����
	����ֵ:
	0��ʾ����ʧ�� (�����Ѿ�����)
	1��ʾ���ӳɹ�
*/

	if (map[x][y] != 0)
		return 0;
	map[x][y] = flag;
	return 1;
}