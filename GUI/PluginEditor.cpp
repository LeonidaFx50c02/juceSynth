/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../Engine/PluginProcessor.h"
#include "PluginEditor.h"
#include <string>

namespace {
    void setupSlider(juce::Slider& slider, float rangeMin, float rangeMax, float interval) {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider.setPopupDisplayEnabled(true, true, nullptr);
        slider.setRange(rangeMin, rangeMax, interval);
        slider.setNumDecimalPlacesToDisplay(2);
    }

    void setupLabel(juce::Label& label, std::string nome) {
        label.setText(nome, juce::dontSendNotification);
        //label.setColour(juce::Label::textColourId, juce::Colours::black);
        label.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    }
}
//==============================================================================
TremoloAudioProcessorEditor::TremoloAudioProcessorEditor (TremoloAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
    , attackAttachment{ p.getParameterRefs().attack, attackSlider }
    , decayAttachment{ p.getParameterRefs().decay, decaySlider }
    , sustainAttachment{ p.getParameterRefs().sustain, sustainSlider }
    , releaseAttachment{ p.getParameterRefs().release, releaseSlider }
    
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

    setupSlider(attackSlider, 0.001f, 5.0f, 0.01);
    setupSlider(decaySlider, 0.001f, 5.0f, 0.01);
    setupSlider(sustainSlider, 0.0f, 1.0f, 0.01);
    setupSlider(releaseSlider, 0.001f, 10.0f, 0.01);

    attackSlider.onValueChange = [this]
        {
            audioProcessor.setAttack((float)attackSlider.getValue());
        };
    decaySlider.onValueChange = [this]
        {
            audioProcessor.setDecay((float)decaySlider.getValue());
        };
    sustainSlider.onValueChange = [this]
        {
            audioProcessor.setSustain((float)sustainSlider.getValue());
        };
    releaseSlider.onValueChange = [this]
        {
            audioProcessor.setRelease((float)releaseSlider.getValue());
        };
    
    setupLabel(attackLabel, "Attack");
    setupLabel(decayLabel, "Decay");
    setupLabel(sustainLabel, "Sustain");
    setupLabel(releaseLabel, "Release");

    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(releaseLabel);

    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
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

    attackLabel.setBounds(100, 20, 60, 20);
    attackSlider.setBounds(90, 40, 80, 80);

    decayLabel.setBounds(190, 20, 60, 20);
    decaySlider.setBounds(180, 40, 80, 80);

    sustainLabel.setBounds(280, 20, 60, 20);
    sustainSlider.setBounds(270, 40, 80, 80);

    releaseLabel.setBounds(370, 20, 60, 20);
    releaseSlider.setBounds(360, 40, 80, 80);

}

