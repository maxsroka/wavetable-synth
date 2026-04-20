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

	setupSliderWithLabel(volumeAttachment, "volume", volumeSlider, volumeSliderLabel);
	setupSliderWithLabel(shapeAttachment, "shape", shapeSlider, shapeSliderLabel);
	setupSliderWithLabel(panAttachment, "pan", panSlider, panSliderLabel);
	setupSliderWithLabel(fadeInAttachment, "fadeIn", fadeInSlider, fadeInSliderLabel);
	setupSliderWithLabel(fadeOutAttachment, "fadeOut", fadeOutSlider, fadeOutSliderLabel);
	
	valueTreeState.addParameterListener("shape", this);
}

WavetableSynthAudioProcessorEditor::~WavetableSynthAudioProcessorEditor()
{
	valueTreeState.removeParameterListener("shape", this);
}

//==============================================================================
void WavetableSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(style.findColour(juce::ResizableWindow::backgroundColourId));

	drawWavetable(g);
}

void WavetableSynthAudioProcessorEditor::resized()
{
	resizeSliderWithLabel(volumeSlider, volumeSliderLabel, 0);
	resizeSliderWithLabel(shapeSlider, shapeSliderLabel, 1);
	resizeSliderWithLabel(panSlider, panSliderLabel, 2);
	resizeSliderWithLabel(fadeInSlider, fadeInSliderLabel, 3);
	resizeSliderWithLabel(fadeOutSlider, fadeOutSliderLabel, 4);
}

void WavetableSynthAudioProcessorEditor::setupSliderWithLabel(std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, const juce::String& parameterID, DefaultSlider& slider, DefaultSliderLabel& label)
{
	attachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(valueTreeState, parameterID, slider));
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

void WavetableSynthAudioProcessorEditor::drawWavetable(juce::Graphics& g)
{
	juce::Rectangle<int> thumbnailBounds(10, 100, getWidth() - 20, getHeight() - 120);
	g.setColour(juce::Colour::fromRGB(67, 67, 67));
	g.fillRect(thumbnailBounds);
	g.setColour(juce::Colour::fromRGB(133, 237, 111));

	auto* wsap = dynamic_cast<WavetableSynthAudioProcessor*>(&processor);
	juce::AudioSampleBuffer* buffer = &wsap->getWavetable().getBuffer();
	float shape = valueTreeState.getParameter("shape")->getValue();

	// i starts as two to avoid out-of-bounds access and to skip drawing the first sample
	for (int i = 2; i < Wavetable::NUM_SAMPLES; ++i)
	{
		float sampleA = buffer->getSample(0, i - 1);
		float sampleB = buffer->getSample(0, i);
		float sampleC = buffer->getSample(1, i - 1);
		float sampleD = buffer->getSample(1, i);

		float sampleAC = std::lerp(sampleA, sampleC, shape);
		float sampleBD = std::lerp(sampleB, sampleD, shape);

		float x1 = thumbnailBounds.getX() + ((i - 1) / static_cast<float>(Wavetable::NUM_SAMPLES)) * thumbnailBounds.getWidth();
		float x2 = thumbnailBounds.getX() + (i / static_cast<float>(Wavetable::NUM_SAMPLES)) * thumbnailBounds.getWidth();
		float y1 = thumbnailBounds.getCentreY() - sampleAC * thumbnailBounds.getHeight() / 2;
		float y2 = thumbnailBounds.getCentreY() - sampleBD * thumbnailBounds.getHeight() / 2;

		g.drawLine(
			x1,
			y1,
			x2,
			y2,
			1.0f
		);
	}
}