#pragma once
#include <vector>
#include <graphics.h>
#include "Block.h"
#include <string>

const int WINDOW_WIDTH = 938;
const int WINDOW_HEIGHT = 896;

class Game {
public:
	/*	�����ˣ��鳤
		���캯�������õ�ͼ��������������������߾���ϱ߾�(�������ʼλ�þ��봰����ߺͶ����ľ���)�����ÿ��С
	*/
	Game(int rows, int cols, int leftDistance, int upDistance, int blockSize);


	/*�����ˣ��
	���ܣ���ʼ��������countTime��delay��score��level��isOver�ȣ�
		�����������ӣ���ʼ������
		��ȡ����ͼƬ����backImg
		��ȡ��ģʽ��߷֣�����highestScore[]
	��������
	����ֵ�� void
	*/
	void init();

	/*
	* �����ˣ��鳤
	* ���ܣ�����ģʽ�µ����к�������play()��������
*	init();
	nextBlock = new Block;//������һ������
	curBlock = nextBlock;//��ֵ����ǰ����
	nextBlock = new Block;//�ٴ�������һ������
	while (true) {
		//if(musicFlag){
			��������
		}
		//�����û����룬�����������ƽ�ƣ���ת�ͼ���
		keyEvent();
		//��ȡʱ��
		countTime += getDelay();
		//�����±�־λ��Ϊtrue�����÷������亯��
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		//������±�־λupdateλtrue
		if (update) {
			update = false;
			//��Ⱦ����
			updateWindow();
			//���һ���жϣ����ӵ÷�
			clearLine();
		}
		//isOver������Ϸ�Ƿ����
		if (isOver) {
			isOver = false;
			//��Ϸ�����󣬸��ݵ�ǰ����������ʷ��߷�
			updateHighestScore(score);
			//չʾ��Ϸ��������
			disPlayOver();
			//�ٴν����û�������Ϣ��ѡ�����¿�ʼ�ص������棬ѡ�������Ϸ exit(0)
			overKeyEvent();
		}
		//level����ͬ��С��delay��5���������ʱ
		if (level > 5) {
			//չʾ��Ϸʤ������
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void classicMode();


	/*�����ˣ�cs
	* ���ܣ�����ģʽ�µ���ں�������play����
	* init();
	nextBlock = new Block;//������һ������
	curBlock = nextBlock;//��ֵ����ǰ����
	nextBlock = new Block;//�ٴ�������һ������
	* while (true) {
	*	//if(musicFlag){
			��������
		}
		//�����û����룬�����������ƽ�ƣ���ת�ͼ���
		keyEvent();
		//��ȡʱ��
		countTime += getDelay();
		//�����±�־λ��Ϊtrue�����÷������亯��
		if (countTime > delay) {
			update = true;
			drop();
			countTime = 0;
		}
		//������±�־λupdateλtrue
		if (update) {
			update = false;
			//��Ⱦ����
			updateWindowForStealth();
			//���һ���жϣ����ӵ÷�
			clearLine();
		}
		//isOver������Ϸ�Ƿ����
		if (isOver) {
			isOver = false;
			//��Ϸ�����󣬸��ݵ�ǰ����������ʷ��߷�
			updateHighestScore(score);
			//չʾ��Ϸ��������
			disPlayOver();
			//�ٴν����û�������Ϣ��ѡ�����¿�ʼ�ص������棬ѡ�������Ϸ exit(0)
			overKeyEvent();
		}
		//level����ͬ��С��delay��5���������ʱ
		if (level > 5) {
			//չʾ��Ϸʤ������
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void stealthMode();

	/*�����ˣ�cs
	* ���ܣ���תģʽ�µ���ں�������play����
	* init();
		nextBlock = new Block����;//������һ������
		curBlock = nextBlock;//��ֵ����ǰ����
		nextBlock = new Block����;//�ٴ�������һ������
		while (true) {
		//if(musicFlag){
			��������
		}
		//�����û����룬�����������ƽ�ƣ���ת�ͼ���
		reverseKeyEvent();
		//��ȡʱ��
		countTime += getDelay();
		//�����±�־λ��Ϊtrue�����÷������亯��
		if (countTime > delay) {
			update = true;
			dropForReverse();//���÷�תģʽ�µ����亯��
			countTime = 0;
		}
		//������±�־λupdateλtrue
		if (update) {
			update = false;
			//��Ⱦ����
			updateWindow();
			//���һ���жϣ����ӵ÷�
			clearLineForReverse();
		}
		//isOver������Ϸ�Ƿ����
		if (isOver) {
			isOver = false;
			//��Ϸ�����󣬸��ݵ�ǰ����������ʷ��߷�
			updateHighestScore(score);
			//չʾ��Ϸ��������
			disPlayOver();
			//�ٴν����û�������Ϣ��ѡ�����¿�ʼ�ص������棬ѡ�������Ϸ exit(0)
			overKeyEvent();
		}
		//level����ͬ��С��delay��5���������ʱ
		if (level > 5) {
			//չʾ��Ϸʤ������
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	void reverseMode();

	/*
	* ��δ���ƣ���ʱ��д
	* ���ܣ��󷽿�ģʽ�µ���ں�������play����
	* init();
		nextBlock = new Block����;//������һ�����飬���ô󷽿�ģʽ�µĹ��캯��
		curBlock = nextBlock;//��ֵ����ǰ����
		nextBlock = new Block����;//�ٴ�������һ�����飬���ô󷽿�ģʽ�µĹ��캯��
		while (true) {
		//if(musicFlag){
			��������
		}
		//�����û����룬�����������ƽ�ƣ���ת�ͼ���
		keyEvent();
		//��ȡʱ��
		countTime += getDelay();
		//�����±�־λ��Ϊtrue�����÷������亯��
		if (countTime > delay) {
			update = true;
			drop();//���þ���ģʽ�µ����亯��
			countTime = 0;
		}
		//������±�־λupdateλtrue
		if (update) {
			update = false;
			//��Ⱦ����
			updateWindow();
			//���һ���жϣ����ӵ÷�
			clearLine();
		}
		//isOver������Ϸ�Ƿ����
		if (isOver) {
			isOver = false;
			//��Ϸ�����󣬸��ݵ�ǰ����������ʷ��߷�
			updateHighestScore(score);
			//չʾ��Ϸ��������
			disPlayOver();
			//�ٴν����û�������Ϣ��ѡ�����¿�ʼ�ص������棬ѡ�������Ϸ exit(0)
			overKeyEvent();
		}
		//level����ͬ��С��delay��5���������ʱ
		if (level > 5) {
			//չʾ��Ϸʤ������
			displaySuccess();
			system("pause");
			break;
		}
	}
	*/
	//void bigBlockMode();

