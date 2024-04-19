/*
  ==============================================================================

    Oscillator1.cpp
    Created: 9 Dec 2020 12:56:17pm
    Author:  Masterfine

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"
#include<string>

Oscillator::Oscillator(SynthThesisAudioProcessor& p, int id) :
    audioProcessor(p), oscId(id)
{
    setSize(200, 500);

    oscId = id;
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Square", 2);
    oscMenu.addItem("Saw", 3);
    oscMenu.addItem("Triangle", 4);
    oscMenu.addItem("Noise", 5);
    oscMenu.setJustificationType(juce::Justification::centred);
    oscMenu.setSelectedId(1, juce::dontSendNotification);
    addAndMakeVisible(&oscMenu);

    pitchSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&pitchSlider);
    panSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    panSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&panSlider);

    gainAM.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gainAM.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&gainAM);
    rateAM.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rateAM.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&rateAM);

    gainFM.setSliderStyle(juce::Slider::SliderStyle::Rotary);;
    gainFM.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&gainFM);
    rateFM.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    rateFM.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(&rateFM);

    oscMenuAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.valueTreeState, MENU_ID + std::to_string(oscId), oscMenu));
    pitchAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, PITCH_ID + std::to_string(oscId), pitchSlider));
    panAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, PAN_ID + std::to_string(oscId), panSlider));
    gainAmAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, LFO_AM_GAIN + std::to_string(oscId), gainAM));
    rateAmAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, LFO_AM_RATE + std::to_string(oscId), rateAM));
    gainFmAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, LFO_FM_GAIN + std::to_string(oscId), gainFM));
    rateFmAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.valueTreeState, LFO_FM_RATE + std::to_string(oscId), rateFM));
    
       
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint(juce::Graphics& g)
{
    //background stuff
    juce::Rectangle<int> titleArea(0, 20, getWidth(), 20);
    juce::Rectangle<int> bigArea(0, 0, getWidth(), getHeight());

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);

    g.drawText("Pitch", 25, 40, 70, 70, juce::Justification::centred);
    g.drawText("Pan", 105, 40, 70, 70, juce::Justification::centred);
    g.drawText("Amount", 25, 190, 70, 70, juce::Justification::centred);
    g.drawText("Rate", 105, 190, 70, 70, juce::Justification::centred);
    g.drawText("Amount", 25, 340, 70, 70, juce::Justification::centred);
    g.drawText("Rate", 105, 340, 70, 70, juce::Justification::centred);
    g.setFont(20.0f);
    g.drawText("Oscillator " + std::to_string(oscId), titleArea, juce::Justification::centredTop);
    g.drawText("LFO AM " + std::to_string(oscId), 50, 170, 100, 70, juce::Justification::centred);
    g.drawText("LFO FM " + std::to_string(oscId), 50, 320, 100, 70, juce::Justification::centred);




    juce::Rectangle <float> area(10, 10, 180, 480);

    g.setColour(juce::Colours::lightcyan);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
    pitchSlider.setBounds(25, 80, 70, 90);
    panSlider.setBounds(105, 80, 70, 90);
    gainAM.setBounds(25, 230, 70, 90);
    rateAM.setBounds(105, 230, 70, 90);
    gainFM.setBounds(25, 380, 70, 90);
    rateFM.setBounds(105, 380, 70, 90);
}

int Oscillator::getId() {
    return oscId;
}