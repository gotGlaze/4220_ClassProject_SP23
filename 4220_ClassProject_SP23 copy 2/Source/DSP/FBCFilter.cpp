/*
  ==============================================================================

    FBCFilter.cpp
    Created: 19 Apr 2023 10:54:17pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#include "FBCFilter.h"


FBCFilter::FBCFilter(float delayInSamples, float speed, float depth){
    fracDelay.setDelaySamples(delayInSamples);
    fracDelay.setSpeed(speed);
    fracDelay.setDepth(depth);
}

FBCFilter::~FBCFilter() {};

void FBCFilter::setFeedback(float fbLevel) {
    this->fbLevel = fbLevel;
}

void FBCFilter::prepareToPlay(float sampleRate) {
    fracDelay.setFs(sampleRate);
}

float FBCFilter::processSample(float x, const int c) {
    float r;
    r = x + fbLevel * samples[c];
    samples[c] = fracDelay.processSample(r, c);
    return samples[c];
}

void FBCFilter::processBlock(juce::AudioBuffer<float> &buffer) {
    
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    for(int c = 0; c < numChannels; c++) {
        for(int n = 0; n < numSamples; n++) {
            float x = buffer.getWritePointer(c) [n];
            x = processSample(x,c);
            buffer.getWritePointer(c) [n] = x;
        }
    }
}




