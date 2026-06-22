/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Engine/PluginProcessor.h"
#include "LfoVisualizer.h"

//==============================================================================
/**
*/
class TremoloAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TremoloAudioProcessorEditor (TremoloAudioProcessor&);
    ~TremoloAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    //class RateSliderListener : public juce::Slider::Listener {
    //public:
    //    RateSliderListener(juce::AudioParameterFloat& p, juce::Slider& s) : parameter{p}, slider { s } {
    //        s.addListener(this);
    //    }

    //    ~RateSliderListener() {
    //        slider.removeListener(this);
    //    }

    //    void sliderValueChanged(juce::Slider* s) override {
    //        parameter = static_cast<float>(s->getValue());
    //    }
    //private:
    //    juce::AudioParameterFloat& parameter;
    //    juce::Slider& slider;
    //};
    TremoloAudioProcessor& audioProcessor;
    synth::LfoVisualizer lfoVisualizer;
    juce::TextButton sineButton{ "Sine" };
    juce::TextButton triangleButton{ "Triangle" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TremoloAudioProcessorEditor)
};
