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
class _4220_ClassProject_SP23AudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::ComboBox::Listener, public juce::Slider::Listener

{
public:
    _4220_ClassProject_SP23AudioProcessorEditor (_4220_ClassProject_SP23AudioProcessor&);
    ~_4220_ClassProject_SP23AudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    virtual void comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) override;
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
    
    juce::LookAndFeel_V2 lookAndFeel2;
    
    juce::TextButton hpfButton; //hpf on off
    
    juce::ComboBox slopeSelector;
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_4220_ClassProject_SP23AudioProcessorEditor)
};
