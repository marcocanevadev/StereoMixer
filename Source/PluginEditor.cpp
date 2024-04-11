
#include "PluginProcessor.h"
#include "PluginEditor.h"


StereoMixerAudioProcessorEditor::StereoMixerAudioProcessorEditor (
    StereoMixerAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState (vts)
{

    leftSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    leftSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);

    rightSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    rightSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 50, 20);

    addAndMakeVisible(&leftSlider);
    addAndMakeVisible(&rightSlider);

    leftGainAttachment.reset(new SliderAttachment(valueTreeState, "LEFTGAIN", leftSlider));
    rightGainAttachment.reset(new SliderAttachment(valueTreeState, "RIGHTGAIN", rightSlider));

    setSize (200, 400);
}

StereoMixerAudioProcessorEditor::~StereoMixerAudioProcessorEditor()
{
}


void StereoMixerAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto purpleHue = juce::Colours::purple.getHue();
    auto redHue = juce::Colours::red.getHue();
    g.fillAll (juce::Colour::fromHSV(purpleHue, 0.5f, 0.4f, 1.0f));
    g.setColour (juce::Colour::fromHSV(purpleHue, 0.5f, 0.05f, 1.0f));
    g.setFont (25.0f);
    g.drawFittedText ("BEHOLD the Stereo Mixer!", getLocalBounds(), juce::Justification::centredTop, 2);
    g.setColour(juce::Colour::fromHSV(purpleHue, 0.5f, 0.8f, 0.5f));
    for (int i = 0; i < 50; ++i)
    {
        g.drawLine(-30 + (i*10), 0 + (i * 20), 10 + (i*15), 10 +(i*22));
    }
    g.setColour(juce::Colour::fromHSV(redHue, 0.5f, 0.8f, 0.5f));

    Path tri1;
    tri1.addTriangle(0, 100, 150, 400,0,400);
    g.fillPath(tri1);
    g.setColour(juce::Colour::fromHSV(purpleHue, 0.5f, 0.4f, 1.0f));
    Path tri2;
    tri2.addTriangle(0, 250, 75, 400, 0, 400);
    g.fillPath(tri2);

}

void StereoMixerAudioProcessorEditor::resized()
{
    leftSlider.setBounds(40, 20, 50, getHeight() - 40);
    rightSlider.setBounds(getWidth() - 90, 20, 50, getHeight() - 40);
}

