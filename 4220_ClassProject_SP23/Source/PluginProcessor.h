/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#pragma once

#include <JuceHeader.h>
#include "DSP/AudioEffect.h"
#include "DSP/ReverbMain.h"
#include "DSP/AllPassFilter.h"
#include "DSP/Biquad.h"
#include "DSP/FractionalDelay.hpp"

//==============================================================================
/**
*/
class _4220_ClassProject_SP23AudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    _4220_ClassProject_SP23AudioProcessor();
    ~_4220_ClassProject_SP23AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float decayTime;
    void setDecayTime(float decayValue);

    float wet;//float wet = 0.5f;
    float smoothWet[2] = {0.f};
    float alpha = 0.999f;
    void setWet(float wetValue);
    
    float hpf;
    void setHPF(float hpfValue);
    
    float predelayMS = 0.0f;
    float preDelayTime;
    //void setPreDelayTime(float pdValue);
    void setPreDelayTime(float pdValue);
    
//    void setEffect(int effectNum) {
//        if(effectNum == 1) {
//            effect = std::unique_ptr<AudioEffect> ();
//        } else if (effectNum == 2) {
//            effect = std::unique_ptr<AudioEffect> ();
//        } else if (effectNum == 3) {
//            effect = std::unique_ptr<AudioEffect> ();
//        } else {
//            effect = std::unique_ptr<AudioEffect> ();
//        }
//    };
    
private:
    //std::unique_ptr<AudioEffect> effect;
    
    FractionalDelay predelay; //???
    float Fs = 48000.f;
    ReverbMain reverb;
    Biquad bqFilter {Biquad::FilterType::HPF, 0.7071f};
    int count = 0;
    
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> sWet {0.f};
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> sHPF {200.f};
    
public:
    juce::AudioProcessorValueTreeState state;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //=====================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (_4220_ClassProject_SP23AudioProcessor)
};
