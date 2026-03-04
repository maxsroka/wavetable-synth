#include "Oscillator.h"
#include <JuceHeader.h>

void Oscillator::setSampleRate(double sampleRate)
{
	this->sampleRate = sampleRate;
}

void Oscillator::setFrequency(double frequency)
{
	angleDelta = (frequency / sampleRate) * juce::MathConstants<double>::twoPi;
}

float Oscillator::getNextSample()
{
	float sample = std::sin(angle);

	angle += angleDelta;
	if (angle >= juce::MathConstants<double>::twoPi)
	{
		angle -= juce::MathConstants<double>::twoPi;
	}

	return sample;
}