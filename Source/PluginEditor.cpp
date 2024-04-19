/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthThesisAudioProcessorEditor::SynthThesisAudioProcessorEditor (SynthThesisAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), oscGui1(p, 1), oscGui2(p, 2), mixerGui(p), envelopeGui(p), filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(800, 530);
    addAndMakeVisible(&oscGui1);
    addAndMakeVisible(&oscGui2);
    addAndMakeVisible(&mixerGui);
    addAndMakeVisible(&envelopeGui);
    addAndMakeVisible(&filterGui);
}

SynthThesisAudioProcessorEditor::~SynthThesisAudioProcessorEditor()
{
}

//==============================================================================
void SynthThesisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::transparentBlack);
    g.setColour(juce::Colours::white);

    g.setFont(12.0f);
    g.drawText("coded at Laboratorio di Informatica Musicale", 25, 500, 400, 30, juce::Justification::centredLeft);
    g.drawText("developed by L.M. :: version 1.0.1", 400, 500, 375, 30, juce::Justification::centredRight);
}

void SynthThesisAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    oscGui1.setBounds(0, 0, 200, 500);
    oscGui2.setBounds(600, 0, 200, 500);
    mixerGui.setBounds(200, 0, 400, 200);
    envelopeGui.setBounds(200, 300, 400, 200);
    filterGui.setBounds(200, 100, 400, 200);
    
}