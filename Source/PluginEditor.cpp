/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WavetableSynthAudioProcessorEditor::WavetableSynthAudioProcessorEditor(juce::AudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), valueTreeState(vts), thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache)
{
	setSize(500, 300);
	
	volumeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "volume", volumeSlider));
	addAndMakeVisible(volumeSlider);
	addAndMakeVisible(volumeSliderLabel);

	shapeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "shape", shapeSlider));
	valueTreeState.addParameterListener("shape", this);
	addAndMakeVisible(shapeSlider);
	addAndMakeVisible(shapeSliderLabel);

	panAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pan", panSlider));
	addAndMakeVisible(panSlider);
	addAndMakeVisible(panSliderLabel);

	auto* wsap = dynamic_cast<WavetableSynthAudioProcessor*>(&processor);
	juce::AudioSampleBuffer* buffer = &wsap->getWavetable().getBuffer();
	thumbnail.setSource(buffer, 1, 0);
}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{
	valueTreeState.removeParameterListener("shape", this);
}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(style.findColour(juce::ResizableWindow::backgroundColourId));

	juce::Rectangle<int> thumbnailBounds(10, 100, getWidth() - 20, getHeight() - 120);
	g.setColour(juce::Colour::fromRGB(67, 67, 67));
	g.fillRect(thumbnailBounds);
	g.setColour(juce::Colour::fromRGB(133, 237, 111));
	thumbnail.drawChannel(g,
		thumbnailBounds,
		0.0,
		thumbnail.getTotalLength(),
		0,
		1.0f);
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

void WavetableSynthAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
	
}