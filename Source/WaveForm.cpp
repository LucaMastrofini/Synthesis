/*
  ==============================================================================

    WaveForm.cpp
    Created: 17 Dec 2020 10:09:28pm
    Author:  Masterfine

  ==============================================================================
*/

#include "WaveForm.h"

// Naive Triangular Wave :: Oscilla tra -1.0 e +1.0
        //float sampleValue = 4.0f * abs(mCurrentPhase - 0.5f) - 1.0f;

        // Naive Sawtooth Wave :: Oscilla tra -1.0 e +1.0
        //float sampleValue = mCurrentPhase - 0.5f;

WaveForm::WaveForm(){
    
    output = 0.0f;
    phase = 0.0f;
}

float WaveForm::sineWave(float frequency)
{
    if (phase >= 1.0f) phase -= 1.0f;
    output = sin(phase * (TWOPI));
    phase += (frequency / (sampleRate));
    return (output);
}

float WaveForm::squareWave(float frequency)
{
    if (phase >= 1.0f) phase -= 1.0f;
    if (sin(phase * (TWOPI)) >= 0.0f)
        output = 0.5f;
    else
        output = -0.5f;

    phase += (frequency / (sampleRate));
    return(output);
}

float WaveForm::sawWave(float frequency)
{
    output = 2.0f*phase - 1.0f;
    if (phase >= 1.0f) phase -= 1.0f;
    phase += ((frequency)/(sampleRate));
    return(output);
}

float WaveForm::triangularWave(float frequency) 
{ 
    if (phase >= 1.0) phase -= 1.0f;
    output = 4.0f * abs(phase - 0.5f) - 1.0f;
    phase += ((frequency) / (sampleRate ));
    return(output);
}

float WaveForm::noise() {

    float output = rand() / (float)RAND_MAX; //random di juce è meglio

    return(output);
}

void WaveForm::setSampleRate(double sampleRT) {
    sampleRate = sampleRT;
}

