#pragma once

#include <memory>
#include <string>
#include <iostream>

class Image final
{
public:
    Image();
    Image(const int width, const int height, const int nChannels);
    Image(const Image& obj);
    Image(Image&& obj) noexcept;
    ~Image() = default;

    Image& operator=(const Image& obj);
    Image& operator=(Image&& obj) noexcept;

    bool isRead(const std::string& path);
    bool isWrite(const std::string& path);
    
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

    std::unique_ptr<uint8_t[]> m_data{ nullptr };
};


