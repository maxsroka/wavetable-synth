/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WavetableSynthAudioProcessorEditor::WavetableSynthAudioProcessorEditor(juce::AudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), valueTreeState(vts)
{
	setSize(500, 300);
	volumeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "volume", volumeSlider));
	addAndMakeVisible(volumeSlider);
	addAndMakeVisible(volumeSliderLabel);

	shapeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "shape", shapeSlider));
	addAndMakeVisible(shapeSlider);
	addAndMakeVisible(shapeSliderLabel);

	panAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pan", panSlider));
	addAndMakeVisible(panSlider);
	addAndMakeVisible(panSliderLabel);
}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(style.findColour(juce::ResizableWindow::backgroundColourId));
}

void WavetableSynthAudioProcessorEditor::resized()
{
	volumeSlider.setBounds(0, 20, 65, 65);
	volumeSliderLabel.setBoundsFromSlider(volumeSlider);

	shapeSlider.setBounds(80, 20, 65, 65);
	shapeSliderLabel.setBoundsFromSlider(shapeSlider);

	panSlider.setBounds(80 * 2, 20, 65, 65);
	panSliderLabel.setBoundsFromSlider(panSlider);
}