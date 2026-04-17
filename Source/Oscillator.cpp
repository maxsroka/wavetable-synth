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

float Oscillator::getNextSample(float shape)
{
	int wavetableSize = wavetable->getSize();
	int indexA = (int)(angle);
	int indexB = (indexA + 1) % wavetableSize;
	float sampleA0 = wavetable->sample(0, indexA);
	float sampleA1 = wavetable->sample(1, indexA);
	float sampleB0 = wavetable->sample(0, indexB);
	float sampleB1 = wavetable->sample(1, indexB);
	float sampleA = std::lerp(sampleA0, sampleA1, shape);
	float sampleB = std::lerp(sampleB0, sampleB1, shape);
	float frac = angle - indexA;
	float sampleAB = sampleA + (sampleB - sampleA) * frac;
	
	angle += angleDelta;
	if (angle >= wavetableSize)
	{
		angle -= wavetableSize;
	}

	return sampleAB;
}

bool Oscillator::getIsActive() const
{
	return isActive;
}

void Oscillator::setActive(bool isActive)
{
	this->isActive = isActive;
}