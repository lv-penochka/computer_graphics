#pragma once
#include <array>
#include "image.h"
#include "Traits.h"
#include <matplot/matplot.h>

class Histogram final
{
public:
    Histogram(const Image& image);
    Histogram(const Histogram& rhs);
    Histogram(Histogram&& rhs) noexcept;

    Image generateEqualized();
    Image generateStretched();

    void show() const;

private:
    using BrightnessFrequencyArray = std::array<int, 256>;    
    
    std::pair<uint8_t, uint8_t> getMinMaxBrightness() const;
    int getCumulativeFrequency(int endBrightness) const;

private:
    BrightnessFrequencyArray frequencyArray;
    Image sourceImage;
};
