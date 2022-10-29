#include "../../PluginEditor.h"


void FairCompressorAudioProcessorEditor::setCommonSliderProps(juce::Slider &slider)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 72, 36);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::whitesmoke.darker(0.8f));
    slider.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colours::black.brighter(0.25f));
    slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::fromFloatRGBA(0.392f, 0.584f, 0.929f, 1.0f).darker(1.0f));
    slider.setLookAndFeel(&customDialLAF);
    
    shadowProperties.radius = 24;
    shadowProperties.offset = juce::Point<int> (0,0);
    shadowProperties.colour = juce::Colours::black;
    dialShadow.setShadowProperties (shadowProperties);
    slider.setComponentEffect(&dialShadow);
    
}
