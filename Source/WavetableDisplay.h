#pragma once
#include <JuceHeader.h>
#include "Wavetable.h"
#include "DefaultStyle.h"

/*
	A component that displays a wavetable.
*/
class WavetableDisplay : public juce::Component
{
public:
	// Initializes the display with its dependencies.
	WavetableDisplay(DefaultStyle& style, Wavetable& wavetable, juce::AudioProcessorValueTreeState& valueTreeState);
	
	// Draws the background and the lines.
	void paint(juce::Graphics& g) override;
	
	// The thickness of the lines drawn.
	constexpr static float LINE_THICKNESS = 1.0f;
	
	// The X position of the display.
	constexpr static int DISPLAY_X = 10;

	// The Y position of the display.
	constexpr static int DISPLAY_Y = 100;

	// The right margin of the display.
	constexpr static int DISPLAY_X_MARGIN = 20;

	// The bottom margin of the display.
	constexpr static int DISPLAY_Y_MARGIN = 120;
private:
	DefaultStyle& style;
	Wavetable& wavetable;
	juce::AudioProcessorValueTreeState& valueTreeState;
	juce::AudioSampleBuffer* buffer;

	void drawBackground(juce::Graphics& g);
	void drawLines(juce::Graphics& g);
};