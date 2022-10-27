#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"


class FairCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FairCompressorAudioProcessorEditor (FairCompressorAudioProcessor&);
    ~FairCompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    FairCompressorAudioProcessor& audioProcessor;
    
    juce::Slider inputDial;
    juce::Slider threshDial;
    juce::Slider ratioDial;
    juce::Slider attackDial;
    juce::Slider releaseDial;
    juce::Slider outputDial;
    
    std::vector<juce::Slider*> dials =
    {
        &inputDial, &threshDial, &ratioDial,
        &attackDial, &releaseDial, &outputDial,
    };
    
    void setCommonSliderProps(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FairCompressorAudioProcessorEditor)
};
