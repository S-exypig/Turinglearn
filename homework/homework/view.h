#pragma once
#ifndef VIEW_H
#define VIEW_H
#include"service.h"
#include<iostream>

/*
	����: չʾѡ��, ��ҿ���������ѡ�������Ϸ, �������û��˳���Ϸ
	������Ϸ: ������Ϸ���溯��gameView();
	��������: �����ڴ�...
	�˳���Ϸ: ����exit(0);
*/
void menuView();

/*
	����: ����map���� ��ӡ��Ϸ����
	����: void
	����ֵ: void
*/
void gameView_ShowMap();

/*
	����: ����flag��ֵ ��ӡ��Ϸʤ������ �û����԰�������ص����˵�
	���� : void
	����ֵ : void
*/
void winView();

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
void gameView();

#endif // !VIEW_H

