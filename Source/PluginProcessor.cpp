#include "PluginProcessor.h"
#include "PluginEditor.h"

WavetableSynthAudioProcessor::WavetableSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	),
	parameters(*this, nullptr, "Parameters", createParameterLayout())
#endif
{}

WavetableSynthAudioProcessor::~WavetableSynthAudioProcessor() {}

const juce::String WavetableSynthAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool WavetableSynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool WavetableSynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool WavetableSynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double WavetableSynthAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int WavetableSynthAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int WavetableSynthAudioProcessor::getCurrentProgram()
{
	return 0;
}

void WavetableSynthAudioProcessor::setCurrentProgram(int index) {}

const juce::String WavetableSynthAudioProcessor::getProgramName(int index)
{
	return {};
}

void WavetableSynthAudioProcessor::changeProgramName(int index, const juce::String& newName)
{}

void WavetableSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	wavetable.generate();

	for (Oscillator& oscillator : oscillators)
	{
		oscillator.setup(&wavetable, sampleRate);
	}
}

void WavetableSynthAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WavetableSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void WavetableSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	for (int i = 0; i < voices.size(); ++i)
	{
		Voice& voice = voices[i];

		if (voice.getDidFadeOut())
		{
			voices.erase(voices.begin() + i);
		}
	}

	float fadeIn = parameters.getParameter("fadeIn")->getValue();
	float fadeOut = parameters.getParameter("fadeOut")->getValue();

	for (auto element : midiMessages)
	{
		juce::MidiMessage msg = element.getMessage();
		int noteNumber = msg.getNoteNumber();

		if (msg.isNoteOn())
		{
			Oscillator* oscillator = Oscillator::findInactive(oscillators);
			if (oscillator == nullptr) continue;

			float velocity = msg.getFloatVelocity();
			Voice voice = Voice(oscillator, noteNumber, velocity, fadeIn, fadeOut);

			voices.push_back(voice);
		}
		else if (msg.isNoteOff())
		{
			int index = Voice::findIndexByNote(voices, noteNumber);
			if (index == -1) continue;

			voices[index].stop();
		}
	}

	int numOutputChannels = getTotalNumOutputChannels();
	jassert(numOutputChannels >= 2);

	int numSamples = buffer.getNumSamples();
	float shape = parameters.getParameter("shape")->getValue();
	float pan = parameters.getParameter("pan")->getValue();
	pan = (pan - 0.5f) * 2.0f;

	for (int i = 0; i < numSamples; ++i)
	{
		float sample = 0.0f;
		for (Voice& voice : voices)
		{
			sample += voice.getNextSample(shape);
		}

		float* leftPtr = buffer.getWritePointer(0);
		float* rightPtr = buffer.getWritePointer(1);

		float leftPan = 1.0f - pan;
		float rightPan = 1.0f + pan;

		float leftSample = sample * leftPan;
		float rightSample = sample * rightPan;

		leftSample *= 0.2f;
		rightSample *= 0.2f;

		leftPtr[i] = leftSample;
		rightPtr[i] = rightSample;
	}

	midiMessages.clear();

	float volume = parameters.getParameter("volume")->getValue();
	buffer.applyGain(volume);
}

bool WavetableSynthAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WavetableSynthAudioProcessor::createEditor()
{
	return new WavetableSynthAudioProcessorEditor(*this, this->parameters);
}

void WavetableSynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void WavetableSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new WavetableSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout WavetableSynthAudioProcessor::createParameterLayout()
{
	juce::AudioProcessorValueTreeState::ParameterLayout layout;

	layout.add(std::make_unique<juce::AudioParameterFloat>("volume", "Volume", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f));
	layout.add(std::make_unique<juce::AudioParameterFloat>("shape", "Shape", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.0f));
	layout.add(std::make_unique<juce::AudioParameterFloat>("pan", "Pan", juce::NormalisableRange<float>(-1.0f, 1.0f, 0.01f), 0.0f));
	layout.add(std::make_unique<juce::AudioParameterFloat>("fadeIn", "Fade In", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.2f));
	layout.add(std::make_unique<juce::AudioParameterFloat>("fadeOut", "Fade Out", juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.05f));

	return layout;
}

Wavetable& WavetableSynthAudioProcessor::getWavetable()
{
	return wavetable;
}