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
    vector<IMAGE*>  m_Frames;                   //存放每一帧的数组
    int             m_FrameNum;                 //该gif的帧数
    int             m_width, m_height;          //该gif的尺寸
    double          m_TimeGap;                  //帧时间间隔
    int             m_CurrentFrame;             //当前播放帧的序号
public:
    //构造
    [[maybe_unused]] explicit GIF(
        const char* path,       //存放Gif所有帧的文件夹路径
        int frame_num,          //图片帧数
        int w,                  //图片宽度
        int h,                  //图片高度
        double time_gap         //帧时间间隔
    );
    //析构
    ~GIF();
    //将该gif输出到easyx绘图窗口，每次调用只输出一帧
    void Put(int x, int y);
    //从第一帧开始，将该gif输出到easyx绘图窗口，每次调用只输出一帧
    void RePut(int x, int y);
};
