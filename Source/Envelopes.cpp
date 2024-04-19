/*
  ==============================================================================

    AmplitudeEnvelope.cpp
    Created: 9 Dec 2020 12:57:36pm
    Author:  Masterfine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelopes.h"

Envelopes::Envelopes(SynthThesisAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(400, 200);

    ampAttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical); 
    ampAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&ampAttackSlider);
    
    ampDecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&ampDecaySlider);
    
    ampSustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&ampSustainSlider);
    
    ampReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    ampReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&ampReleaseSlider);

    filterAttackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&filterAttackSlider);

    filterDecaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&filterDecaySlider);

    filterSustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&filterSustainSlider);

    filterReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 30, 20);
    addAndMakeVisible(&filterReleaseSlider);
    
    filterEnvAmount.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    filterEnvAmount.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(&filterEnvAmount);
    
    attackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, ATTACK_ID, ampAttackSlider));
    decayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, DECAY_ID, ampDecaySlider));
    sustainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, SUSTAIN_ID, ampSustainSlider));
    releaseAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, RELEASE_ID, ampReleaseSlider));
    filterAttackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_ATTACK_ID, filterAttackSlider));
    filterDecayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_DECAY_ID, filterDecaySlider));
    filterSustainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_SUSTAIN_ID, filterSustainSlider));
    filterReleaseAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_RELEASE_ID, filterReleaseSlider));
    filterEnvAmountAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_ENV_AMT_ID, filterEnvAmount));


}

Envelopes::~Envelopes()
{
}

void Envelopes::paint(juce::Graphics& g)
{
    //background stuff
    juce::Rectangle<int> AMPtitleArea(0, 20, 180, 20);
    juce::Rectangle<int> FiltertitleArea(180, 20, 220, 20);


    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("A", 5, 20, 70, 70, juce::Justification::centred);
    g.drawText("D", 40, 20, 70, 70, juce::Justification::centred);
    g.drawText("S", 75, 20, 70, 70, juce::Justification::centred);
    g.drawText("R", 110, 20, 70, 70, juce::Justification::centred);
    g.drawText("A", 180, 20, 70, 70, juce::Justification::centred);
    g.drawText("D", 215, 20, 70, 70, juce::Justification::centred);
    g.drawText("S", 250, 20, 70, 70, juce::Justification::centred);
    g.drawText("R", 285, 20, 70, 70, juce::Justification::centred);
    g.drawText("AMT", 320, 20, 70, 70, juce::Justification::centred);

    g.setFont(20.0f);
    g.drawText("AMP ENV", AMPtitleArea, juce::Justification::centredTop);
    g.drawText("FILTER ENV", FiltertitleArea, juce::Justification::centredTop);




    juce::Rectangle <float> area(10, 10, 380, 180);

    g.setColour(juce::Colours::lightcyan);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void Envelopes::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    ampAttackSlider.setBounds(20, 60, 40, 120);
    ampDecaySlider.setBounds(55, 60, 40, 120);
    ampSustainSlider.setBounds(90, 60, 40, 120);
    ampReleaseSlider.setBounds(125, 60, 40, 120);
    filterAttackSlider.setBounds(195, 60, 40, 120);
    filterDecaySlider.setBounds(230, 60, 40, 120);
    filterSustainSlider.setBounds(265, 60, 40, 120);
    filterReleaseSlider.setBounds(300, 60, 40, 120);
    filterEnvAmount.setBounds(335, 60, 40, 120);
}