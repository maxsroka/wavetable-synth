#include "Oscillator.h"

class Voice
{
public:
	Voice(Oscillator* oscillator, int noteNumber);
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);
	void start();
	void stop();
	float getNextSample(float shape);
private:
	Oscillator* oscillator;
	int noteNumber;
};