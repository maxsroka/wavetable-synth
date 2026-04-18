#include "DefaultStyle.h"

DefaultStyle::DefaultStyle()
{
	setBackgroundColor();
	setButtonColors();
	setSliderColors();
}

void DefaultStyle::setBackgroundColor()
{
	setColour(juce::ResizableWindow::backgroundColourId, darkerColor);
}

void DefaultStyle::setButtonColors()
{
	setColour(juce::TextButton::buttonColourId, darkColor);
	setColour(juce::ComboBox::outlineColourId, lightColor);
}

void DefaultStyle::setSliderColors()
{
	setColour(juce::Slider::backgroundColourId, darkColor);
	setColour(juce::Slider::rotarySliderFillColourId, lightColor);
	setColour(juce::Slider::rotarySliderOutlineColourId, darkColor);
	setColour(juce::Slider::thumbColourId, accentColor);
	setColour(juce::Slider::textBoxBackgroundColourId, darkColor);
	setColour(juce::Slider::textBoxOutlineColourId, lightColor);
	setColour(juce::Slider::textBoxHighlightColourId, lighterColor);
}