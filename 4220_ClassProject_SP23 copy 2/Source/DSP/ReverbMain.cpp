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
    fbcfilter3.processSample(x,c) + fbcfilter4.processSample(x, c);
    
    float apf1Output = apf1.processSample(fbcfilterOutput, c);
    float apf2Output = apf2.processSample(apf1Output, c);
    float outSample  = apf3.processSample(apf2Output, c);
    
    return outSample;
}

//dif

void ReverbMain::setTime(float gain) {
    
    fbcfilter1.setFeedback(gain);
    fbcfilter2.setFeedback(gain);
    fbcfilter3.setFeedback(gain);
    fbcfilter4.setFeedback(gain);
    
}



