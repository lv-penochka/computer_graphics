#pragma once

#include <memory>
#include <string>
#include <iostream>

namespace ImageTransformation 
{

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

private:
    friend class Histogram;
    int width{ 0 };
    int height{ 0 };

    int numberChannels;

    int size;

    std::unique_ptr<uint8_t[]> data{ nullptr };
};

} // namespace ImageTransformation

