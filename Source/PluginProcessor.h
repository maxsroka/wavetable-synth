#pragma once
#include <JuceHeader.h>
#include "Oscillator.h"
#include "Voice.h"

/*
	Main processor class of the plugin. 
	This is where audio processing happens.
	See also PluginEditor.h for the GUI.
*/
class WavetableSynthAudioProcessor : public juce::AudioProcessor
{
public:
	WavetableSynthAudioProcessor();
	~WavetableSynthAudioProcessor() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	Wavetable& getWavetable();

	static constexpr int NUM_OSCILLATORS = 16;
private:
	Wavetable wavetable;
	std::vector<Oscillator> oscillators{ NUM_OSCILLATORS };
	std::vector<Voice> voices;
	juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
	juce::AudioProcessorValueTreeState parameters{ *this, nullptr };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WavetableSynthAudioProcessor)
};
