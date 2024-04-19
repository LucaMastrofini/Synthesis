/*
  ==============================================================================

    SynthSound.h
    Created: 7 Dec 2020 1:35:22pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int /*midiNoteNumber*/) {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/) {
        return true;
    }
};