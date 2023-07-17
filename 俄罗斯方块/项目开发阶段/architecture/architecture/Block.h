#pragma once
#include <graphics.h>
#include <vector>

/*
ÿ��������ĸ�С�����λ�����꣬��main.cpp
*/
struct Position {
	int row, col;
};
/*
	������
*/
class Block {
public:
	/*�����ˣ�����
		���ܣ������ʼ�������ѡ��һ����ɫ������״����ֵ��blockType����ʼ���÷���ÿ��С���������position[4],��ȡ��С�����Ӧ��ͼ���ļ���ֵ��img
	*/
	Block();


	/*�����ˣ���һ
	* ���ܣ���תģʽ�µķ����ʼ������Ҫ�ı䷽��ĳ�ʼλ��
	*/
	Block(int reverse);

	///*
	//* ���ܣ��󷽿�ģʽ�µķ����ʼ��
	//*/
	//Block(double bigMode);

	/*�����ˣ��Ѽ�
	���ܣ��������䣬��position���ĸ�С�����row�����һ����Game���drop()��������
	*/
	void drop();

	/*�����ˣ��Ѽ�
	* ���ܣ���תģʽ�µķ�������,��position���ĸ�С�����row�����һ����Game���drop()��������
	*/
	void dropForReverse();

	/*�����ˣ��Ѽ�
	* ���ܣ��ƶ�����������ƫ��ֵ��ÿ��С������col���иı䣬��Game���moveLeftOrRight()����
	* ������ƫ��ֵ�������������Ϣȷ��Ϊ1��-1
	*/
	void move(int dx);

	/*�����ˣ��Ѽ�
	* ���ܣ����ݹ�ʽ�Է��������ת����Game��roate()��������
	*    ʵ��˼·��
	*	Position p = position[1];
		for (int i = 0; i < 4; i++) {
			Position tmp = position[i];
			position[i].col = p.col - tmp.row + p.row;
			position[i].row = p.row + tmp.col - p.col;
		}
	*/
	void rotate();

	/*�����ˣ���һ
		���ܣ���������Ƶ�������
		������leftMarginΪ��Ϸ��ͼ�У������ʼλ�þ��봰����߽�ľ���
			  topMarginΪ��Ϸ��ͼ�У������ʼλ�þ��봰���ϱ߽�ľ���
	*/
	void draw(int leftMargin, int topMargin);

	/*
	���ܣ�����imgs��Ա
	*/
	static IMAGE** getImgs();

	/*�����ˣ���һ
	���ܣ����������=�����ڿ�������blockType��position
	*/
	Block& operator=(const Block& other);

	/*�����ˣ�լè
	* ���ܣ���鷽���Ƿ��ںϷ�λ�ã��Ϸ�λ��ָposition�е��ĸ�����Դ��ڱ߽��ڣ���û��map�в�Ϊ0��ֵ�غ�
	* �����������ͼ���ݣ������ж�
	* ����ֵ������true���Ϸ�������false�����Ϸ�
	*/
	bool checkPositionIsValid(const std::vector<std::vector<int>>& map);

	/*�����ˣ�լè
	* ���ܣ�����position�ĸ�С��������꣬�����Ӧ��ֵ��ֵ��map�Ķ�Ӧλ��
	* �����������ͼ����map�������޸ĵ�ͼ������
	*/
	void solidy(std::vector<std::vector<int>>& map);

	/*
	* ������ģʽ�µķ������
	*/
	void drawForReverse(int leftMargin, int upMargin);


private:
	//�������ͣ���Ӧ7����ɫ��ȡֵΪ1-7
	int blockType;
	//������ĸ�С���������
	Position position[4];
	//�󷽿�ģʽ�µ�8��С���������
	Position bigPosition[8];
	//����ÿ��С�����ͼƬ�ļ����ĸ�С���鶼��ͬһ����ɫ�����Թ���һ��img�ļ�����
	IMAGE* img;
	//��̬���������е���״���е�7����ɫ�ļ�������blockType==1����ȡ��imgs�еĵ�0����ɫ�ļ���ֵ��img�ļ�
	static IMAGE* imgs[7];
	//�������Ⱦ�ߴ�
	static int size;
};