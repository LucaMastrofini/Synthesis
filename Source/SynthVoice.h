/*
  ==============================================================================

    SynthVoice.h
    Created: 7 Dec 2020 1:35:45pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "WaveForm.h"
#include "Define.h"
#include <string>

class SynthVoice : public juce::SynthesiserVoice, public juce::AudioProcessorValueTreeState::Listener
{

public:

    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        adsrGain.noteOn();
        adsrFilter.noteOn();

    }

    void stopNote(float velocity, bool allowTailOff)
    {   
        
        adsrGain.noteOff();
        adsrFilter.noteOff();
        clearCurrentNote();
    }

    void pitchWheelMoved(int newPitchWheelValue)
    {

    }

    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    void prepareToPlay(double sampleRate, int numChannels, int blockSize) 
    {
        adsrGain.setSampleRate(sampleRate);
        adsrFilter.setSampleRate(sampleRate);
        oscillator1.setSampleRate(sampleRate);
        oscillator2.setSampleRate(sampleRate);
        amplitudeLFO1.setSampleRate(sampleRate);
        frequencyLFO1.setSampleRate(sampleRate);
        amplitudeLFO2.setSampleRate(sampleRate);
        frequencyLFO2.setSampleRate(sampleRate);

        synthSpecs.maximumBlockSize = blockSize;
        synthSpecs.sampleRate = sampleRate;
        synthSpecs.numChannels = numChannels;
        synthFilter.prepare(synthSpecs);
        synthFilter.reset();
        adsrFilter.reset();
        adsrGain.reset();

        synthFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        synthFilter.setCutoffFrequency(20.0f);
        
    }

    float* dsp()
    {

        
        float champ[2] = { 0, 0 };
        float freqOsc[2];
        float gainOsc[2];

    
        freqOsc[0] = (frequency * pow(2.0f, pitch[0] / 1200) * pow(2.0f, gainFM[0] * frequencyLFO1.sineWave(rateFM[0]) / 1200));
        freqOsc[1] = (frequency * pow(2.0f, pitch[1] / 1200) * pow(2.0f, gainFM[1] * frequencyLFO2.sineWave(rateFM[1]) / 1200)) / 2.0f;
        gainOsc[0] = 1.0f + (gainAM[0] * amplitudeLFO1.sineWave(rateAM[0]));
        gainOsc[1] = 1.0f + (gainAM[1] * amplitudeLFO2.sineWave(rateAM[1]));



        switch (int(waveType[0])) {
            case 1:
                champ[0] = oscillator1.sineWave(freqOsc[0]);
                break;

            case 2:
                champ[0] = oscillator1.squareWave(freqOsc[0]);
                break;

            case 3:
                champ[0] = oscillator1.sawWave(freqOsc[0]);
                break;

            case 4:
                champ[0] = oscillator1.triangularWave(freqOsc[0]);
                break;

            case 5:
                champ[0] = oscillator1.noise();
                break;
        }

        switch (int(waveType[1])) {
            case 1:
                champ[1] = oscillator2.sineWave(freqOsc[1]);
                break;

            case 2:
                champ[1] = oscillator2.squareWave(freqOsc[1]);
                break;

            case 3:
                champ[1] = oscillator2.sawWave(freqOsc[1]);
                break;

            case 4:
                champ[1] = oscillator2.triangularWave(freqOsc[1]);
                break;

            case 5:
                champ[1] = oscillator2.noise();
                break;
        }

        sample[0] = (champ[0] * gainOsc[0] * (1 - blend) * sqrt(1 - pan[0]) + champ[1] * gainOsc[1] * (blend) * sqrt(1 - pan[1])) * masterGain * level;
        sample[1] = (champ[0] * gainOsc[0] * (1 - blend) * sqrt(pan[0]) + champ[1] * gainOsc[1] * (blend) * sqrt(pan[1])) * masterGain * level;

        return sample;

    }

    void setFilterType(int type) {
        switch (type) 
        {

        case 1:
            synthFilter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;

        case 2:
            synthFilter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;

        case 3:
            synthFilter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
        }
    }

    void updateFilterCutoff() {
        float adsrCutOff = adsrFilter.getNextSample() * 20000.0f * filterEnvAmt;
        float lfoCutOff = pow(2.0f, filterGainLFO * filterLFO.sineWave(filterRateLFO) / 1200);
        float totalCutoff = lfoCutOff * (cutOff + adsrCutOff);
        //Funzione juce senza if -> J limit
        totalCutoff = juce::jlimit<float>(20.0f, 20000.0f, totalCutoff);
        synthFilter.setCutoffFrequency(totalCutoff);
    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {   

        for (int sample = 0; sample < numSamples; ++sample)
        {
            float *rawSample = dsp();
            updateFilterCutoff();
            filteredSample[0] = synthFilter.processSample(0, rawSample[0]);
            filteredSample[1] = synthFilter.processSample(1, rawSample[1]);
            auto* outs = outputBuffer.getArrayOfWritePointers();
            outs[0][startSample+sample] += filteredSample[0] * adsrGain.getNextSample();
            outs[1][startSample+sample] += filteredSample[1] * adsrGain.getNextSample();
        }
              
    
    }

    void parameterChanged(const juce::String& paramID, float newValue) override {

        for (int id = 1; id <= 2; id++) {

            if (paramID == (paramIDs::menu + juce::String(id)))
                waveType[id - 1] = newValue;

            else if (paramID == (paramIDs::pitch + juce::String(id)))
                pitch[id - 1] = newValue;

            else if (paramID == (paramIDs::pan + juce::String(id)))
                pan[id - 1] = newValue;

            else if (paramID == (paramIDs::lfo_am_gain + juce::String(id)))
                gainAM[id - 1] = newValue;

            else if (paramID == (paramIDs::lfo_am_rate + juce::String(id)))
                rateAM[id - 1] = newValue;

            else if (paramID == (paramIDs::lfo_fm_gain + juce::String(id)))
                gainFM[id - 1] = newValue;

            else if (paramID == (paramIDs::lfo_fm_rate + juce::String(id)))
                rateFM[id - 1] = newValue;

        }

        if (paramID == paramIDs::blend)
            blend = newValue;

        else if (paramID == paramIDs::master_gain)
            masterGain = newValue;

        else if (paramID == paramIDs::attack) 
        {
            paramADSR.attack = newValue;
            adsrGain.setParameters(paramADSR);
        }

        else if (paramID == paramIDs::decay)
        {
            paramADSR.decay = newValue;
            adsrGain.setParameters(paramADSR);
        }

        else if (paramID == paramIDs::sustain)
        {
            paramADSR.sustain = newValue;
            adsrGain.setParameters(paramADSR);
        }

        else if (paramID == paramIDs::release)
        {
            paramADSR.release = newValue;
            adsrGain.setParameters(paramADSR);
        }

        else if (paramID == paramIDs::filterMenu) 
        {
            setFilterType(newValue);
        }

        else if (paramID == paramIDs::cutOff) 
        {
            cutOff = newValue;
        }

        else if (paramID == paramIDs::resonance) 
        {
            synthFilter.setResonance(newValue);
        }

        else if (paramID == paramIDs::filterGainLFO)
        {
            filterGainLFO = newValue;
        }

        else if (paramID == paramIDs::filterRateLFO)
        {
            filterRateLFO = newValue;
        }

        else if (paramID == paramIDs::filterAttack)
        {
            adsrFilterParams.attack = newValue;
            adsrFilter.setParameters(adsrFilterParams);
        }

        else if (paramID == paramIDs::filterDecay)
        {
            adsrFilterParams.decay = newValue;
            adsrFilter.setParameters(adsrFilterParams);
        }

        else if (paramID == paramIDs::filterSustain)
        {
            adsrFilterParams.sustain = newValue;
            adsrFilter.setParameters(adsrFilterParams);
        }

        else if (paramID == paramIDs::filterRelease)
        {
            adsrFilterParams.release = newValue;
            adsrFilter.setParameters(adsrFilterParams);
        }

        else if (paramID == paramIDs::filterRelease)
        {
            adsrFilterParams.release = newValue;
            adsrFilter.setParameters(adsrFilterParams);
        }

        else if (paramID == paramIDs::filterEnvAmt)
        {
            filterEnvAmt = newValue;
        }
    }

private:
    float sample[2];
    float level;
    float frequency;
    float tailOff = false;
    int waveType[2] = { DEFAULT_MENU, DEFAULT_MENU };
    float pitch[2] = { DEFAULT_PITCH, DEFAULT_PITCH };
    float pan[2] = { DEFAULT_PAN, DEFAULT_PAN };
    float gainAM[2] = { DEFAULT_GAINAM, DEFAULT_GAINAM };
    float rateAM[2] = { DEFAULT_RATEAM, DEFAULT_RATEAM };
    float gainFM[2] = { DEFAULT_GAINFM, DEFAULT_GAINFM };
    float rateFM[2] = { DEFAULT_RATEFM, DEFAULT_RATEFM };
    float masterGain = DEFAULT_MASTERGAIN;
    float blend = DEFAULT_BLEND;
    float filteredSample[2];
    float cutOff = 20.0f;
    float filterGainLFO;
    float filterRateLFO;
    float filterEnvAmt;
    WaveForm oscillator1;
    WaveForm oscillator2;
    WaveForm amplitudeLFO1;
    WaveForm frequencyLFO1;
    WaveForm amplitudeLFO2;
    WaveForm frequencyLFO2;
    juce::ADSR adsrGain;
    juce::ADSR::Parameters paramADSR;
    juce::dsp::StateVariableTPTFilter<float> synthFilter;
    juce::dsp::ProcessSpec synthSpecs;
    WaveForm filterLFO;
    juce::ADSR adsrFilter;
    juce::ADSR::Parameters adsrFilterParams;
};