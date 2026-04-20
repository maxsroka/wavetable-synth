#pragma once
#include <JuceHeader.h>

/*
	Generates samples and stores them in a buffer.
	Channel 0 -> sine wave
	Channel 1 -> square wave
*/
class Wavetable
{
public:
	// Initializes the buffer and fills it with samples.
	void generate();

	// Returns the sample at the given channel and index.
	// Call generate() before calling this method.
	float sample(int channel, int index) const;

	// Returns a reference to the internal buffer.
	juce::AudioSampleBuffer& getBuffer();
	
	// Number of samples per channel in the buffer.
	static constexpr int NUM_SAMPLES = 256;

	// Number of channels in the buffer.
	static constexpr int NUM_CHANNELS = 2;
private:
	juce::AudioSampleBuffer buffer;
};