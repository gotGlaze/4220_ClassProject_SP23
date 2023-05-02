/*
  ==============================================================================

    ReverbMain.cpp
    Created: 19 Apr 2023 10:39:38pm
    Author:  Kyrah Glaze

  ==============================================================================
*/

#include "ReverbMain.h"

float ReverbMain::processSample(float x, const int c) {
    
    float fbcfilterOutput = fbcfilter1.processSample(x,c) + fbcfilter2.processSample(x,c) +
    fbcfilter3.processSample(x,c);
    
    float apf1Output = apf1.processSample(fbcfilterOutput, c);
    float outSample = apf2.processSample(apf1Output, c);
    
    return outSample;
}

//setDiffusion?

void ReverbMain::setTime(float gain) {
    
    fbcfilter1.setFeedback(gain);
    fbcfilter2.setFeedback(gain);
    fbcfilter3.setFeedback(gain);
    
}



