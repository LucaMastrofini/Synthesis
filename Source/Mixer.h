/*
  ==============================================================================

    Mixer.h
    Created: 9 Dec 2020 12:57:14pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Define.h"

class Mixer : public juce::Component
{
public:
    Mixer(SynthThesisAudioProcessor&);
    ~Mixer() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Slider masterGain, interpol;
    SynthThesisAudioProcessor& audioProcessor;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> interpolAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Mixer)
};