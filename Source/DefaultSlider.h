#pragma once
#include <JuceHeader.h>
#include "DefaultStyle.h"
#include "DefaultSliderLabel.h"

class DefaultSlider : public juce::Slider
{
public:
	DefaultSlider(DefaultStyle& style, double rangeMin, double rangeMax, double interval, juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& parameterID, const juce::String& displayName);
	DefaultSliderLabel& getLabel();
	bool operator==(juce::Slider* slider);

	constexpr static int SLIDER_X = 80;
	constexpr static int SLIDER_Y = 20;
	constexpr static int SLIDER_H = 65;
	constexpr static int SLIDER_W = 65;
private:
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	DefaultSliderLabel label;
};