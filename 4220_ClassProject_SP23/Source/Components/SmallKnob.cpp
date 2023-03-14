/*
  ==============================================================================

    SmallKnob.cpp
    Created: 14 Mar 2023 2:44:04am
    Author:  Kyrah Glaze

  ==============================================================================
*/

#include "SmallKnob.h"

void SmallKnob::drawRotarySlider (juce::Graphics& g, int x, int y, int w, int h, float sliderPos, const float rotartyStartAngle, const float rotaryEndAngle, juce::Slider& slider) {
    
    
    const float angle = rotartyStartAngle + sliderPos * (rotaryEndAngle - rotartyStartAngle);
    juce::AffineTransform rotator;
    g.drawImageTransformed(knob, rotator.rotated(angle, (float)(knob.getWidth()/2), (float)(knob.getHeight()/2)));
    
    
}
