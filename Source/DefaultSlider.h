#pragma once

#include <JuceHeader.h>
#include "Style.h"

class DefaultSlider : public juce::Slider
{
public:
	DefaultSlider(Style& style, double rangeMin, double rangeMax, double interval);
	bool operator==(juce::Slider* slider);
};