#include "Oscillator.h"
#include <JuceHeader.h>

void Oscillator::setup(Wavetable* wavetable, double sampleRate)
{
	jassert(wavetable != nullptr);
	jassert(sampleRate > 0);

	this->wavetable = wavetable;
	this->sampleRate = sampleRate;
}

void Oscillator::setFrequency(double frequency)
{
	jassert(sampleRate > 0);

	this->frequency = frequency;
	angleDelta = frequency * (static_cast<double>(Wavetable::NUM_SAMPLES) / sampleRate);
}

float Oscillator::getNextSample(float shape)
{
	int indexA = static_cast<int>(angle);
	int indexB = (indexA + 1) % Wavetable::NUM_SAMPLES;

	float sampleA0 = wavetable->sample(0, indexA);
	float sampleA1 = wavetable->sample(1, indexA);

	float sampleB0 = wavetable->sample(0, indexB);
	float sampleB1 = wavetable->sample(1, indexB);

	float sampleA = std::lerp(sampleA0, sampleA1, shape);
	float sampleB = std::lerp(sampleB0, sampleB1, shape);

	float frac = angle - indexA;
	float sampleAB = std::lerp(sampleA, sampleB, frac);

	angle += angleDelta;
	if (angle >= Wavetable::NUM_SAMPLES)
	{
		angle -= Wavetable::NUM_SAMPLES;
	}

	return sampleAB;
}

bool Oscillator::isActive() const
{
	return frequency > 0.0;
}

Oscillator* Oscillator::findInactive(std::vector<Oscillator>& oscillators)
{
	for (Oscillator& oscillator : oscillators)
	{
		if (oscillator.isActive()) continue;

		return &oscillator;
	}

	return nullptr;
}