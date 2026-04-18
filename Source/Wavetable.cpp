#include "Wavetable.h"

void Wavetable::generate()
{
	buffer.setSize(NUM_CHANNELS, NUM_SAMPLES);
	
	double angle = 0.0;
	double angleDelta = juce::MathConstants<double>::twoPi / (double)(NUM_SAMPLES - 1);

	for (int i = 0; i < NUM_SAMPLES; ++i)
	{
		float sineSample = std::sin(angle);
		buffer.setSample(0, i, sineSample);

		float squareSample = sineSample > 0.0f ? 1.0f : -1.0f;
		buffer.setSample(1, i, squareSample);

		angle += angleDelta;
	}
}

float Wavetable::sample(int channel, int index) const
{
	jassert(channel >= 0 && channel < buffer.getNumChannels());
	jassert(index >= 0 && index < buffer.getNumSamples());

	return buffer.getSample(channel, index);
}