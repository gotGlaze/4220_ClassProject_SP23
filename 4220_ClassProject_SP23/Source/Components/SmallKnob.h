/*
  ==============================================================================

    SmallKnob.h
    Created: 14 Mar 2023 2:44:04am
    Author:  Kyrah Glaze

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once

class SmallKnob : public juce::LookAndFeel_V2 {
    
public:
    
    juce::Image knob = juce::ImageCache::getFromMemory(BinaryData::knob_small_png, BinaryData::knob_small_pngSize);
    
    void drawRotarySlider (juce::Graphics& g, int x, int y, int w, int h, float sliderPos, const float rotartyStartAngle, const float rotaryEndAngle, juce::Slider& slider);
    
    
private:
    
    
  
    
};
