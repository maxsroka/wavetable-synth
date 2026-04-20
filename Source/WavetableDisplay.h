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
	constexpr static int DISPLAY_X = 10;
	constexpr static int DISPLAY_Y = 100;
	constexpr static int DISPLAY_W_MARGIN = 20;
	constexpr static int DISPLAY_H_MARGIN = 120;
private:
	DefaultStyle& style;
	Wavetable& wavetable;
	juce::AudioProcessorValueTreeState& valueTreeState;
};