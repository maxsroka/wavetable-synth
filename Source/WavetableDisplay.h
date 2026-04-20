#pragma once
#include <JuceHeader.h>
#include "Wavetable.h"
#include "DefaultStyle.h"

class WavetableDisplay : public juce::Component
{
public:
	WavetableDisplay(DefaultStyle& style, Wavetable& wavetable, juce::AudioProcessorValueTreeState& valueTreeState) 
		: style(style), wavetable(wavetable), valueTreeState(valueTreeState) {}
	void paint(juce::Graphics& g) override;
	
	constexpr static float LINE_THICKNESS = 1.0f;
private:
	DefaultStyle& style;
	Wavetable& wavetable;
	juce::AudioProcessorValueTreeState& valueTreeState;
};