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

	setupAttachments();
	setupThumbnail();
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
		1.0,
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

void WavetableSynthAudioProcessorEditor::setupAttachments()
{
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
}

void WavetableSynthAudioProcessorEditor::parameterChanged(const juce::String& parameterID, float newValue)
{
	if (parameterID == "shape")
	{
		reloadThumbnail(newValue);
	}
}

void WavetableSynthAudioProcessorEditor::setupThumbnail()
{
	thumbnail.addChangeListener(this);
	displayBuffer.setSize(1, Wavetable::NUM_SAMPLES);
	float shape = valueTreeState.getParameter("shape")->getValue();
	reloadThumbnail(shape);
}

// a temporary solution for real-time thumbnail updates
// this feature would be more efficient by avoiding the use of juce::AudioThumbnail
void WavetableSynthAudioProcessorEditor::reloadThumbnail(float shapeParameter)
{
	if (isReloadingThumbnail) return;
	isReloadingThumbnail = true;

	auto* wsap = dynamic_cast<WavetableSynthAudioProcessor*>(&processor);
	juce::AudioSampleBuffer* wavetableBuffer = &wsap->getWavetable().getBuffer();

	for (int i = 0; i < Wavetable::NUM_SAMPLES; ++i)
	{
		float sampleA = wavetableBuffer->getSample(0, i);
		float sampleB = wavetableBuffer->getSample(1, i);
		float sampleAB = std::lerp(sampleA, sampleB, shapeParameter);

		displayBuffer.setSample(0, i, sampleAB);
	}

	thumbnail.setSource(&displayBuffer, 1, 0);
}

void WavetableSynthAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
	if (source == &thumbnail)
	{
		repaint();
		isReloadingThumbnail = false;
	}
}