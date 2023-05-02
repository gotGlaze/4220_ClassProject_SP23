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
    
    void setTime(float gain);
    
private:
    
    const float DSF1  = 1047; //delay samples feedback comb filter
    const float DSF2  = 1149;
    const float DSF3  = 2098;
    const float DSF4  = 1899;
    
    const float DEPTH = 4;
    const float DEPTH2 = 7;
    const float DSA1  = 80; //delay samples all pass filter
    const float DSA2  = 256;
    const float DSA3 = 120;
    
    float feedback = 0.6; //feedback level
    
    const float speedF1  = 1.047f; //FBCF speed
    const float speedF2  = 1.188f;
    const float speedF3  = 1.092f;
    const float speedF4  = 0.9431f;
    
    const float speedA1  = 0.9945f;
    const float speedA2  = 0.9839f;
    const float speedA3 = 1.1045f;
    
    FBCFilter fbcfilter1 {DSF1, speedF1, DEPTH};
    FBCFilter fbcfilter2 {DSF2, speedF2, DEPTH};
    FBCFilter fbcfilter3 {DSF3, speedF3, DEPTH};
    FBCFilter fbcfilter4 {DSF4, speedF4, DEPTH2};
    
    AllPassFilter apf1 {speedA1, DEPTH, DSA1};
    AllPassFilter apf2 {speedA2, DEPTH2, DSA2};
    AllPassFilter apf3 {speedA3, DEPTH, DSA3};
    
};
