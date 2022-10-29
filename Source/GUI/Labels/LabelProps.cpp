#include "../../PluginEditor.h"

void FairCompressorAudioProcessorEditor::setCommonLabelProps(juce::Label &label)
{
    addAndMakeVisible(label);
    label.setFont(juce::Font("Helvetica", 16.0f, juce::Font::FontStyleFlags::bold));
    label.setJustificationType(juce::Justification::centred);
}
