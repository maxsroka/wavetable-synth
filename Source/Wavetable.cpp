#include "Wavetable.h"

void Wavetable::generate()
{
	int size = 128;
	buffer.setSize(1, size);
	float* ptr = buffer.getWritePointer(0);
	
	double angle = 0.0;
	double angleDelta = juce::MathConstants<double>::twoPi / (double)(size - 1);

	for (int i = 0; i < size; ++i)
	{
		float sample = std::sin(angle);
		ptr[i] = sample;

		angle += angleDelta;
	}
}