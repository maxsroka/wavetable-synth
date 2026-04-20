#pragma once
#include <JuceHeader.h>

class DefaultSlider;

class DefaultSliderLabel : public juce::Label
{
public:
	DefaultSliderLabel(juce::String text);
	void setBoundsFromSlider(DefaultSlider& slider);
};