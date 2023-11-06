#pragma once
#include <array>
#include "image.h"

namespace ImageTransformation
{

class Histogram final
{
public:
    using BrightnessFrequencyArray = std::array<int, 256>;

    Histogram(const Image& image);
    Histogram(const Histogram& rhs);
    Histogram(Histogram&& rhs) noexcept;
    ~Histogram() noexcept = default;

    Histogram& operator=(const Histogram& rhs) = delete;
    Histogram& operator=(Histogram&& rhs) noexcept = delete;
    Histogram& operator=(const Image& image) = delete;

    Image generateEqualized();
    Image generateStretched();

    void show() const;

private:
    std::pair<uint8_t, uint8_t> getMinMaxBrightness() const;
    int getCumulativeFrequency(int stopBrightnessIndex) const;

private:
    BrightnessFrequencyArray frequencyArray;
    Image sourceImage;
};

} // namespace ImageTransformation