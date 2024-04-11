#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class StereoMixerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    StereoMixerAudioProcessorEditor (StereoMixerAudioProcessor&,
        AudioProcessorValueTreeState&);
    ~StereoMixerAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    AudioProcessorValueTreeState& valueTreeState;
    StereoMixerAudioProcessor& audioProcessor;
    
    Slider leftSlider;
    Slider rightSlider;

    std::unique_ptr<SliderAttachment> leftGainAttachment;
    std::unique_ptr<SliderAttachment> rightGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoMixerAudioProcessorEditor)
};
