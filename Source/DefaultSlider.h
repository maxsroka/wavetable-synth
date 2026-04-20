#pragma once

#include <JuceHeader.h>
#include "DefaultStyle.h"

class DefaultSlider : public juce::Slider
{
public:
	DefaultSlider(DefaultStyle& style, double rangeMin, double rangeMax, double interval, juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& parameterID);
	bool operator==(juce::Slider* slider);
private:
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
};