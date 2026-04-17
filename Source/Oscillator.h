#pragma once
#include "Wavetable.h"

class Oscillator
{
public:
	Oscillator() {};
	void setSampleRate(double sampleRate);
	void setFrequency(double frequency);
	void setWavetable(Wavetable* wavetable);
	float getNextSample(float shape);
	bool isActive = false;
private:
	double angle = 0.0;
	double angleDelta = 0.0;
	double frequency = 0.0;
	int sampleRate = 0;
	Wavetable* wavetable = nullptr;
};