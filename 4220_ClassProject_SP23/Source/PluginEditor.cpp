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
    
    reverbTimeSlider.addListener(this);
    reverbTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //reverb time
    reverbTimeSlider.setBounds(50,40,180,180);
    reverbTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    reverbTimeSlider.setRange(0.0, 5000);
    reverbTimeSlider.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(reverbTimeSlider);
    
    preDelaySlider.addListener(this);
    preDelaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //predelay
    preDelaySlider.setBounds(275,40,100,100);
    preDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    preDelaySlider.setRange(0, 200);
    preDelaySlider.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(preDelaySlider);
    
    hpfSlider.addListener(this);
    hpfSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //hpf frequency
    hpfSlider.setBounds(50,300,100,100);
    hpfSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    hpfSlider.setRange(0, 500);
    hpfSlider.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(hpfSlider);
    
    hpfButton.setBounds(50, 245, 55, 35);
    hpfButton.setButtonText("HPF");
    hpfButton.setClickingTogglesState(true);
    hpfButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::peru);
    hpfButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::red);
    addAndMakeVisible(hpfButton);
    
    slopeSelector.addListener(this);
    slopeSelector.addItem("Choose Slope", 1);
    slopeSelector.addItem("-6dB", 2);
    slopeSelector.addItem("-12dB", 3);
    slopeSelector.addItem("-18dB",4);
    slopeSelector.addItem("-24dB", 5);
    slopeSelector.setBounds(200, 350, 150, 50);
    addAndMakeVisible(slopeSelector);

    wetSlider.addListener(this);
    wetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //reverb time
    wetSlider.setBounds(200,150,180,180);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    wetSlider.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(wetSlider);

    
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


void _4220_ClassProject_SP23AudioProcessorEditor::comboBoxChanged (juce::ComboBox *comboBoxThatHasChanged) {
    if(comboBoxThatHasChanged == &slopeSelector) {
        if(slopeSelector.getSelectedId() == 1) {
            audioProcessor.setEffect(slopeSelector.getSelectedId());
        } else if(slopeSelector.getSelectedId() == 2) {
            audioProcessor.setEffect(slopeSelector.getSelectedId());
        } else if(slopeSelector.getSelectedId() == 3) {
            audioProcessor.setEffect(slopeSelector.getSelectedId());
        } else { //==4
            audioProcessor.setEffect(slopeSelector.getSelectedId());
        }
    }
}

void _4220_ClassProject_SP23AudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    int a;
    if(slider == &preDelaySlider) {
        a = 0;
        //do process
    }
    
    if(slider == &reverbTimeSlider) {
        a = 0;
        //do process
    }
    
    if(slider == &hpfSlider) {
        a = 0;
        //hpf
    }
    
    if(slider == &wetSlider) {
        a = 0;
        //do process
    }
    
}
