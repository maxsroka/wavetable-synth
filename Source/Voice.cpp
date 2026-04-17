#include "Voice.h"

Voice::Voice(Oscillator* oscillator, int noteNumber) : oscillator(oscillator), noteNumber(noteNumber)
{

}

void Voice::start()
{
    float noteFreq = juce::MidiMessage::getMidiNoteInHertz(noteNumber);
    oscillator->setFrequency(noteFreq);
    oscillator->setActive(true);
}

void Voice::stop()
{
    oscillator->setFrequency(0.0);
    oscillator->setActive(false);
}

float Voice::getNextSample(float shape)
{
    return oscillator->getNextSample(shape) * 0.4f;
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