	/*�����ˣ�cs
		���ܣ���ں���
		while{true}{
				չʾ�����棬�ȴ��û�ѡ�񣨾���ģʽ����սģʽ����Ϸ���ã��˳���Ϸ��
				ѡ���˳���Ϸ��exit(0)
				ѡ����Ϸ���ã�
					չʾ��Ϸ���ý��棺
						չʾ�������
						С�����
						չʾ��ͬ������ť�������û�����л�backImg��ֵ
						չʾ�Ƿ񲥷����ְ�ť�������û�����л�musicFlag��־λ��ֵ��true��ʾ���ţ�fasle��ʾ������
						չʾ�����ʷ��¼ѡ���������clearHistory()
						չʾ���ذ�ť����������»ص�������,contiue;
				ѡ�񾭵�ģʽ
					void classicMode();
				ѡ����սģʽ��
					չʾ��սģʽ���棬��������ת��
					����ѡ������Ӧģʽ
						����ֻ��Ⱦ��һ������ķ����һ��ʱ��֮��ȥ�����Ҳ���Ҫ��Ⱦ��һ�����顣��ͼ����Ⱦȡ���������߼��뾭��ģʽӦ�û���һ��
							void stealthMode();
						��ת���޸ķ���ĳ�ʼ����λ�ú���Ⱦλ�ú������߼��Լ��÷ֺ�ʧ�ܵ��ж�
							void reverseMode();
						�󷽿飺ʹ��biGposition��Ϊ��������
							void bigBlockMode();
		}

	*/
	void play();

	/*
	* �����ˣ��̺�
	* ���ܣ���keyevent�෴������Ϊ���٣�����Ϊ����
	*/
	void reverseKeyEvent();
private:
	/*�����ˣ�cs
	���ܣ����ݳ���������������ʱ�䣨ms��������ʱ
	��������
	����ֵ���õ�countTime��ֵ
	*/
	int getDelay();

	/*�����ˣ��
	���ܣ���ȡ������Ϣ���룬����������ƣ���������ת����������١�������Ϣ���ö�Ӧ����ת����rotate()��ƽ�ƺ���moveLeftOrRight(int dx)
		  ���ټ��ͽ���delay��ֵ��
	*/
	void keyEvent();

	/*�����ˣ�����
	���ܣ����»��ƽ��棬�������Ʊ���ͼƬ����ǰ����Ļ��ƣ���һ������Ļ��ƣ���Ϸ��������Ϸ��ǰ�ȼ�����Ϸ��߷ֵĻ��ơ�
		�����Ѿ��̻�����Ļ���
	*/
	void updateWindow();

	/*�����ˣ�����
	* ���ܣ���Ⱦ����ģʽ�µĽ��棬ֻҪ��Ⱦ��һ�����飬����һ��ʱ���ȥ�����Ҳ���Ⱦ��һ�����飬��ͼ��Ⱦȡ����
	*/
	void updateWindowForStealth();

