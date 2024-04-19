/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Oscillator.h"
#include "Mixer.h"
#include "Envelopes.h"
#include "Filter.h"


//==============================================================================
/**
*/
class SynthThesisAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthThesisAudioProcessorEditor (SynthThesisAudioProcessor&);
    ~SynthThesisAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Oscillator oscGui1;
    Oscillator oscGui2;
    Mixer mixerGui;
    Envelopes envelopeGui;
    Filter filterGui;
    
    
    SynthThesisAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthThesisAudioProcessorEditor)
};
