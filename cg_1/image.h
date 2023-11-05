#pragma once

#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Image final
{
public:
    Image();
    Image(const int width, const int height, const int nChannels);

    Image(const Image&);
    Image(Image&&) noexcept;

    ~Image();

    Image& operator=(const Image&);
    Image& operator=(Image&&) noexcept;

    bool isRead(const string& path);
    bool isWrite(const string& path);
    
    void setPixel(const int row, const int col, const int r, const int g, const int b, const int a);
    void getPixel(const int row, const int col, int& r, int& g, int& b, int& a);

    void equalizeHistogram();

    std::array<int, 256> getHistogram() const;

    void stretchHistogram();

    std::pair<uint8_t, uint8_t> getMinMaxBrightness() const;


private:
    int m_width{ 0 };
    int m_height{ 0 };

    int m_nChannels;

    int m_size;


    unique_ptr<uint8_t[]> m_data{ nullptr };
};


