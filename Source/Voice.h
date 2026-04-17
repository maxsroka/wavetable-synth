#include "Oscillator.h"

class Voice
{
public:
	Voice(Oscillator* oscillator);
	Oscillator* oscillator;
	int noteNumber;
};