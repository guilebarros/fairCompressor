#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "./GUI/LookAndFeel/DialLAF.h"


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
    
    DialStyle customDialLAF;
    
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    
    std::vector<juce::Slider*> dials =
    {
        &inputDial, &threshDial, &ratioDial,
        &attackDial, &releaseDial, &outputDial,
    };
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> threshAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttach;
    
    void attachSliders();
    
    juce::Label inputDialLabel;
    juce::Label threshDialLabel;
    juce::Label ratioDialLabel;
    juce::Label attackDialLabel;
    juce::Label releaseDialLabel;
    juce::Label outputDialLabel;
    
    std::vector<juce::Label*> dialLabels =
    {
        &inputDialLabel, &threshDialLabel, &ratioDialLabel,
        &attackDialLabel, &releaseDialLabel, &outputDialLabel,
    };
    
    void setCommonSliderProps(juce::Slider& slider);
    void setCommonLabelProps(juce::Label& label);

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FairCompressorAudioProcessorEditor)
};
