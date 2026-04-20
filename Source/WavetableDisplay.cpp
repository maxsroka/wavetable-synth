#include "WavetableDisplay.h"

WavetableDisplay::WavetableDisplay(DefaultStyle& style, Wavetable& wavetable, juce::AudioProcessorValueTreeState& valueTreeState)
	: style(style), wavetable(wavetable), valueTreeState(valueTreeState), buffer(&wavetable.getBuffer())
{ }

void WavetableDisplay::paint(juce::Graphics& g)
{
	drawBackground(g);
	drawLines(g);
}

void WavetableDisplay::drawBackground(juce::Graphics& g)
{
	g.setColour(style.darkColor);
	g.fillRect(getLocalBounds());
}

void WavetableDisplay::drawLines(juce::Graphics& g)
{
	g.setColour(style.accentColor);

	auto bounds = getLocalBounds();
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