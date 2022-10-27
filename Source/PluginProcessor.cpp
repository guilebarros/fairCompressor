#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FairCompressorAudioProcessor::FairCompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    treeState.addParameterListener("input", this);
    treeState.addParameterListener("thresh", this);
    treeState.addParameterListener("ratio", this);
    treeState.addParameterListener("attack", this);
    treeState.addParameterListener("release", this);
    treeState.addParameterListener("output", this);
}

FairCompressorAudioProcessor::~FairCompressorAudioProcessor()
{
    treeState.removeParameterListener("input", this);
    treeState.removeParameterListener("thresh", this);
    treeState.removeParameterListener("ratio", this);
    treeState.removeParameterListener("attack", this);
    treeState.removeParameterListener("release", this);
    treeState.removeParameterListener("output", this);
}

// Parametros do tree state

juce::AudioProcessorValueTreeState::ParameterLayout FairCompressorAudioProcessor::createParameterLayout()
{
    
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    juce::NormalisableRange<float> attackRange = juce::NormalisableRange<float>(0.0f, 200.0f, 1.0f);
    attackRange.setSkewForCentre(50.0f); // mesmo skew do compressor do Logic
    
    juce::NormalisableRange<float> releaseRange = juce::NormalisableRange<float>(5.0f, 5000.0f, 1.0f);
    releaseRange.setSkewForCentre(160.0f);// mesmo skew do compressor do Logic
    
    auto pInput = std::make_unique<juce::AudioParameterFloat>("input", "Input", -60.0f, 24.0f, 0.0f);
    auto pThresh = std::make_unique<juce::AudioParameterFloat>("thresh", "Thresh", 1.0f, 20.0f, 1.0f);
    auto pRatio = std::make_unique<juce::AudioParameterFloat>("ratio", "Ratio", 1.0f, 20.0f, 1.0f);
    auto pAttack = std::make_unique<juce::AudioParameterFloat>("attack", "Attack", attackRange, 50.0f);
    auto pRelease = std::make_unique<juce::AudioParameterFloat>("release", "Release", releaseRange, 160.0f);
    auto pOutput = std::make_unique<juce::AudioParameterFloat>("output", "Output", -60.0f, 24.0f, 0.0f);
    
    params.push_back(std::move(pInput));
    params.push_back(std::move(pThresh));
    params.push_back(std::move(pRatio));
    params.push_back(std::move(pAttack));
    params.push_back(std::move(pRelease));
    params.push_back(std::move(pOutput));
    
    return { params.begin(), params.end() };
    
}

void FairCompressorAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    updateParameters();
}


void FairCompressorAudioProcessor::updateParameters()
{
    inputModule.setGainDecibels(treeState.getRawParameterValue("input")->load());
    compressorModule.setThreshold(treeState.getRawParameterValue("thresh")->load());
    compressorModule.setRatio(treeState.getRawParameterValue("ratio")->load());
    compressorModule.setAttack(treeState.getRawParameterValue("attack")->load());
    compressorModule.setRelease(treeState.getRawParameterValue("output")->load());
    
}

//==============================================================================
const juce::String FairCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FairCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FairCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FairCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FairCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FairCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FairCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FairCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FairCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void FairCompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================


void FairCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // inicializar o spec para os modulos dsp
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    
    // prepara os modulos dsp para processamento
    
    inputModule.prepare(spec);
    inputModule.setRampDurationSeconds(0.02f);
    outputModule.setRampDurationSeconds(0.02f);
    outputModule.prepare(spec);
    compressorModule.prepare(spec);
    updateParameters();
}

void FairCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FairCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FairCompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    juce::dsp::AudioBlock<float> block { buffer };
    
    // processa os modulos DSP
    
    inputModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    compressorModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    outputModule.process(juce::dsp::ProcessContextReplacing<float>(block));

}

//==============================================================================
bool FairCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FairCompressorAudioProcessor::createEditor()
{
     return new FairCompressorAudioProcessorEditor (*this);
    // return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void FairCompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // permite o salvamento dos parametros do plugin
    juce::MemoryOutputStream stream(destData, false);
    treeState.state.writeToStream(stream);

}

void FairCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // recall dos parametros salvos
    auto tree = juce::ValueTree::readFromData(data, size_t(sizeInBytes));
    
    if (tree.isValid())
    {
        treeState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FairCompressorAudioProcessor();
}
