#pragma once
#include <easyx.h>
#include <graphics.h>
#include <vector>
#include <utility>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;
class [[maybe_unused]] GIF
{
protected:
    vector<IMAGE*>  m_Frames;                   //���ÿһ֡������
    int             m_FrameNum;                 //��gif��֡��
    int             m_width, m_height;          //��gif�ĳߴ�
    double          m_TimeGap;                  //֡ʱ����
    int             m_CurrentFrame;             //��ǰ����֡�����
public:
    //����
    [[maybe_unused]] explicit GIF(
        const char* path,       //���Gif����֡���ļ���·��
        int frame_num,          //ͼƬ֡��
        int w,                  //ͼƬ���
        int h,                  //ͼƬ�߶�
        double time_gap         //֡ʱ����
    );
    //����
    ~GIF();
    //����gif�����easyx��ͼ���ڣ�ÿ�ε���ֻ���һ֡
    void Put(int x, int y);
    //�ӵ�һ֡��ʼ������gif�����easyx��ͼ���ڣ�ÿ�ε���ֻ���һ֡
    void RePut(int x, int y);
};
