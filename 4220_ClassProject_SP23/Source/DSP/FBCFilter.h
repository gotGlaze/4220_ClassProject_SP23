/*
  ==============================================================================

    FBCFilter.h
    Created: 19 Apr 2023 10:54:17pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FractionalDelay.hpp"

class FBCFilter{
    
public:
    
    FBCFilter(float delaySamples, float speed, float depth);
    
    ~FBCFilter();
    
    void processBlock(juce::AudioBuffer<float> &buffer);
    
    void prepareToPlay(float sampleRate);
    
    float processSample(float x, const int c);
    
    void setFeedback(float fbLevel);
    
private:
    
    float fbLevel = 0.f;
    FractionalDelay fracDelay;
    float samples[2] = {0.f};
    
};
