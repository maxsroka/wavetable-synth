#pragma once
#include <JuceHeader.h>

class Wavetable 
{
public:
	void generate();
	float sample(int channel, int index) const;
	static constexpr int NUM_SAMPLES = 32;
	static constexpr int NUM_CHANNELS = 2;
private:
	juce::AudioSampleBuffer buffer;
};