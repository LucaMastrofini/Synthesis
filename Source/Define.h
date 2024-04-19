/*
  ==============================================================================

    Define.h
    Created: 22 Dec 2020 5:04:22pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


#define MENU_ID       "menuOsc"
#define PITCH_ID     "pitchOsc"
#define PAN_ID        "panOsc"
#define LFO_AM_GAIN   "lfoAMGain"
#define LFO_AM_RATE   "lfoAMRate"
#define LFO_FM_GAIN   "lfoFmGain"
#define LFO_FM_RATE   "lfoFmRate"
#define MASTER_GAIN_ID "masterGain"
#define BLEND_ID        "blend"
#define ATTACK_ID       "attack"
#define SUSTAIN_ID      "sustain"
#define DECAY_ID        "decay"
#define RELEASE_ID      "release"
#define FILTER_MENU_ID  "filterMenu"
#define CUTOFF_ID       "cutoff"
#define RESONANCE_ID      "resonance"
#define FILTER_GAIN_LFO_ID        "filterGainLfo"
#define FILTER_RATE_LFO_ID      "filterRateLfo"
#define FILTER_ATTACK_ID       "filterAttack"
#define FILTER_DECAY_ID        "filterDecay"
#define FILTER_SUSTAIN_ID      "filterSustain"
#define FILTER_RELEASE_ID      "filterRelease"
#define FILTER_ENV_AMT_ID       "filterEnvAmt"
#define DEFAULT_MENU        1
#define DEFAULT_PITCH       0.0f
#define DEFAULT_PAN         0.5f
#define DEFAULT_GAINAM      0.0f
#define DEFAULT_RATEAM      0.0f
#define DEFAULT_GAINFM      0.0f
#define DEFAULT_RATEFM      0.0f
#define DEFAULT_MASTERGAIN  1.0f
#define DEFAULT_BLEND       0.5f
#define DEFAULT_CUTOFF      20000.0f



namespace paramIDs {
    const juce::String menu = "menuOsc";
    const juce::String pitch = "pitchOsc";
    const juce::String pan = "panOsc";
    const juce::String lfo_am_gain = "lfoAMGain";
    const juce::String lfo_am_rate = "lfoAMRate";
    const juce::String lfo_fm_gain = "lfoFmGain";
    const juce::String lfo_fm_rate = "lfoFmRate";
    const juce::String master_gain = "masterGain";
    const juce::String blend = "blend";
    const juce::String attack = "attack";
    const juce::String decay = "decay";
    const juce::String sustain = "sustain";
    const juce::String release = "release";
    const juce::String filterMenu = "filterMenu";
    const juce::String cutOff = "cutoff";
    const juce::String resonance = "resonance";
    const juce::String filterGainLFO = "filterGainLfo";
    const juce::String filterRateLFO = "filterRateLfo";
    const juce::String filterAttack = "filterAttack";
    const juce::String filterDecay = "filterDecay";
    const juce::String filterSustain = "filterSustain";
    const juce::String filterRelease = "filterRelease";
    const juce::String filterEnvAmt = "filterEnvAmt";
}