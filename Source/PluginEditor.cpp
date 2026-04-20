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

	for (int i = 0; i < sliders.size(); ++i)
	{
		auto& slider = sliders[i];

		addAndMakeVisible(slider);
		addAndMakeVisible(slider.getLabel());
	}

	valueTreeState.addParameterListener("shape", this);
	
	addAndMakeVisible(wavetableDisplay);
}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{
	valueTreeState.removeParameterListener("shape", this);
}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(style.findColour(juce::ResizableWindow::backgroundColourId));
}

void WavetableSynthAudioProcessorEditor::resized()
{
	for (int i = 0; i < sliders.size(); ++i)
	{
		auto& slider = sliders[i];
		auto& label = slider.getLabel();

		slider.setBounds(DefaultSlider::SLIDER_X * i, DefaultSlider::SLIDER_Y, DefaultSlider::SLIDER_W, DefaultSlider::SLIDER_H);
		label.setBoundsFromSlider(slider);
	}

	wavetableDisplay.setBounds(10, 100, getWidth() - 20, getHeight() - 120);
}

void WavetableSynthAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
	if (parameterID == "shape")
	{
		const juce::MessageManagerLock mmLock;
		repaint();
	}
}

Wavetable& WavetableSynthAudioProcessorEditor::getWavetable()
{
	auto* wsap = dynamic_cast<WavetableSynthAudioProcessor*>(&processor);
	Wavetable& wavetable = wsap->getWavetable();

	return wavetable;
}