/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../Engine/PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TremoloAudioProcessorEditor::TremoloAudioProcessorEditor (TremoloAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(lfoVisualizer);
    addAndMakeVisible(sineButton);
    addAndMakeVisible(triangleButton);
    sineButton.onClick = [this] {
        audioProcessor.changeWaveForm(LfoWaveForm::sine);
    };
    triangleButton.onClick = [this] {
        audioProcessor.changeWaveForm(LfoWaveForm::triangle);
    };

    sineButton.setButtonText("Sinusoidale");
    triangleButton.setButtonText("Triangolare");
    setSize (540, 270);
}

TremoloAudioProcessorEditor::~TremoloAudioProcessorEditor()
{

}

//==============================================================================
void TremoloAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::white);
    g.drawLine(10, 170, 530, 170);
}

void TremoloAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto bounds = getLocalBounds();
    sineButton.setBounds(10, 10, 80, 30);
    triangleButton.setBounds(10, 40, 80, 30);
    lfoVisualizer.setBounds(10, 130, 520, 80);

}
