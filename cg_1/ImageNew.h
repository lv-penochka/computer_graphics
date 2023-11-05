#pragma once

#include <memory>
#include <string>
#include <iostream>

using namespace std;

template<unsigned L>
class ImageNew final
{
public:

	ImageNew::ImageNew()
	{
		this->m_height = 0;
		this->m_width = 0;
		this->m_size = 0;
		this->m_nChannels = 0;
		this->m_data = nullptr;
	}

	ImageNew::ImageNew(const int width, const int height, const int m_nChannels)

	{
		this->m_height = height;
		this->m_width = width;
		this->m_nChannels = m_nChannels;
		m_data = std::make_unique<uint8_t[]>(m_size);
	}

	ImageNew::ImageNew(const ImageNew& obj)
	{
		this->m_height = obj.m_height;
		this->m_width = obj.m_width;
		this->m_size = obj.m_size;
		this->m_nChannels = obj.m_nChannels;

		this->m_data = std::make_unique<uint8_t[]>(m_size);
		for (int i = 0; i < m_size; i++) {
			m_data[i] = obj.m_data[i];
		}
	}

	ImageNew::ImageNew(ImageNew&& obj) noexcept
	{
		m_height = obj.m_height;
		m_width = obj.m_width;
		m_size = obj.m_size;
		m_nChannels = obj.m_nChannels;
		m_data = std::move(obj.m_data);

		obj.m_data = nullptr;
	}

	ImageNew::~ImageNew()
	{
	}

	ImageNew& ImageNew::operator=(const ImageNew& obj)
	{
		this->m_height = obj.m_height;
		this->m_width = obj.m_width;
		this->m_size = obj.m_size;
		this->m_nChannels = obj.m_nChannels;

		this->m_data = std::make_unique<uint8_t[]>(m_size);
		for (int i = 0; i < m_size; i++) {
			m_data[i] = obj.m_data[i];
		}
		return *this;
	}

	ImageNew& ImageNew::operator=(ImageNew&& obj) noexcept
	{
		if (&obj == this)
			return *this;

		m_height = obj.m_height;
		m_width = obj.m_width;
		m_size = obj.m_size;
		m_nChannels = obj.m_nChannels;
		m_data = std::move(obj.m_data);

		obj.m_data = nullptr;

		return *this;
	}

	bool ImageNew::isRead(const std::string& path)
	{
		m_data.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_nChannels, 0));
		if (m_data)
			m_size = m_width * m_height * m_nChannels;
		return false;
	}

	bool ImageNew::isWrite(const std::string& path)
	{
		return stbi_write_png(path.c_str(), m_width, m_height, m_nChannels, m_data.get(), 0);
	}

	void ImageNew::setPixel(const int row, const int col, const int r, const int g, const int b, const int a)
	{
		int index = (row * m_width + col) * m_nChannels;

		m_data[index] = static_cast<uint8_t>(r);
		m_data[index + 1] = static_cast<uint8_t>(g);
		m_data[index + 2] = static_cast<uint8_t>(b);
		if (m_nChannels == 4)
			m_data[index + 3] = static_cast<uint8_t>(a);
	}

	void ImageNew::getPixel(const int row, const int col, int& r, int& g, int& b, int& a)
	{
		int index = (row * m_width + col) * m_nChannels;

		r = m_data[index];
		g = m_data[index + 1];
		b = m_data[index + 2];
		if (m_nChannels == 4)
			a = m_data[index + 3];
		else
			a = 255;
	}

	void ImageNew::equalizeHistogram() {
		auto histogram = getHistogram();
		auto getCumulativeFrequency = [histogram](const int k) -> int {
			int result = 0;
			for (int i = 0; i <= k; ++i) {
				result += histogram[i];
			}
			return result;
		};
		for (int i = 0; i < m_size; ++i) {
			auto pixel = m_data[i];
			m_data[i] = ( double(L - 1) / m_size) * getCumulativeFrequency(pixel); // TODO: заменить на L - 1
		}
	}

	std::array<int, L> ImageNew::getHistogram() const
	{
		std::array<int, L> histogram;
		histogram.fill(0);

		for (int i = 0; i < m_size; ++i) {
			uint8_t pixelValue = m_data[i];
			histogram[pixelValue]++;
		}
		return histogram;
	}

	// Реализация метода равномерного растяжения гистограммы
	void ImageNew::stretchHistogram() {
		// Найти минимальное и максимальное значение яркости пикселей
		int minValue = m_data[0];
		int maxValue = m_data[0];
		for (int i = 1; i < m_size; ++i) {
			uint8_t pixelValue = m_data[i];
			if (pixelValue < minValue) {
				minValue = pixelValue;
			}
			if (pixelValue > maxValue) {
				maxValue = pixelValue;
			}
		}

		// Растянуть гистограмму
		for (int i = 0; i < m_size; ++i) {
			uint8_t pixelValue = m_data[i];
			uint8_t stretchedValue = (255.0 * (pixelValue - minValue) / (maxValue - minValue));
			if (pixelValue != stretchedValue) std::cout << "ZALUPA";
			m_data[i] = stretchedValue;
		}
	}


private:
    int m_width{ 0 };
    int m_height{ 0 };

    int m_nChannels;

    int m_size;


    unique_ptr<uint8_t[]> m_data{ nullptr };
};


