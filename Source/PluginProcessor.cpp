#include "PluginProcessor.h"
#include "PluginEditor.h"

StereoMixerAudioProcessor::StereoMixerAudioProcessor()
    : parameters(*this, nullptr, "MyMxrParams", {
    std::make_unique<AudioParameterFloat>("LEFTGAIN", "Left", -48.0f, 6.0f, 0.0f),
    std::make_unique<AudioParameterFloat>("RIGHTGAIN", "Right", -48.0f, 6.0f, 0.0f)
        })
{
    parameters.addParameterListener("LEFTGAIN", this);
    parameters.addParameterListener("RIGHTGAIN", this);

    leftGain.setCurrentAndTargetValue(1.0f);
    rightGain.setCurrentAndTargetValue(1.0f);



}

StereoMixerAudioProcessor::~StereoMixerAudioProcessor()
{
}


const juce::String StereoMixerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoMixerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoMixerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoMixerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoMixerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoMixerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoMixerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoMixerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StereoMixerAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoMixerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}


void StereoMixerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    leftGain.reset(sampleRate, 0.02);
    rightGain.reset(sampleRate, 0.02);
}

void StereoMixerAudioProcessor::releaseResources()
{

}

//===============================================================================================================================================================
void StereoMixerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto numSamples = buffer.getNumSamples();
  
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)       //CLEARING...
        buffer.clear (i, 0, numSamples);


    ///auto* channelData = buffer.getArrayOfWritePointers();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        if (channel == 0)
        {
            leftGain.applyGain(buffer, numSamples);
        }
        if (channel == 1)
        {
            rightGain.applyGain(buffer, numSamples);
            
        }
        //auto* channelData = buffer.getWritePointer (channel);
        
        // ..do something to the data...
    }
    
}


bool StereoMixerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StereoMixerAudioProcessor::createEditor()
{
    return new StereoMixerAudioProcessorEditor (*this, parameters);
}


void StereoMixerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void StereoMixerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));

}

void StereoMixerAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == "LEFTGAIN")
    {
        leftGain.setTargetValue(Decibels::decibelsToGain(newValue));
    }
    if (paramID == "RIGHTGAIN")
    {
        rightGain.setTargetValue(Decibels::decibelsToGain(newValue));
    }
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoMixerAudioProcessor();
}
