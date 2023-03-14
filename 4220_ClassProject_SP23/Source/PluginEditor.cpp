/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_4220_ClassProject_SP23AudioProcessorEditor::_4220_ClassProject_SP23AudioProcessorEditor (_4220_ClassProject_SP23AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (417, 419);
    bgImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    
    slider1.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //reverb time
    slider1.setBounds(50,50,180,180);
    slider1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider1.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(slider1);
    
    slider2.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //predelay
    slider2.setBounds(300,50,100,100);
    slider2.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider2.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(slider2);
    
    slider3.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //hpf frequency
    slider3.setBounds(50,320,100,100);
    slider3.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider3.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(slider3);
    
    button1.setBounds(50, 230, 55, 35);
    button1.setButtonText("HPF");
    button1.setClickingTogglesState(true);
    button1.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::peru);
    button1.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::red);
    addAndMakeVisible(button1);

    
}

_4220_ClassProject_SP23AudioProcessorEditor::~_4220_ClassProject_SP23AudioProcessorEditor()
{
}

//==============================================================================
void _4220_ClassProject_SP23AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImageAt(bgImage,0,0);
    
}

void _4220_ClassProject_SP23AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
