/*
  ==============================================================================

    AudioEffect.h
    Created: 21 Feb 2023 1:32:15pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
// This is a generic base class for doing audio processing
// Other effects can inherit from it to use its functionality and variables
class AudioEffect
{
public:
    
    virtual ~AudioEffect() {
        // if there is anything to delete, do it here
    };
    
    // Make this function to be able to be overridden "virtual"
    //virtual float processSample(float x, const int c);
    
    // Make this a "pure" virtual function, must be overridden
    virtual float processSample(float x, const int c) = 0;
    
    void processBlock(juce::AudioBuffer<float> & buffer);
    
    void processInPlace(float * buffer, const int numSamples, const int channel);
    
    void prepareToPlay(float sampleRate, int samplesPerBlock);
    
    //virtual void setKnob(float value);

protected:
    
    float Fs;
    //float knobValue; 
    
private:
    
    
    int bufferSize;
};
