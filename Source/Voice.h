#include "Oscillator.h"

/*
	A voice represents a note being played.
*/
class Voice
{
public:
	// Initializes the voice. 
	// The oscillator parameter can't be nullptr.
	// The velocity, fadeIn, and fadeOut parameters should be in range 0-1.
	Voice(Oscillator* oscillator, int noteNumber, float velocity, float fadeIn, float fadeOut);
	
	// Starts the fade out process. See getDidFadeOut().
	void stop();

	// Returns the next sample of the voice, applying the fade in/out and velocity. Call this again to get the next sample.
	float getNextSample(float shape);

	// Returns the index of the first voice with the specified note number in the given vector.
	// Returns -1 if no voice is found.
	static int findIndexByNote(std::vector<Voice> voices, int noteNumber);

	// Returns whether the voice has finished fading out.
	bool getDidFadeOut() const;
private:
	Oscillator* oscillator;
	int noteNumber;

	float velocity;
	bool didStop = false;
	
	int fadeIndex = 0;
	int fadeInNumSamples = 0;
	int fadeOutNumSamples = 0;
	bool didFadeOut = false;
	float getNextFade();
};