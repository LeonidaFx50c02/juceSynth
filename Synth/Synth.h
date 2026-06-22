/*
  ==============================================================================

    Synth.h
    Created: 18 Jun 2026 11:57:48am
    Author:  Leonida

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

enum class LfoWaveForm {
    sine, triangle
};

namespace synth {
    class Synth {
    public:
        Synth();

        void prepare(double sampleRate, int expectedMaxFramesPerBlock);

        void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) noexcept;

        void reset() noexcept;

        void setWaveForm(LfoWaveForm newWaveForm);

    private:
        // You should put class members and private functions here
        juce::dsp::Oscillator<float> lfo;
        bool noteIsOn = false;
        juce::MidiMessage msg;
        std::vector<int> notePremute;
        LfoWaveForm wave = LfoWaveForm::sine;
        float velocity; 
    };
}  // namespace tremolo