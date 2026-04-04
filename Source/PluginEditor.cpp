/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WavetableSynthAudioProcessorEditor::WavetableSynthAudioProcessorEditor (WavetableSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 300);
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(volumeSliderLabel);
    juce::Logger::getCurrentLogger()->writeToLog("hello");
}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{
}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (style.findColour (juce::ResizableWindow::backgroundColourId));
}

void WavetableSynthAudioProcessorEditor::resized()
{
    volumeSlider.setBounds(0, 20, 65, 65);
    volumeSliderLabel.setBoundsFromSlider(volumeSlider);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

}

void WavetableSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    juce::Logger::getCurrentLogger()->writeToLog("slider changed");

    if (volumeSlider == slider)
    {
        juce::Logger::getCurrentLogger()->writeToLog(std::to_string(slider->getValue()));
        audioProcessor.volume = ((float)slider->getValue());
    }
}