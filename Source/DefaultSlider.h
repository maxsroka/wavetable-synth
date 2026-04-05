#pragma once

#include <JuceHeader.h>
#include "DefaultStyle.h"

class DefaultSlider : public juce::Slider
{
public:
	DefaultSlider(DefaultStyle& style, double rangeMin, double rangeMax, double interval);
	bool operator==(juce::Slider* slider);
};