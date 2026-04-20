#include "Voice.h"

Voice::Voice(Oscillator* oscillator, int noteNumber, float velocity, float fadeIn, float fadeOut) : oscillator(oscillator), noteNumber(noteNumber), velocity(velocity) 
{
	jassert(oscillator != nullptr);
	jassert(velocity >= 0.0f && velocity <= 1.0f);
	jassert(fadeIn >= 0.0f && fadeIn <= 1.0f);
	jassert(fadeOut >= 0.0f && fadeOut <= 1.0f);

	fadeInNumSamples = fadeIn * 44100;
	fadeOutNumSamples = fadeOut * 44100;

	float noteFreq = juce::MidiMessage::getMidiNoteInHertz(noteNumber);
	oscillator->setFrequency(noteFreq);
}

void Voice::stop()
{
	didStop = true;
	fadeIndex = fadeOutNumSamples;
}

float Voice::getNextFade()
{
	float fade;

	if (!didStop)
	{
		++fadeIndex;
		fade = static_cast<float>(fadeIndex) / fadeInNumSamples;
	}
	else
	{
		--fadeIndex;
		fade = static_cast<float>(fadeIndex) / fadeOutNumSamples;

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
	return oscillator->getNextSample(shape) * velocity * fade;
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

bool Voice::getDidFadeOut() const
{
	return didFadeOut;
}