#pragma once

#include <JuceHeader.h>

class DefaultStyle : public juce::LookAndFeel_V4
{
public:
	DefaultStyle();
private:
	void setBackgroundColor();
	void setButtonColors();
	void setSliderColors();
	juce::Colour accentColor = juce::Colour::fromRGB(133, 237, 111);
	juce::Colour darkerColor = juce::Colour::fromRGB(51, 51, 51);
	juce::Colour darkColor = juce::Colour::fromRGB(67, 67, 67);
	juce::Colour lightColor = juce::Colour::fromRGB(87, 87, 87);
	juce::Colour lighterColor = juce::Colour::fromRGB(107, 107, 107);
};