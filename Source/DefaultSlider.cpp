#include "DefaultSlider.h"
#include "DefaultStyle.h"

DefaultSlider::DefaultSlider(DefaultStyle& style, double rangeMin, double rangeMax, double interval, juce::AudioProcessorValueTreeState& valueTreeState, const juce::String& parameterID, const juce::String& displayName)
	: label(displayName)
{
	this->setRange(rangeMin, rangeMax, interval);
	this->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	this->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 16);
	this->setLookAndFeel(&style);

	attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, parameterID, *this));
}

DefaultSliderLabel& DefaultSlider::getLabel()
{
	return label;
}