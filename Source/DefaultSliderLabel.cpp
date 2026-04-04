#include "DefaultSliderLabel.h"
#include "DefaultSlider.h"

DefaultSliderLabel::DefaultSliderLabel(juce::String text)
{
    setText(text, juce::dontSendNotification);
    setJustificationType(juce::Justification::centred);
}

void DefaultSliderLabel::setBoundsFromSlider(DefaultSlider& slider)
{
    auto bounds = slider.getBounds();
    int y = bounds.getY();
    bounds.setY(y - 10);
    bounds.setHeight(15);
    this->setBounds(bounds);
}