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
	int indexA = (int)(angle);
	int indexB = (indexA + 1) % wavetableSize;
	float sampleA = wavetable->sample(0, indexA);
	float sampleB = wavetable->sample(0, indexB);
	float frac = angle - indexA;
	float sampleAB = sampleA + (sampleB - sampleA) * frac;

	angle += angleDelta;
	if (angle >= wavetableSize)
	{
		angle -= wavetableSize;
	}

	return sampleAB;
}