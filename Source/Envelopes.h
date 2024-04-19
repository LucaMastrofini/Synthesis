/*
  ==============================================================================

    AmplitudeEnvelope.h
    Created: 9 Dec 2020 12:57:36pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Define.h"

class Envelopes : public juce::Component
{
public:
    Envelopes(SynthThesisAudioProcessor&);
    ~Envelopes() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Slider ampAttackSlider, ampDecaySlider, ampSustainSlider, ampReleaseSlider, filterAttackSlider, filterDecaySlider, filterSustainSlider, filterReleaseSlider, filterEnvAmount;
    SynthThesisAudioProcessor& audioProcessor;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterReleaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterEnvAmountAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Envelopes)
};