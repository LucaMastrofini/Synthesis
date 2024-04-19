/*
  ==============================================================================

    Filter.cpp
    Created: 9 Dec 2020 12:56:48pm
    Author:  Masterfine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

Filter::Filter(SynthThesisAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(400, 200);
    
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("Band Pass", 2);
    filterMenu.addItem("High Pass", 3);
    filterMenu.setJustificationType(juce::Justification::centred);
    filterMenu.setSelectedId(1, juce::dontSendNotification);
    addAndMakeVisible(&filterMenu);

    cutOffSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    cutOffSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
    addAndMakeVisible(&cutOffSlider);

    resSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    resSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&resSlider);

    filterLfoGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    filterLfoGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&filterLfoGainSlider);

    filterLfoRateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    filterLfoRateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&filterLfoRateSlider);


    filterMenuAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.valueTreeState, FILTER_MENU_ID, filterMenu));
    cutOffSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, CUTOFF_ID, cutOffSlider));
    resSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, RESONANCE_ID, resSlider));
    filterLfoGainSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_GAIN_LFO_ID, filterLfoGainSlider));
    filterLfoRateSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_RATE_LFO_ID, filterLfoRateSlider));
    filterAttackAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_ATTACK_ID, filterAttackSlider));
    filterDecayAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_DECAY_ID, filterDecaySlider));
    filterSustainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_SUSTAIN_ID, filterSustainSlider));
    filterReleaseAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, FILTER_RELEASE_ID, filterReleaseSlider));

}

Filter::~Filter()
{
}

void Filter::paint(juce::Graphics& g)
{
    
    juce::Rectangle<int> titleArea(50, 20, 100, 20);


    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("Cutoff", 25, 30, 70, 70, juce::Justification::centred);
    g.drawText("Res", 105, 30, 70, 70, juce::Justification::centred);
    g.drawText("Amount", 225, 30, 70, 70, juce::Justification::centred);
    g.drawText("Rate", 305, 30, 70, 70, juce::Justification::centred);

    g.setFont(20.0f);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);
    g.drawText("LFO Cutoff", 250, 20, 100, 20, juce::Justification::centred);







    juce::Rectangle <float> area(10, 10, 380, 180);

    g.setColour(juce::Colours::lightcyan);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void Filter::resized()
{

    filterMenu.setBounds(150, 20, 100, 20);
    cutOffSlider.setBounds(25, 70, 70, 90);
    resSlider.setBounds(105, 70, 70, 90);
    filterLfoGainSlider.setBounds(225, 70, 70, 90);
    filterLfoRateSlider.setBounds(305, 70, 70, 90);
    
    
}