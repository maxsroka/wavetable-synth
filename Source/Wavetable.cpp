#include "Wavetable.h"

void Wavetable::generate()
{
	int size = 32;
	buffer.setSize(2, size);
	
	double angle = 0.0;
	double angleDelta = juce::MathConstants<double>::twoPi / (double)(size - 1);

	for (int i = 0; i < size; ++i)
	{
		float sineSample = std::sin(angle);
		buffer.setSample(0, i, sineSample);

		float squareSample = sineSample > 0.0f ? 1.0f : -1.0f;
		buffer.setSample(1, i, squareSample);

		angle += angleDelta;
	}
}

int Wavetable::getSize() const
{
	return buffer.getNumSamples();
}

float Wavetable::sample(int channel, int index) const
{
	return buffer.getSample(channel, index);
}