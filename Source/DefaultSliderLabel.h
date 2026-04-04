#pragma once

#include <JuceHeader.h>
#include "DefaultSlider.h"

class DefaultSliderLabel : public juce::Label
{
public:
	DefaultSliderLabel(juce::String text);
	void setBoundsFromSlider(DefaultSlider& slider);
};