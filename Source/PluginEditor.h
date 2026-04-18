/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DefaultStyle.h"
#include "DefaultSlider.h"
#include "DefaultSliderLabel.h"

//==============================================================================
/**
*/
class WavetableSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	WavetableSynthAudioProcessorEditor(juce::AudioProcessor&, juce::AudioProcessorValueTreeState&);
	~WavetableSynthAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;

private:
	DefaultStyle style;
	DefaultSlider volumeSlider{ style, 0.0, 1.0, 0.01 };
	DefaultSliderLabel volumeSliderLabel{ "Volume" };
	DefaultSlider shapeSlider{ style, 0.0, 1.0, 0.01 };
	DefaultSliderLabel shapeSliderLabel{ "Shape" };
	DefaultSlider panSlider{ style, -1.0, 1.0, 0.01 };
	DefaultSliderLabel panSliderLabel{ "Pan" };
	juce::AudioProcessorValueTreeState& valueTreeState;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> shapeAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthAudioProcessorEditor)
};
