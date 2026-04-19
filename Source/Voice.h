#include "Oscillator.h"

class Voice
{
public:
	Voice(Oscillator* oscillator, int noteNumber, float velocity, float fadeIn, float fadeOut);
	void start();
	void stop();
	float getNextSample(float shape);

	constexpr static float VOICE_LEVEL = 1.0f;
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);
	bool didFadeOut = false;
private:
	Oscillator* oscillator;
	int noteNumber;
	float velocity;
	bool didStop = false;
	int fadeIndex = 0;
	int fadeInNumSamples = 0;
	int fadeOutNumSamples = 0;
	float getNextFade();
};