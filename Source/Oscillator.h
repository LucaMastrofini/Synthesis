/*
  ==============================================================================

    Oscillator.h
    Created: 14 Dec 2020 12:56:17pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Define.h"


class Oscillator : public juce::Component
{
public:
    Oscillator(SynthThesisAudioProcessor&, int id);
    ~Oscillator() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    int getId();

    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    int oscId;
    juce::ComboBox oscMenu;
    juce::Slider pitchSlider, panSlider, gainFM, rateFM, gainAM, rateAM;
    SynthThesisAudioProcessor& audioProcessor;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscMenuAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAmAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateAmAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainFmAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateFmAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};