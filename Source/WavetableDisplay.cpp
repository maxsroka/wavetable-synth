#include "WavetableDisplay.h"

void WavetableDisplay::paint(juce::Graphics& g)
{
	juce::Rectangle<int> bounds = getLocalBounds();
	g.setColour(style.darkColor);
	g.fillRect(bounds);
	g.setColour(style.accentColor);

	juce::AudioSampleBuffer* buffer = &wavetable.getBuffer();
	float shape = valueTreeState.getParameter("shape")->getValue();

	// i starts as two to avoid out-of-bounds access and to skip drawing the first sample
	for (int i = 2; i < Wavetable::NUM_SAMPLES; ++i)
	{
		float sampleA = buffer->getSample(0, i - 1);
		float sampleB = buffer->getSample(0, i);
		float sampleC = buffer->getSample(1, i - 1);
		float sampleD = buffer->getSample(1, i);

		float sampleAC = std::lerp(sampleA, sampleC, shape);
		float sampleBD = std::lerp(sampleB, sampleD, shape);

		float x1 = bounds.getX() + ((i - 1) / static_cast<float>(Wavetable::NUM_SAMPLES)) * bounds.getWidth();
		float x2 = bounds.getX() + (i / static_cast<float>(Wavetable::NUM_SAMPLES)) * bounds.getWidth();
		float y1 = bounds.getCentreY() - sampleAC * bounds.getHeight() / 2;
		float y2 = bounds.getCentreY() - sampleBD * bounds.getHeight() / 2;

		g.drawLine(
			x1,
			y1,
			x2,
			y2,
			LINE_THICKNESS
		);
	}
}