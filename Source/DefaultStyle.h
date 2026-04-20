#pragma once
#include <JuceHeader.h>

/*
	Exposes a set of colors to be used and sets the colors of internal JUCE components.
*/
class DefaultStyle : public juce::LookAndFeel_V4
{
public:
	DefaultStyle();

	const juce::Colour accentColor = juce::Colour::fromRGB(133, 237, 111);
	const juce::Colour darkerColor = juce::Colour::fromRGB(51, 51, 51);
	const juce::Colour darkColor = juce::Colour::fromRGB(67, 67, 67);
	const juce::Colour lightColor = juce::Colour::fromRGB(87, 87, 87);
	const juce::Colour lighterColor = juce::Colour::fromRGB(107, 107, 107);
private:
	void setBackgroundColor();
	void setButtonColors();
	void setSliderColors();
};