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

        auto redBrightness = getMinMaxBrightness(RED);
        auto redMinBrightness = redBrightness.first;
        auto redMaxBrightness = redBrightness.second;

        for (int i = 0; i < stretched.size; i+=3) {
            ColorTypeTrait::codingType pixelValue = stretched.data[i];
            ColorTypeTrait::codingType stretchedValue = 
                (double(ColorTypeTrait::max) * (pixelValue - redMinBrightness) / (redMaxBrightness - redMinBrightness));
            if (pixelValue != stretchedValue)
                stretched.data[i] = stretchedValue;
        }

        auto greenBrightness = getMinMaxBrightness(GREEN);
        auto greenMinBrightness = greenBrightness.first;
        auto greenMaxBrightness = greenBrightness.second;

        for (int i = 1; i < stretched.size; i += 3) {
            ColorTypeTrait::codingType pixelValue = stretched.data[i];
            ColorTypeTrait::codingType stretchedValue = 
                (double(ColorTypeTrait::max) * (pixelValue - greenMinBrightness) / (greenMaxBrightness - greenMinBrightness));
            if (pixelValue != stretchedValue)
                stretched.data[i] = stretchedValue;
        }
        auto blueBrightness = getMinMaxBrightness(BLUE);
        auto blueMinBrightness = blueBrightness.first;
        auto blueMaxBrightness = blueBrightness.second;

        for (int i = 2; i < stretched.size; i += 3) {
            ColorTypeTrait::codingType pixelValue = stretched.data[i];
            ColorTypeTrait::codingType stretchedValue = 
                (double(ColorTypeTrait::max) * (pixelValue - blueMinBrightness) / (blueMaxBrightness - blueMinBrightness));
            if (pixelValue != stretchedValue)
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
    
    enum Color {
        RED = 0,
        GREEN,
        BLUE,
        ALPHA
    };
    
    std::pair<typename ColorTypeTrait::codingType, typename ColorTypeTrait::codingType> getMinMaxBrightness(Color c) const
    {
        int minValue;
        int maxValue;
        int i;
        switch (c) {
        case RED: {
            minValue = sourceImage.data[0];
            maxValue = sourceImage.data[0];
            i = 1;
        } break;
        case GREEN: {
            minValue = sourceImage.data[1];
            maxValue = sourceImage.data[1];
            i = 2;
        } break;
        case BLUE: {
            minValue = sourceImage.data[2];
            maxValue = sourceImage.data[2];
            i = 3;
        } break;
        case ALPHA: {
            minValue = sourceImage.data[3];
            maxValue = sourceImage.data[3];
            i = 4;
        }
        }
        
        //std::cout << sourceImage.numberChannels << std::endl;
        auto increment = sourceImage.numberChannels == 4
            ? 4
            : 3;

        for (; i < sourceImage.size; i+=increment) {
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
