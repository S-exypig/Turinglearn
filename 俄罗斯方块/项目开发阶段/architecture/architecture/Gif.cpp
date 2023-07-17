#include "Gif.h"
#include <locale>
#include <codecvt>
GIF::~GIF() {
    m_Frames.clear();
    m_width = m_height = m_FrameNum = 0;
    m_TimeGap = 0;
}
GIF::GIF(const char* path, int frame_num, int w, int h, double time_gap) :
    m_TimeGap(time_gap),
    m_width(w),
    m_height(h),
    m_FrameNum(frame_num)
{
    m_Frames.clear();
    for (int i = 1; i <= frame_num; i++) {
        string s_path(path);
        s_path += '/';
        s_path += to_string(i);
        s_path += ".png";
        IMAGE* img = new IMAGE;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wide = converter.from_bytes(s_path);
        loadimage(img, wide.c_str(), w, h);
        m_Frames.push_back(img);
    }
    m_CurrentFrame = 0;
}

void GIF::Put(int x, int y) {
    static clock_t start = clock() - m_TimeGap * CLK_TCK;
    clock_t moment = clock();
    putimage(x, y, m_Frames[m_CurrentFrame]);
    if ((double)(moment - start) / CLK_TCK >= m_TimeGap)
    {
        start = clock();
        m_CurrentFrame = (m_CurrentFrame + 1) % m_FrameNum;
    }
}

void GIF::RePut(int x, int y) {
    m_CurrentFrame = 0;

    static clock_t start = clock() - (clock_t)m_TimeGap * CLK_TCK;
    clock_t moment = clock();
    putimage(x, y, m_Frames[m_CurrentFrame]);
    if ((double)(moment - start) / CLK_TCK >= m_TimeGap)
    {
        start = clock();
        m_CurrentFrame = (m_CurrentFrame + 1) % m_FrameNum;
    }
}
