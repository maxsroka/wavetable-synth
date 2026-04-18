#include "Voice.h"

Voice::Voice(Oscillator* oscillator, int noteNumber) : oscillator(oscillator), noteNumber(noteNumber) {}

void Voice::start()
{
	float noteFreq = juce::MidiMessage::getMidiNoteInHertz(noteNumber);
	oscillator->setFrequency(noteFreq);
}

void Voice::stop()
{
	oscillator->setFrequency(0.0);
}

float Voice::getNextSample(float shape)
{
	return oscillator->getNextSample(shape) * VOICE_LEVEL;
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