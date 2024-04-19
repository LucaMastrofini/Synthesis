/*
  ==============================================================================

    Mixer.cpp
    Created: 9 Dec 2020 12:57:14pm
    Author:  Masterfine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Mixer.h"


Mixer::Mixer(SynthThesisAudioProcessor& p) :
    audioProcessor(p)
{
    setSize(400, 200);

    masterGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    masterGain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&masterGain);
    interpol.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    interpol.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&interpol);

    masterGainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, MASTER_GAIN_ID, masterGain));
    interpolAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, BLEND_ID, interpol));
    
            }

Mixer::~Mixer()
{
}

void Mixer::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 40, getWidth(), 20);
   
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("Gain", 25, 0, 70, 20, juce::Justification::centred);
    g.drawText("Blend", 305, 0, 70, 20, juce::Justification::centred);
    
    g.setFont(30.0f);
    g.drawText("SynthThesis", 0, 35, 400, 30, juce::Justification::centred);

    g.setColour(juce::Colours::lightcyan);
    g.drawRoundedRectangle(110, 25, 180, 50, 20, 2);

}

void Mixer::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    masterGain.setBounds(25, 10, 70, 85);
    interpol.setBounds(305, 10, 70, 85);
}