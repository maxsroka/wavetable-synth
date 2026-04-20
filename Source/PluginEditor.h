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
class WavetableSynthAudioProcessorEditor : public juce::AudioProcessorEditor,
	public juce::AudioProcessorValueTreeState::Listener
{
public:
	WavetableSynthAudioProcessorEditor(juce::AudioProcessor&, juce::AudioProcessorValueTreeState&);
	~WavetableSynthAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;
	void parameterChanged(const juce::String& parameterID, float newValue) override;
private:
	DefaultStyle style;

	juce::AudioProcessorValueTreeState& valueTreeState;

	std::array<DefaultSlider, 5> sliders{
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "volume" },
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "shape" },
		DefaultSlider{ style, -1.0, 1.0, 0.01, valueTreeState, "pan" },
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "fadeIn" },
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "fadeOut" }
	};

	std::array<DefaultSliderLabel, 5> sliderLabels{
		DefaultSliderLabel{ "Volume" },
		DefaultSliderLabel{ "Shape" },
		DefaultSliderLabel{ "Pan" },
		DefaultSliderLabel{ "Fade In" },
		DefaultSliderLabel{ "Fade Out" }
	};

	void addSliderWithLabel(DefaultSlider& slider, DefaultSliderLabel& label);
	void resizeSliderWithLabel(DefaultSlider& slider, DefaultSliderLabel& label, int index);

	Wavetable& getWavetable();
	void drawWavetable(juce::Graphics& g);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthAudioProcessorEditor)
};
