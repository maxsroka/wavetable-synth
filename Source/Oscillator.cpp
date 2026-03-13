#include "Oscillator.h"
#include <JuceHeader.h>

void Oscillator::setWavetable(Wavetable* wavetable)
{
	this->wavetable = wavetable;
}

void Oscillator::setSampleRate(double sampleRate)
{
	this->sampleRate = sampleRate;
}

void Oscillator::setFrequency(double frequency)
{
	this->frequency = frequency;

	angleDelta = frequency * ((double)wavetable->getSize() / (double)sampleRate);
}

float Oscillator::getNextSample()
{
	int wavetableSize = wavetable->getSize();
	int index = (int)(angle);
	float sample = wavetable->sample(index);

	angle += angleDelta;
	if (angle >= wavetableSize)
	{
		angle -= wavetableSize;
	}

	return sample;
}