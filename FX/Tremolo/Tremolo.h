/*
  ==============================================================================

    Tremolo.h
    Created: 16 Jun 2026 9:34:57am
    Author:  Leonida

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

enum class LfoWaveForm {
    sine, triangle
};

namespace tremolo {
    class Tremolo {
public:
    Tremolo();
    void prepare(double sampleRate, int expectedMaxFramesPerBlock);
    void process(juce::AudioBuffer<float>& buffer) noexcept;
    void reset();
    void setWaveForm(LfoWaveForm newWaveForm);
    void setModulationRate(float rateHz);

private:
    //juce::dsp::Oscillator<float> lfo{
    //    [](float x) {
    //        return std::sin(x);
    //    }
    //};

    juce::dsp::Oscillator<float> lfo;

    LfoWaveForm wave = LfoWaveForm::sine;
};
}
