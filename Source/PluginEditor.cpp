
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
    g.fillAll (Colours::palevioletred);
    g.setColour (juce::Colours::black);
    g.setFont (25.0f);
    g.drawFittedText ("Behold the Stereo Mixer!", getLocalBounds(), juce::Justification::centredTop, 2);
}

void StereoMixerAudioProcessorEditor::resized()
{
    leftSlider.setBounds(40, 20, 50, getHeight() - 40);
    rightSlider.setBounds(getWidth() - 90, 20, 50, getHeight() - 40);
}

