#pragma once
#include <JuceHeader.h>

class DefaultSlider;

/*
	A label used with the DefaultSlider component.
*/
class DefaultSliderLabel : public juce::Label
{
public:
	// Initializes the label with the given text.
	DefaultSliderLabel(juce::String text);

	// Places the label above the given slider.
	// This method places the label in a slightly different position compared to the JUCE's attachToComponent().
	void setBoundsFromSlider(DefaultSlider& slider);
};