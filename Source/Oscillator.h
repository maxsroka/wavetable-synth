#pragma once

class Oscillator
{
public:
	Oscillator() {};
	void setSampleRate(double sampleRate);
	void setFrequency(double frequency);
	float getNextSample();
private:
	double angle = 0.0;
	double angleDelta = 0.0;
	int sampleRate = 0;
};