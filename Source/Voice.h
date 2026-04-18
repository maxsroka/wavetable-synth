#include "Oscillator.h"

class Voice
{
public:
	Voice(Oscillator* oscillator, int noteNumber);
	void start();
	void stop();
	float getNextSample(float shape);

	constexpr static float VOICE_LEVEL = 0.4f;
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);
private:
	Oscillator* oscillator;
	int noteNumber;
};