/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include<string>

//==============================================================================
SynthThesisAudioProcessor::SynthThesisAudioProcessor():
/*#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , */
    valueTreeState(*this, nullptr, juce::Identifier("VTS"), {
        std::make_unique <juce::AudioParameterInt>(MENU_ID + std::to_string(1), "OscMenu1", 1, 5, 1),
        std::make_unique <juce::AudioParameterFloat>(PITCH_ID + std::to_string(1), "Pitch1", -1200.0f, 1200.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(PAN_ID + std::to_string(1), "Pan1", 0.0f, 1.0f, 0.5f),
        std::make_unique <juce::AudioParameterFloat>(LFO_AM_GAIN + std::to_string(1), "AmAmount1", 0.0f, 1.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_AM_RATE + std::to_string(1), "AmRate1", 0.0f, 20.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_FM_GAIN + std::to_string(1), "FmAmount1", 0.0f, 1200.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_FM_RATE + std::to_string(1), "FmRate1", 0.0f, 20.0f, 0.0f),
        std::make_unique <juce::AudioParameterInt>(MENU_ID + std::to_string(2), "OscMenu2", 1, 5, 1),
        std::make_unique <juce::AudioParameterFloat>(PITCH_ID + std::to_string(2), "Pitch2", -1200.0f, 1200.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(PAN_ID + std::to_string(2), "Pan2", 0.0f, 1.0f, 0.5f),
        std::make_unique <juce::AudioParameterFloat>(LFO_AM_GAIN + std::to_string(2), "AmAmount2", 0.0f, 1.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_AM_RATE + std::to_string(2), "AmRate2", 0.0f, 20.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_FM_GAIN + std::to_string(2), "FmAmount2", 0.0f, 1200.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(LFO_FM_RATE + std::to_string(2), "FmRate2", 0.0f, 20.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(MASTER_GAIN_ID, "MasterGain", 0.0f, 1.2f, 1.0f),
        std::make_unique <juce::AudioParameterFloat>(BLEND_ID, "Blend", 0.0f, 1.0f, 0.5f),
        std::make_unique <juce::AudioParameterFloat>(ATTACK_ID, "Attack", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(DECAY_ID, "Decay", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(SUSTAIN_ID, "Sustain", 0.0f, 1.0f, 1.0f),
        std::make_unique <juce::AudioParameterFloat>(RELEASE_ID, "Release", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterInt>(FILTER_MENU_ID, "FilterMenu", 1, 3, 1),
        std::make_unique <juce::AudioParameterFloat>(CUTOFF_ID, "Cutoff", juce::NormalisableRange<float> {20.0f, 20000.0f, 0.1f, 0.25f}, 20000.0f),
        std::make_unique <juce::AudioParameterFloat>(RESONANCE_ID, "Resonace", 0.1f, 4.0f, 0.1f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_GAIN_LFO_ID, "FilterAmountLFO", 0.0f, 1200.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_RATE_LFO_ID, "FilterRateLFO", 0.0f, 20.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_ATTACK_ID, "FilterAttack", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_DECAY_ID, "FilterDecay", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_SUSTAIN_ID, "FilterSustain", 0.0f, 1.0f, 1.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_RELEASE_ID, "FilterRelease", 0.0f, 5.0f, 0.0f),
        std::make_unique <juce::AudioParameterFloat>(FILTER_ENV_AMT_ID, "FilterEnvAMT", juce::NormalisableRange<float> {0.0f, 1.0f, 0.001f, 0.25f}, 0.0f)
    })

        
{

    

    mySynth.clearVoices();

    for (int i = 0; i < numVoices; i++)
    {
        mySynth.addVoice(new SynthVoice());
        valueTreeState.addParameterListener(MENU_ID + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(MENU_ID + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(PITCH_ID + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(PITCH_ID + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(PAN_ID + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(PAN_ID + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_AM_GAIN + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_AM_GAIN + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_AM_RATE + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_AM_RATE + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_FM_GAIN + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_FM_GAIN + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_FM_RATE + std::to_string(1), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(LFO_FM_RATE + std::to_string(2), dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(MASTER_GAIN_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(BLEND_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(ATTACK_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(DECAY_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(SUSTAIN_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(RELEASE_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_MENU_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(CUTOFF_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(RESONANCE_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_GAIN_LFO_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_RATE_LFO_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_ATTACK_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_DECAY_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_SUSTAIN_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_RELEASE_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
        valueTreeState.addParameterListener(FILTER_ENV_AMT_ID, dynamic_cast<SynthVoice*>(mySynth.getVoice(i)));
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

}

SynthThesisAudioProcessor::~SynthThesisAudioProcessor()
{
}

//==============================================================================
const juce::String SynthThesisAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthThesisAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthThesisAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthThesisAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthThesisAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthThesisAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthThesisAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthThesisAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthThesisAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthThesisAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthThesisAudioProcessor::prepareToPlay (double sampleRate, int blockSize)
{
    int totalNumOutputChannels = getTotalNumOutputChannels();
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    for (int i = 0; i < numVoices; i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->prepareToPlay(sampleRate, totalNumOutputChannels, blockSize);
            myVoice->parameterChanged(paramIDs::cutOff, 20000.0f);
            myVoice->parameterChanged(paramIDs::filterMenu, 1);
        }
    }
}

void SynthThesisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthThesisAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void SynthThesisAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool SynthThesisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthThesisAudioProcessor::createEditor()
{
    return new SynthThesisAudioProcessorEditor (*this);
}

//==============================================================================
void SynthThesisAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = valueTreeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SynthThesisAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement>XmlState(getXmlFromBinary(data, sizeInBytes));
    if (XmlState.get() != nullptr)
        if (XmlState->hasTagName(valueTreeState.state.getType()))
            valueTreeState.replaceState(juce::ValueTree::fromXml(*XmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthThesisAudioProcessor();
}
