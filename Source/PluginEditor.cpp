#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FairCompressorAudioProcessorEditor::FairCompressorAudioProcessorEditor (FairCompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    for (int i = 0; i < dials.size(); i++)
    {
        setCommonSliderProps(*dials[i]);
    }

    setSize (1000, 500);
}

FairCompressorAudioProcessorEditor::~FairCompressorAudioProcessorEditor()
{
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
    
    for (int i = 0; i < dials.size(); i++)
    {
        if(i == 0) // checa se eh o primeiro slider
        {
            dials[i]->setBounds(24, 100, 140, 140);
        }
        
        else // baseados no slider anterior (i - 1)
        {
            dials[i]->setBounds(dials[i - 1]->getX() + dials[i - 1]->getWidth(), 100, 140, 140);
        }
    }


}
