#pragma once
#include "Wavetable.h"

/*
	Generates audio samples using a wavetable and a specified frequency.
	Call setup() and setFrequency() before calling getNextSample().
*/
class Oscillator
{
public:
	// Initializes the oscillator.
	// The wavetable parameter can't be nullptr.
	// The sampleRate parameter must be greater than 0.
	void setup(Wavetable* wavetable, double sampleRate);

	// Sets the frequency of the oscillator. A frequency of 0 marks it as inactive. 
	// Call setup() before calling setFrequency().
	void setFrequency(double frequency);

	// Returns a sample from the wavetable. Call this again to get the next sample.
	// The shape parameter controls the interpolation between the wavetable's channels. It should be in range 0-1.
	float getNextSample(float shape);

	// Returns whether the oscillator is currently used.
	bool isActive() const;

	// Returns a pointer to the first inactive oscillator in the given vector.
	// Returns nullptr if all are active or the vector is empty.
	static Oscillator* findInactive(std::vector<Oscillator>& oscillators);
private:
	double angle = 0.0;
	double angleDelta = 0.0;
	double frequency = 0.0;
	int sampleRate = 0;
	Wavetable* wavetable = nullptr;
};