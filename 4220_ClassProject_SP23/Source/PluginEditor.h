/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/LargeKnob.h"
#include "Components/SmallKnob.h"

//==============================================================================
/**
*/
class _4220_ClassProject_SP23AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    _4220_ClassProject_SP23AudioProcessorEditor (_4220_ClassProject_SP23AudioProcessor&);
    ~_4220_ClassProject_SP23AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _4220_ClassProject_SP23AudioProcessor& audioProcessor;
    
    juce::Image bgImage;
    juce::Slider slider1; //reverbtime
    juce::Slider slider2; //predelay
    juce::Slider slider3; //hpf freq 
    
    LargeKnob largeKnobLNF;
    SmallKnob smallKnobLNF;
    
    juce::LookAndFeel_V2 lookAndFeel2;
    
    juce::TextButton button1; //hpf on off
    //juce::drop hpfMenu; //slope
    
  
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_4220_ClassProject_SP23AudioProcessorEditor)
};
