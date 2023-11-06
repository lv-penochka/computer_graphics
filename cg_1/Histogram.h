#pragma once
#include <array>
#include "image.h"
#include "Traits.h"
#include <matplot/matplot.h>

template<typename ColorTypeTrait>
class Histogram final
{
public:
    Histogram(const Image<ColorTypeTrait>& image)
        : sourceImage(image)
    {
        frequencyArray.fill(0);

        for (int i = 0; i < sourceImage.size; ++i) {
            auto pixel = sourceImage.data[i];
            frequencyArray[pixel]++;
        }
    }

    Histogram(const Histogram<ColorTypeTrait>& rhs)
        : sourceImage(rhs.sourceImage)
        , frequencyArray(rhs.frequencyArray)
    {
    }

    Histogram(Histogram<ColorTypeTrait>&& rhs) noexcept
        : sourceImage(std::move(rhs.sourceImage))
        , frequencyArray(std::move(rhs.frequencyArray))
    {
    }

    Image<ColorTypeTrait> generateEqualized()
    {
        Image<ColorTypeTrait> equalized(sourceImage);
        for (int i = 0; i < equalized.size; ++i) {
            auto pixel = equalized.data[i];
            equalized.data[i] = (double(ColorTypeTrait::max) / equalized.size) * getCumulativeFrequency(pixel);
        }
        return equalized;
    }

    Image<ColorTypeTrait> generateStretched()
    {
        Image<ColorTypeTrait> stretched(sourceImage);

        auto brightness = getMinMaxBrightness();
        auto minBrightness = brightness.first;
        auto maxBrightness = brightness.second;

        for (int i = 0; i < stretched.size; ++i) {
            ColorTypeTrait::codingType pixelValue = stretched.data[i];
            ColorTypeTrait::codingType stretchedValue = (double(ColorTypeTrait::max) * (pixelValue - minBrightness) / (maxBrightness - minBrightness));
            if (pixelValue != stretchedValue);
            stretched.data[i] = stretchedValue;
        }
        return stretched;
    }

    void show() const
    {
        std::array<int, ColorTypeTrait::bound> temp;
        for (int i = 0; i < temp.size(); ++i) {
            temp[i] = i;
        }
        matplot::stairs(temp, frequencyArray);
        matplot::show();
        return;
    }

private:
    using BrightnessFrequencyArray = std::array<int, ColorTypeTrait::bound>;
    std::pair<typename ColorTypeTrait::codingType, typename ColorTypeTrait::codingType> getMinMaxBrightness() const
    {
        int minValue = sourceImage.data[0];
        int maxValue = sourceImage.data[0];
        for (int i = 1; i < sourceImage.size; ++i) {
            ColorTypeTrait::codingType pixelValue = sourceImage.data[i];
            if (pixelValue < minValue) {
                minValue = pixelValue;
            }
            if (pixelValue > maxValue) {
                maxValue = pixelValue;
            }
        }
        return { minValue, maxValue };
    }

    int getCumulativeFrequency(int endBrightness) const
    {
        int result = 0;
        for (int brightness = 0; brightness <= endBrightness; ++brightness) {
            result += frequencyArray[brightness];
        }
        return result;
    }

private:
    BrightnessFrequencyArray frequencyArray;
    Image<ColorTypeTrait> sourceImage;
};