	/*�����ˣ����鳤
	���ܣ�ʵ�ַ���������Լ���������ʱ��Ϸ�Ƿ������־λ�ĸ���
		ʵ�ְ�����
		//���ȱ��浱ǰ�����λ��
		preBlock = *curBlock;
		//���÷��鱾������亯��
		curBlock->drop();
		//��������ķ���λ���Ƿ�Ϸ�
		if (!curBlock->checkPositionIsValid(map)) {
			//���Ϸ�������̻�����ͼ��
			preBlock.solidy(map);
			//ɾ����ǰ����
			delete curBlock;
			//����һ�����鸳ֵ����ǰ����
			curBlock = nextBlock;
			//������һ������
			nextBlock = new Block;
			//������һ������ʱ�����̽���λ�úϷ��жϣ������ϸ���˵����Ϸ����
			if (!curBlock->checkPositionIsValid(map)) {
				isOver = true;
			}
		}
		//�����¼��ټ�֮����ʱ��̣�Ϊ�˷�ֹ����һֱ���٣�������Ҫ����ԭ������ʱ
		delay = SPEED_NORMAL[level - 1];
	*/
	void drop();//����

	/*�����ˣ����鳤
	* ���ܣ�ʵ�ַ�תģʽ�µ�����
	*/
	void dropForReverse();


	/*
	* �����ˣ��鳤
	���ܣ����һ�У�����÷֣�����ʱ���������Ч
	*/
	void clearLine();

	/*
	* �����ˣ����鳤
	* ���ܣ���תģʽ�µ����һ�м���÷�
	*/
	void clearLineForReverse();

	/*�����ˣ��
	���ܣ�ʵ�ַ����ƽ�ƣ�ʵ��ģʽ�뷽������drop()���ƣ�
	������dxΪƫ����������Ϊ-1������Ϊ+1
	*/
	void moveLeftOrRight(int dx);

	/*�����ˣ�����
	���ܣ�ʵ�ַ������ת��ʵ��ģʽ�뷽������drop()���ƣ�
	*/
	void rotate();//��ת

	/*
	* �����ˣ�լè
	���ܣ��ڱ���ͼƬ��ָ��λ�ý���ǰ�ĵ÷֣��ȼ�����߷ֵ���Ϣ�����ڽ����ϣ���updateWindow()��updateWindowForStealth()��������
	*/
	void drwaScore();//��ʾ�÷�

	/*�����ˣ�cs
	���ܣ����ݱ��ε÷����ļ��б���ķ������бȽϣ������ھ͸����ļ������򲻱�
	������ ���ε÷�
	*/
	void updateHighestScore(int curScores);

	/*�����ˣ����鳤
	���ܣ���ӡ��Ϸ��������
	*/
	void disPlayOver();

	/*
	* �����ˣ��̺�
	*���ܣ���ӡ��Ϸ��ʤ����
	*/
	void displaySuccess();

	/*
	* �����ˣ��̺�
	* ���ܣ������ʷ��¼
	*/
	void clearHistory();

	/*
	* ��Ϸ�����󣬵ȴ��û�����������ݣ�����1��ʾ���»ص������档����2��ʾ������Ϸexit(0)
	*/
	void overKeyEvent();
public:
	static std::string musicFiles[3];//��ű������ֵ��ļ���
private:
	int countTime;//ͳ��ʱ�䣬�����ж��Ƿ���½���
	int delay;//��ʱ
	bool update;//�����Ƿ���±�־λ
	std::vector<std::vector<int>> map;//��ͼ����
	int rows, cols, leftDistance, upDistance, blockSize;//��ͼ�ĺ�������������ͼ���봰�ڵ��������Ͼ���
	IMAGE backImg;//����ͼƬ��ʹ�����飬��Ϊ���ж��ű���ͼƬ��
	Block* nextBlock;//��һ�����ɵķ���
	Block* curBlock;//��ǰ����
	Block preBlock;//��ʱ���飬���ڷ��ط�����һ��״̬
	int score;//��ǰ����
	int countOfLines;//��ǰ�Ѿ�����������
	int level;//��ǰ���ڵڼ���
	int highestScore[3];//��ǰ��߷֣�����ʹ�����飬��Ϊ�ж���ģʽ��
	bool isOver;//��Ϸ�Ƿ������־λ
	bool musicFlag;//�Ƿ񲥷����ֱ�־λ
	int curMode;//��ǰ����ʲô��Ϸģʽ��0�����䣬1��������2����ת
	bool isPaused;//��Ϸ��ǰ�Ƿ�����ͣ״̬
	int musicIndex;//�����ļ�����
	int preMusicIndex;//��һ�����ŵ�����
};

