#include "Style.h"

Style::Style()
{
	setBackgroundColor();
	setButtonColors();
	setSliderColors();
}

void Style::setBackgroundColor()
{
	setColour(juce::ResizableWindow::backgroundColourId, darkerColor);
}

void Style::setButtonColors()
{
	setColour(juce::TextButton::buttonColourId, darkColor);
	setColour(juce::ComboBox::outlineColourId, lightColor);
}

void Style::setSliderColors()
{
	setColour(juce::Slider::backgroundColourId, darkColor);
	setColour(juce::Slider::rotarySliderFillColourId, lightColor);
	setColour(juce::Slider::rotarySliderOutlineColourId, darkColor);
	setColour(juce::Slider::thumbColourId, lighterColor);
	setColour(juce::Slider::textBoxBackgroundColourId, darkColor);
	setColour(juce::Slider::textBoxOutlineColourId, lightColor);
	setColour(juce::Slider::textBoxHighlightColourId, lighterColor);
}