#include "Histogram.h"

#include <matplot/matplot.h>

Histogram::Histogram(const Image& image)
    : sourceImage(image)
{
    frequencyArray.fill(0);

    for (int i = 0; i < sourceImage.size; ++i) {
        auto pixel = sourceImage.data[i];
        frequencyArray[pixel]++;
    }
}

Histogram::Histogram(const Histogram& rhs)
    : sourceImage(rhs.sourceImage)
    , frequencyArray(rhs.frequencyArray)
{
}

Histogram::Histogram(Histogram&& rhs) noexcept
    : sourceImage(std::move(rhs.sourceImage))
    , frequencyArray(std::move(rhs.frequencyArray))
{
}

Image Histogram::generateEqualized()
{
    Image equalized(sourceImage);
    for (int i = 0; i < equalized.size; ++i) {
        auto pixel = equalized.data[i];
        equalized.data[i] = (255.0 / equalized.size) * getCumulativeFrequency(pixel);
    }
    return equalized;
}

Image Histogram::generateStretched()
{
    Image stretched(sourceImage);

    auto brightness = getMinMaxBrightness();
    auto minBrightness = brightness.first;
    auto maxBrightness = brightness.second;

    for (int i = 0; i < stretched.size; ++i) {
        uint8_t pixelValue = stretched.data[i];
        uint8_t stretchedValue = (255.0 * (pixelValue - minBrightness) / (maxBrightness - minBrightness));
        if (pixelValue != stretchedValue);
        stretched.data[i] = stretchedValue;
    }
    return stretched;
}

void Histogram::show() const
{
    std::array<int, 256> temp;
    for (int i = 0; i < temp.size(); ++i) {
        temp[i] = i;
    }
    matplot::stairs(temp, frequencyArray);
    matplot::show();
    return;
}

std::pair<uint8_t, uint8_t> Histogram::getMinMaxBrightness() const
{
    int minValue = sourceImage.data[0];
    int maxValue = sourceImage.data[0];
    for (int i = 1; i < sourceImage.size; ++i) {
        uint8_t pixelValue = sourceImage.data[i];
        if (pixelValue < minValue) {
            minValue = pixelValue;
        }
        if (pixelValue > maxValue) {
            maxValue = pixelValue;
        }
    }
    return { minValue, maxValue };
}

int Histogram::getCumulativeFrequency(int endBrightness) const
{
    int result = 0;
    for (int brightness = 0; brightness <= endBrightness; ++brightness) {
        result += frequencyArray[brightness];
    }
    return result;
}
