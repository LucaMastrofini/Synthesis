/*
  ==============================================================================

    WaveForm.h
    Created: 17 Dec 2020 10:09:28pm
    Author:  Masterfine

  ==============================================================================
*/

#pragma once

#include <math.h>
#include <iterator>
#include <iostream>

#define PI  3.1415926535897932384626433832795
#define TWOPI 6.283185307179586476925286766559

class WaveForm {

    float sampleRate = 44100.0;
    float output;
    float phase;
    
public:
    WaveForm();
    float sineWave(float frequency);
    float squareWave(float frequency);
    float sawWave(float frequency);
    float triangularWave(float frequency);
    float noise();
    void setSampleRate(double sampleRT);
};