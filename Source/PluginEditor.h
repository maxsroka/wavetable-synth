#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "DefaultStyle.h"
#include "DefaultSlider.h"
#include "DefaultSliderLabel.h"
#include "WavetableDisplay.h"

class WavetableSynthAudioProcessorEditor : public juce::AudioProcessorEditor,
	public juce::AudioProcessorValueTreeState::Listener
{
public:
	WavetableSynthAudioProcessorEditor(juce::AudioProcessor&, juce::AudioProcessorValueTreeState&);
	~WavetableSynthAudioProcessorEditor() override;

	void paint(juce::Graphics&) override;
	void resized() override;
	void parameterChanged(const juce::String& parameterID, float newValue) override;
private:
	DefaultStyle style;

	juce::AudioProcessorValueTreeState& valueTreeState;

	std::array<DefaultSlider, 5> sliders{
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "volume", "Volume"},
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "shape", "Shape"},
		DefaultSlider{ style, -1.0, 1.0, 0.01, valueTreeState, "pan", "Pan"},
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "fadeIn", "Fade In"},
		DefaultSlider{ style, 0.0, 1.0, 0.01, valueTreeState, "fadeOut", "Fade Out"}
	};

	Wavetable& getWavetable();
	WavetableDisplay wavetableDisplay{style, getWavetable(), valueTreeState};

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthAudioProcessorEditor)
};
