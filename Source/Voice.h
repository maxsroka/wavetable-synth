#include "Oscillator.h"

class Voice
{
public:
	Voice(Oscillator* oscillator, int noteNumber, float velocity);
	void start();
	void stop();
	float getNextSample(float shape);

	constexpr static float VOICE_LEVEL = 0.8f;
	constexpr static int FADE_IN_NUM_SAMPLES = 44100 / 8;
	constexpr static int FADE_OUT_NUM_SAMPLES = 44100 / 8;
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);
	bool didFadeOut = false;
private:
	Oscillator* oscillator;
	int noteNumber;
	float velocity;
	bool didStop = false;
	int fadeIndex = 0;
	float getNextFade();
};