#include "Oscillator.h"

class Voice
{
public:
	constexpr static float VOICE_LEVEL = 0.4f;
	Voice(Oscillator* oscillator, int noteNumber);
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);
	void start();
	void stop();
	float getNextSample(float shape);
private:
	Oscillator* oscillator;
	int noteNumber;
};