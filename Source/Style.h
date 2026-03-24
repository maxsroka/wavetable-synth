#pragma once

#include <JuceHeader.h>

class Style : public juce::LookAndFeel_V4
{
public:
	Style();
private:
	void setBackgroundColor();
	void setButtonColors();
	void setSliderColors();
	juce::Colour darkerColor = juce::Colour::fromRGB(51, 51, 51);
	juce::Colour darkColor = juce::Colour::fromRGB(67, 67, 67);
	juce::Colour lightColor = juce::Colour::fromRGB(87, 87, 87);
	juce::Colour lighterColor = juce::Colour::fromRGB(107, 107, 107);
};