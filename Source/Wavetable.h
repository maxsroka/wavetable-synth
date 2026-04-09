#pragma once
#include <JuceHeader.h>

class Wavetable 
{
public:
	Wavetable() {}
	void generate();
	int getSize() const;
	float sample(int channel, int index) const;
private:
	juce::AudioSampleBuffer buffer;
};