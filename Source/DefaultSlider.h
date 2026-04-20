#pragma once
#include <JuceHeader.h>
#include "DefaultStyle.h"
#include "DefaultSliderLabel.h"

/*
	A standard rotary slider used by the plugin.
*/
class DefaultSlider : public juce::Slider
{
public:
	// Creates a slider with the given style, range, value tree state, parameter ID and display name.
	DefaultSlider(DefaultStyle& style, double rangeMin, double rangeMax, double interval, juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& parameterID, const juce::String& displayName);
	
	// Returns the internal DefaultSliderLabel.
	DefaultSliderLabel& getLabel();

	// The X position of the slider.
	constexpr static int SLIDER_X = 80;
	
	// The Y position of the slider.
	constexpr static int SLIDER_Y = 20;
	
	// The height of the slider.
	constexpr static int SLIDER_H = 65;
	
	// The width of the slider.
	constexpr static int SLIDER_W = 65;
private:
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
	DefaultSliderLabel label;
};