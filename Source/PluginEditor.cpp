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
		addSliderWithLabel(sliders[i], sliderLabels[i]);
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
		resizeSliderWithLabel(sliders[i], sliderLabels[i], i);
	}

	wavetableDisplay.setBounds(10, 100, getWidth() - 20, getHeight() - 120);
}

void WavetableSynthAudioProcessorEditor::addSliderWithLabel(DefaultSlider& slider, DefaultSliderLabel& label)
{
	addAndMakeVisible(slider);
	addAndMakeVisible(label);
}

void WavetableSynthAudioProcessorEditor::resizeSliderWithLabel(DefaultSlider& slider, DefaultSliderLabel& label, int index)
{
	constexpr int sliderX = 80;
	constexpr int sliderY = 20;
	constexpr int sliderH = 65;
	constexpr int sliderW = 65;

	slider.setBounds(sliderX * index, sliderY, sliderW, sliderH);
	label.setBoundsFromSlider(slider);
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