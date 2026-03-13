#pragma once
#include <JuceHeader.h>

class Wavetable 
{
public:
	Wavetable() {}
	void generate();
private:
	juce::AudioSampleBuffer buffer;
};