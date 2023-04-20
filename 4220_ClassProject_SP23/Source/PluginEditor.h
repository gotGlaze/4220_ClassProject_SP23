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
class _4220_ClassProject_SP23AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener

{
public:
    _4220_ClassProject_SP23AudioProcessorEditor (_4220_ClassProject_SP23AudioProcessor&);
    ~_4220_ClassProject_SP23AudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider *slider) override;
    //virtual void buttonClicked(juce::Button* button);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    _4220_ClassProject_SP23AudioProcessor& audioProcessor;
    
    juce::Image bgImage;
    juce::Slider reverbTimeSlider; //reverbtime
    juce::Slider preDelaySlider; //predelay
    juce::Slider hpfSlider; //hpf freq
    juce::Slider wetSlider; //gain/mix
    
    LargeKnob largeKnobLNF;
    SmallKnob smallKnobLNF;
    
    juce::Label reverbTimeLabel;
    juce::Label preDelayLabel;
    juce::Label wetLabel;
    juce::Label hpfLabel;
    
    juce::Label mainTitle;
    
    juce::LookAndFeel_V2 lookAndFeel2;
    
//value tree 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_4220_ClassProject_SP23AudioProcessorEditor)
};
