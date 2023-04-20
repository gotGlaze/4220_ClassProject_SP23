/*
  ==============================================================================

    ReverbMain.h
    Created: 19 Apr 2023 10:39:38pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#pragma once

#include "AudioEffect.h"
#include "AllPassFilter.h"
#include "FBCFilter.h"

class ReverbMain : public AudioEffect {
    
public:
//    ~ReverbMain () override{
//        AudioEffect::~AudioEffect();
//    };
    
    float processSample(float x, const int c) override;
    //diffusion?
    void setTime(float gain);
    
private:
    
    const float DSF1  = 1047; //delay samples feedback comb filter
    const float DSF2  = 1149;
    const float DSF3  = 2098;
    
    const float DEPTH = 4;
    const float DSA1  = 200; //delay samples all pass filter
    const float DSA2  = 80;
    
    float feedback = 0.5; //feedback level
    
    const float speedF1  = 1.047;
    const float speedF2  = 1.188;
    const float speedF3  = 1.092;
    
    const float speedA1  = 0.8945;
    const float speedA2  = 0.9839;
    
    FBCFilter fbcfilter1 {DSF1, speedF1, DEPTH};
    FBCFilter fbcfilter2 {DSF2, speedF2, DEPTH};
    FBCFilter fbcfilter3 {DSF3, speedF3, DEPTH};
    
    AllPassFilter apf1 {speedA1, DEPTH, DSA1};
    AllPassFilter apf2 {speedA2, DEPTH, DSA2};
    
};
