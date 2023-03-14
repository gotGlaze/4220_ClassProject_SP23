/*
  ==============================================================================

    LargeKnob.h
    Created: 14 Mar 2023 2:43:49am
    Author:  Kyrah Glaze

  ==============================================================================
*/

//#include "../JuceLibraryCode/JuceHeader.h"
#include <JuceHeader.h>
#pragma once

class LargeKnob : public juce::LookAndFeel_V2 {
    
public:
    
    juce::Image knob = juce::ImageCache::getFromMemory(BinaryData::knob_large_png, BinaryData::knob_large_pngSize);
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int w, int h, float sliderPos, const float rotartyStartAngle, const float rotaryEndAngle, juce::Slider& slider);
    
    
private:
    
    
    
  
    
};

