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
    
    //Reverb Time
    //reverbTimeSlider.addListener(this);
    reverbTimeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    reverbTimeSlider.setBounds(40,80,145,180);
    reverbTimeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    reverbTimeSlider.setRange(0.0, 5000);
    reverbTimeSlider.setValue(60.0);
    reverbTimeSlider.setTextValueSuffix(" ms");
    reverbTimeSlider.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(reverbTimeSlider);
    
    reverbTimeLabel.setText("Reverb Time", juce::dontSendNotification);
    reverbTimeLabel.attachToComponent(&reverbTimeSlider, false);
    reverbTimeLabel.setJustificationType(juce::Justification::centredBottom);
    reverbTimeLabel.setFont(juce::Font("Times New Roman", 20.0, juce::Font::bold));
    
    
    //Predelay
    //preDelaySlider.addListener(this);
    preDelaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //predelay
    preDelaySlider.setBounds(280,100,87,100);
    preDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    preDelaySlider.setRange(0, 200);
    preDelaySlider.setValue(20.0);
    preDelaySlider.setTextValueSuffix(" ms");
    preDelaySlider.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(preDelaySlider);
    
    preDelayLabel.setText("Predelay", juce::dontSendNotification);
    preDelayLabel.attachToComponent(&preDelaySlider, false);
    preDelayLabel.setJustificationType(juce::Justification::centredLeft);
    preDelayLabel.setFont(juce::Font("Times New Roman", 20.0, juce::Font::bold));
    
    
    //High pass filter
    //hpfSlider.addListener(this);
    hpfSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //hpf frequency
    hpfSlider.setBounds(70,300,87,100);
    hpfSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 20);
    hpfSlider.setRange(0, 1000); //0 to 500 previously
    hpfSlider.setValue(200.f);
    hpfSlider.setTextValueSuffix(" Hz");
    hpfSlider.setLookAndFeel(&smallKnobLNF);
    addAndMakeVisible(hpfSlider);
    
    hpfLabel.setText("HPF", juce::dontSendNotification);
    hpfLabel.attachToComponent(&hpfSlider, false);
    hpfLabel.setJustificationType(juce::Justification::centredLeft);
    hpfLabel.setFont(juce::Font("Times New Roman", 20.0, juce::Font::bold));
    
    //Wet dry mix
    //wetSlider.addListener(this);
    wetSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag); //reverb time
    wetSlider.setBounds(245,230,145,180);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    wetSlider.setRange(0.f, 1.f);
    wetSlider.setLookAndFeel(&largeKnobLNF);
    addAndMakeVisible(wetSlider);
                    //feedback rn
    wetLabel.setText("Dry to Wet Mix", juce::dontSendNotification);
    wetLabel.attachToComponent(&wetSlider, false);
    wetLabel.setJustificationType(juce::Justification::centredBottom);
    wetLabel.setFont(juce::Font("Times New Roman", 20.0, juce::Font::bold));
    
    //Main Title
    mainTitle.setText("4220 Reverb", juce::dontSendNotification);
    mainTitle.setJustificationType(juce::Justification::centred);
    mainTitle.setBounds(95,5,250,40);
    mainTitle.setFont(juce::Font("Times New Roman", 35.0, juce::Font::bold));
    addAndMakeVisible(mainTitle);
    
//    reverbTimeSlider.resized();
//    hpfSlider.resized();
//    preDelaySlider.resized();
//    wetSlider.resized();
    
//    setResizable(true, true);
//    setSize(800,300);
//    setResizeLimits(412, 140, 1600, 550);
    
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,
                                                                                           "wetValue", wetSlider));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,
                                                                                           "decayTime", wetSlider));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,
                                                                                           "preDelayTime", wetSlider));
    sliderAttachment.emplace_back(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.state,
                                                                                           "hpf", wetSlider));

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


//void _4220_ClassProject_SP23AudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
//
//    if(slider == &preDelaySlider) {
//        audioProcessor.setPreDelayTime(preDelaySlider.getValue());
//    }
//
//    if(slider == &reverbTimeSlider) {
//        audioProcessor.setDecayTime(reverbTimeSlider.getValue());
//    }
//
//    if(slider == &hpfSlider) {
//        audioProcessor.setHPF(hpfSlider.getValue());
//        //hpf
//    }
//
//    if(slider == &wetSlider) {
//        audioProcessor.setWet(wetSlider.getValue());
//    }
//
//}
