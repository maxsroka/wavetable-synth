#include "DefaultSlider.h"
#include "Style.h"

DefaultSlider::DefaultSlider(Style& style, double rangeMin, double rangeMax, double interval)
{
    this->setRange(rangeMin, rangeMax, interval);
    this->setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    this->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 16);
    this->setLookAndFeel(&style);
}

bool DefaultSlider::operator==(juce::Slider* slider)
{
    return slider->getComponentID() == this->getComponentID();
}