#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <memory>
#include <string>
#include <iostream>
#include "stb_image.hpp"
#include "stb_image_write.hpp"

template<typename ColorTypeTrait>
class Histogram;

template<typename ColorTypeTrait>
class Image final
{
public:
	Image()
	{
		this->height = 0;
		this->width = 0;
		this->size = 0;
		this->numberChannels = 0;
		this->data = nullptr;
	}

	Image(const int width, const int height, const int m_nChannels)
	{
		this->height = height;
		this->width = width;
		this->numberChannels = m_nChannels;
		data = std::make_unique<typename ColorTypeTrait::codingType[]>(size);
	}

	Image(const Image& obj)
	{
		this->height = obj.height;
		this->width = obj.width;
		this->size = obj.size;
		this->numberChannels = obj.numberChannels;

		this->data = std::make_unique<ColorTypeTrait::codingType[]>(size);
		for (int i = 0; i < size; i++) {
			data[i] = obj.data[i];
		}
	}

	Image(Image&& obj) noexcept
	{
		height = obj.height;
		width = obj.width;
		size = obj.size;
		numberChannels = obj.numberChannels;
		data = std::move(obj.data);

		obj.data = nullptr;
	}

	Image& operator=(const Image& obj)
	{
		this->height = obj.height;
		this->width = obj.width;
		this->size = obj.size;
		this->numberChannels = obj.numberChannels;

		this->data = std::make_unique<ColorTypeTrait::codingType[]>(size);
		for (int i = 0; i < size; i++) {
			data[i] = obj.data[i];
		}
		return *this;
	}

	Image& operator=(Image&& obj) noexcept
	{
		if (&obj == this)
			return *this;

		height = obj.height;
		width = obj.width;
		size = obj.size;
		numberChannels = obj.numberChannels;
		data = std::move(obj.data);

		obj.data = nullptr;

		return *this;
	}

	bool isRead(const std::string& path)
	{
		data.reset(stbi_load(path.c_str(), &width, &height, &numberChannels, 0));
		if (data)
			size = width * height * numberChannels;
		return false;
	}

	bool isWrite(const std::string& path)
	{
		return stbi_write_png(path.c_str(), width, height, numberChannels, data.get(), 0);
	}

	void setPixel(const int row, const int col, const int r, const int g, const int b, const int a)
	{
		int index = (row * width + col) * numberChannels;

		data[index] = static_cast<ColorTypeTrait::codingType>(r);
		data[index + 1] = static_cast<ColorTypeTrait::codingType>(g);
		data[index + 2] = static_cast<ColorTypeTrait::codingType>(b);
		if (numberChannels == 4)
			data[index + 3] = static_cast<ColorTypeTrait::codingType>(a);
	}

	void getPixel(const int row, const int col, int& r, int& g, int& b, int& a)
	{
		int index = (row * width + col) * numberChannels;

		r = data[index];
		g = data[index + 1];
		b = data[index + 2];
		if (numberChannels == 4)
			a = data[index + 3];
		else
			a = ColorTypeTrait::max;
	}

private:
    friend class Histogram<ColorTypeTrait>;
    int width{ 0 };
    int height{ 0 };

    int numberChannels;

    int size;

    std::unique_ptr<typename ColorTypeTrait::codingType[]> data{ nullptr };
};
