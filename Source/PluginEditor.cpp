#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FairCompressorAudioProcessorEditor::FairCompressorAudioProcessorEditor (FairCompressorAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
, inputDialLabel("Input", "Input")
, threshDialLabel("Thresh", "Thresh")
, ratioDialLabel("Ratio", "Ratio")
, attackDialLabel("Attack", "Attack")
, releaseDialLabel("Release", "Release")
, outputDialLabel("Output", "Output")
{
for (int i = 0; i < dials.size(); i++)
{
    setCommonSliderProps(*dials[i]);
}

attachSliders();

for (int i = 0; i < dialLabels.size(); i++)
{
    setCommonLabelProps(*dialLabels[i]);
    dialLabels[i]->attachToComponent(dials[i], false);
}


setSize (1000, 500);
juce::AudioProcessorEditor::setResizable(true, true);
juce::AudioProcessorEditor::setResizeLimits(getWidth() * 0.75, getHeight() * 0.75, getWidth() * 1.25, getHeight() * 1.25);
juce::AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
}

FairCompressorAudioProcessorEditor::~FairCompressorAudioProcessorEditor()
{
    for (auto& dial : dials)
    {
        dial->setLookAndFeel(nullptr);
    }
    dials.clear();
    dials.shrink_to_fit();
}

//==============================================================================
void FairCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // o component eh opaco, entao devemos preencher o background com uma cor solida
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromRGB(48, 42, 53).darker(0.75), getHeight(), juce::Colour::fromRGB(40, 42, 53).brighter(0.02f), getHeight() * 0.4f));
    g.fillRect(getLocalBounds());

}

void FairCompressorAudioProcessorEditor::resized()
{
    
    auto dialSize = getWidth() * 0.18f;
    auto mainLeftMargin = getWidth() * 0.25f;
    auto leftMargin = getWidth() * 0.03f;
    auto secondRowHeight = 1.3f;
    
    inputDial.setBounds(leftMargin, 50, dialSize, dialSize);
    threshDial.setBounds(mainLeftMargin, 50, dialSize, dialSize);
    ratioDial.setBounds(threshDial.getX() + threshDial.getWidth(),50, dialSize, dialSize);
    
    outputDial.setBounds(leftMargin, inputDial.getY() + inputDial.getHeight() * secondRowHeight, dialSize, dialSize);
    attackDial.setBounds(threshDial.getX(), outputDial.getY(), dialSize, dialSize);
    releaseDial.setBounds(ratioDial.getX(), outputDial.getY(), dialSize, dialSize);
    

    

}
