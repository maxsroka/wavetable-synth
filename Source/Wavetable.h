#pragma once
#include <JuceHeader.h>

class Wavetable 
{
public:
	Wavetable() {}
	void generate();
	int getSize();
	float sample(int channel, int index);
private:
	juce::AudioSampleBuffer buffer;
};