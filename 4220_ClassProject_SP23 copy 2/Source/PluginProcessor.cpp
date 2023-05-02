/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_4220_ClassProject_SP23AudioProcessor::_4220_ClassProject_SP23AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "ReverbParameters", createParameterLayout())
#endif
{
}

_4220_ClassProject_SP23AudioProcessor::~_4220_ClassProject_SP23AudioProcessor()
{
}

//value tree state set parameters
juce::AudioProcessorValueTreeState::ParameterLayout _4220_ClassProject_SP23AudioProcessor::createParameterLayout() {
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> ("wetValue","Mix",
                                                                  juce::NormalisableRange<float> (0.f, 1.f),
                                                                  0.4f) );
    params.push_back(std::make_unique<juce::AudioParameterFloat> ("decayTime","Time",
                                                                  juce::NormalisableRange<float> (0.f, 5000.f),
                                                                  100.f) ); //default
    params.push_back(std::make_unique<juce::AudioParameterFloat> ("preDelayTime","Predelay",
                                                                  juce::NormalisableRange<float> (0.f, 200.f),
                                                                  20.f) );
    params.push_back(std::make_unique<juce::AudioParameterFloat> ("hpf","Frequency",
                                                                  juce::NormalisableRange<float> (0.f, 1000.f),
                                                                  500.f));
    return {params.begin(), params.end()}; //version
    
}

//==============================================================================
const juce::String _4220_ClassProject_SP23AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool _4220_ClassProject_SP23AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool _4220_ClassProject_SP23AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool _4220_ClassProject_SP23AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double _4220_ClassProject_SP23AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int _4220_ClassProject_SP23AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int _4220_ClassProject_SP23AudioProcessor::getCurrentProgram()
{
    return 0;
}

void _4220_ClassProject_SP23AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String _4220_ClassProject_SP23AudioProcessor::getProgramName (int index)
{
    return {};
}

void _4220_ClassProject_SP23AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void _4220_ClassProject_SP23AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback initialisation that you need..
    predelay.setFs(sampleRate); predelay.setDelaySamples(0.0f);
    predelay.setDepth(1.0f);
    predelay.setSpeed(10.0f);
    reverb.prepareToPlay(sampleRate, samplesPerBlock);
    bqFilter.setFs(sampleRate);
    
    float rate = 0.1;
    alpha = std::exp(-log(9.f)/(sampleRate * rate));

    sWet.reset(sampleRate, rate);
    sHPF.reset(sampleRate, rate);
}

void _4220_ClassProject_SP23AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool _4220_ClassProject_SP23AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void _4220_ClassProject_SP23AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
//    predelay.setDepth(2.0f);
//    predelay.setSpeed(2.0f);
    
    float predelaySec = predelayMS * 0.001;
    float predelaySamples = predelaySec * Fs;
    predelay.setDelaySamples(predelaySamples);
    
    int numSamples = buffer.getNumSamples();
    
    // GUI values state raw parameter values
    float wetValue = *state.getRawParameterValue("wetValue");
    sWet.setTargetValue(wetValue/100.f); //same for all parameters
    
    float hpfValue = *state.getRawParameterValue("hpf");
    sHPF.setTargetValue(hpfValue);
    
    float decayTime = *state.getRawParameterValue("decayTime");
    setDecayTime(decayTime);
    
    float preDelayTime = *state.getRawParameterValue("preDelayTime");
    setPreDelayTime(preDelayTime);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for(int n = 0; n < numSamples; ++n) {
        float v = sWet.getNextValue();
        //float hpfFreq = sHPF.getNextValue();
        if(count < 8) {
            count++;
        } else {
            count = 0;
            float hpfFreq = sHPF.skip(8);
            bqFilter.setFreq(hpfFreq);
        }
        
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float x = buffer.getWritePointer(channel) [n];
        float verb = predelay.processSample(x, channel);
        verb = reverb.processSample(verb, channel);
        verb = bqFilter.processSample(verb, channel);
    
        float y = ((1.f-v) * x) + (v * verb);
        buffer.getWritePointer(channel) [n] = y;
        
    }
                   
    }
}

//==============================================================================
bool _4220_ClassProject_SP23AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* _4220_ClassProject_SP23AudioProcessor::createEditor()
{
    return new _4220_ClassProject_SP23AudioProcessorEditor (*this);
}

//==============================================================================
void _4220_ClassProject_SP23AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    //current state info
    auto currentState = state.copyState();
    std::unique_ptr<juce::XmlElement> xml( currentState.createXml());
    copyXmlToBinary(*xml, destData);
}

void _4220_ClassProject_SP23AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    //xml state
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if(xml && xml->hasTagName(state.state.getType())) {
        state.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

void _4220_ClassProject_SP23AudioProcessor::setDecayTime(float decayValue) {
    reverb.setTime(decayValue/100.f);
}

void _4220_ClassProject_SP23AudioProcessor::setHPF(float hpfValue) {
    hpf = hpfValue;
    //bqFilter.setFreq(hpf);
    sHPF.setTargetValue(hpfValue);
}


void _4220_ClassProject_SP23AudioProcessor::setPreDelayTime(float pdValue) {
    pdValue = predelayMS;
    predelay.setDelaySamples(predelayMS);
}

void _4220_ClassProject_SP23AudioProcessor::setWet(float wetValue) {
    wet = wetValue/100.f;
    sWet.setTargetValue(wetValue/100.f);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new _4220_ClassProject_SP23AudioProcessor();
}
