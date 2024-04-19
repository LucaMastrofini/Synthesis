/*
  ==============================================================================

    Filter.h
    Created: 9 Dec 2020 12:56:48pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Define.h"

class Filter : public juce::Component
{
public:
    Filter(SynthThesisAudioProcessor&);
    ~Filter() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::ComboBox filterMenu;
    juce::Slider cutOffSlider, resSlider, filterLfoGainSlider, filterLfoRateSlider, filterAttackSlider, filterDecaySlider, filterSustainSlider, filterReleaseSlider;
    SynthThesisAudioProcessor& audioProcessor;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterMenuAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutOffSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterLfoGainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterLfoRateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterSustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterReleaseAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};