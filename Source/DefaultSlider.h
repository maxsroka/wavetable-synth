#pragma once

#include <JuceHeader.h>
#include "Style.h"

class DefaultSlider : public juce::Component
{
public:
	DefaultSlider(Style& style, std::string text, double rangeMin, double rangeMax, double interval);
private:
	juce::Slider slider;
	juce::Label label;
	void resized() override;
};