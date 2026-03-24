#include "DefaultSlider.h"
#include "Style.h"

DefaultSlider::DefaultSlider(Style& style, std::string text, double rangeMin, double rangeMax, double interval)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);

    slider.setRange(rangeMin, rangeMax, interval);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 16);
    slider.setLookAndFeel(&style);

    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
}

void DefaultSlider::resized()
{
    slider.setBounds(0, 20, 65, 65);
    label.setBounds(0, 5, 60, 20);
}