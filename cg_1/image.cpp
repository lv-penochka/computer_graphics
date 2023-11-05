#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "image.h"

#include "libs/stb_image.h"
#include "libs/stb_image_write.h"
#include <algorithm>
#include <array>


Image::Image()
{
	this->m_height = 0;
	this->m_width = 0;
	this->m_size = 0;
	this->m_nChannels = 0;
	this->m_data = nullptr;
}

Image::Image(const int width, const int height, const int m_nChannels)

{
	this->m_height = height;
	this->m_width = width;
	this->m_nChannels = m_nChannels;
	m_data = std::make_unique<uint8_t[]>(m_size);
}

Image::Image(const Image& obj)
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

Image::Image(Image&& obj) noexcept
{
	m_height = obj.m_height;
	m_width = obj.m_width;
	m_size = obj.m_size;
	m_nChannels = obj.m_nChannels;
	m_data = std::move(obj.m_data);

	obj.m_data = nullptr;
}

Image::~Image()
{
}

Image& Image::operator=(const Image& obj)
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

Image& Image::operator=(Image&& obj) noexcept
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

bool Image::isRead(const std::string& path)
{
	m_data.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_nChannels, 0));
	if (m_data)
		m_size = m_width * m_height * m_nChannels;
	return false;
}

bool Image::isWrite(const std::string& path)
{
	return stbi_write_png(path.c_str(), m_width, m_height, m_nChannels, m_data.get(), 0);
}

void Image::setPixel(const int row, const int col, const int r, const int g, const int b, const int a)
{
	int index = (row * m_width + col) * m_nChannels;

	m_data[index] = static_cast<uint8_t>(r);
	m_data[index + 1] = static_cast<uint8_t>(g);
	m_data[index + 2] = static_cast<uint8_t>(b);
	if (m_nChannels == 4)
		m_data[index + 3] = static_cast<uint8_t>(a);
}

void Image::getPixel(const int row, const int col, int& r, int& g, int& b, int& a)
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

void Image::equalizeHistogram() {
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
		m_data[i] = (255.0 / m_size) * getCumulativeFrequency(pixel);
	}
}

std::array<int, 256> Image::getHistogram() const
{
	std::array<int, 256> histogram;
	histogram.fill(0);

	for (int i = 0; i < m_size; ++i) {
		uint8_t pixelValue = m_data[i];
		histogram[pixelValue]++;
	}
	return histogram;
}

void Image::stretchHistogram() {
	auto brightness = getMinMaxBrightness();
	auto minBrightness = brightness.first;
	auto maxBrightness = brightness.second;

	for (int i = 0; i < m_size; ++i) {
        uint8_t pixelValue = m_data[i];
        uint8_t stretchedValue = (255.0 * (pixelValue - minBrightness) / (maxBrightness - minBrightness));
        if (pixelValue != stretchedValue);
        m_data[i] = stretchedValue;
    }
}

std::pair<uint8_t, uint8_t> Image::getMinMaxBrightness() const
{
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
	return { minValue, maxValue };
}
