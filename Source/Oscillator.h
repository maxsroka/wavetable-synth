#pragma once
#include "Wavetable.h"

class Oscillator
{
public:
	Oscillator() {};
	void setup(Wavetable* wavetable, double sampleRate);
	void setFrequency(double frequency);
	float getNextSample(float shape);
	bool isActive() const;

	static Oscillator* findInactive(std::vector<Oscillator>& oscillators);
private:
	double angle = 0.0;
	double angleDelta = 0.0;
	double frequency = 0.0;
	int sampleRate = 0;
	Wavetable* wavetable = nullptr;
};