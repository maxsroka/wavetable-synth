#include "Voice.h"

Voice::Voice(Oscillator* oscillator, int noteNumber, float velocity) : oscillator(oscillator), noteNumber(noteNumber), velocity(velocity) {}

void Voice::start()
{
	float noteFreq = juce::MidiMessage::getMidiNoteInHertz(noteNumber);
	oscillator->setFrequency(noteFreq);
}

void Voice::stop()
{
	didStop = true;
	fadeIndex = FADE_OUT_NUM_SAMPLES;
}

float Voice::getNextFade()
{
	float fade;

	if (!didStop)
	{
		++fadeIndex;
		fade = static_cast<float>(fadeIndex) / FADE_IN_NUM_SAMPLES;
	}
	else
	{
		--fadeIndex;
		fade = static_cast<float>(fadeIndex) / FADE_OUT_NUM_SAMPLES;

		if (fadeIndex <= 0)
		{
			oscillator->setFrequency(0.0);
			didFadeOut = true;
		}
	}

	fade = std::clamp(fade, 0.0f, 1.0f);

	return fade;
}

float Voice::getNextSample(float shape)
{
	float fade = getNextFade();
	return oscillator->getNextSample(shape) * VOICE_LEVEL * velocity * fade;
}

int Voice::findIndexByNote(std::vector<Voice> voices, int noteNumber)
{
	for (int i = 0; i < voices.size(); ++i)
	{
		Voice& voice = voices[i];

		if (voice.noteNumber == noteNumber)
		{
			return i;
		}
	}

	return -1;
}