/*
  ==============================================================================

    Tremolo.cpp
    Created: 16 Jun 2026 9:35:10am
    Author:  Leonida

  ==============================================================================
*/

#include "Tremolo.h"
namespace tremolo {
    Tremolo::Tremolo()
    {
        setWaveForm(LfoWaveForm::sine);
        lfo.setFrequency(5.f, true);
    }

    void Tremolo::prepare(double sampleRate, int expectedMaxFramesPerBlock)
    {
        const juce::dsp::ProcessSpec processSpec{
           .sampleRate = sampleRate,
           .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
           .numChannels = 1u,
        };
        lfo.prepare(processSpec);
    }

    void Tremolo::process(juce::AudioBuffer<float>& buffer) noexcept
    {
        for (int frameIndex = 0; frameIndex < buffer.getNumSamples(); frameIndex++) {

            const auto lfoValue = lfo.processSample(0.f);

            constexpr auto modulationDepth = 0.4f;
            const auto modulationValue = modulationDepth * lfoValue;

            for (int channelIndex = 0; channelIndex < buffer.getNumChannels(); channelIndex++) {
                //prende il sample dal buffer
                const auto inputSample = buffer.getSample(channelIndex, frameIndex);
                //il sample viene modulato
                const auto outputSample = inputSample * modulationValue;
                //invia output
                buffer.setSample(channelIndex, frameIndex, outputSample);
            }
        }
    }

    void Tremolo::reset()
    {
        lfo.reset();
    }

    void Tremolo::setWaveForm(LfoWaveForm newWaveForm)
    {
        wave = newWaveForm;
        switch (wave) {
            case LfoWaveForm::sine:
                lfo.initialise([](float x) {
                    return std::sin(x);
                });
                break;

            case LfoWaveForm::triangle:
                lfo.initialise([](float x) {
                    return 2.0f * std::abs(x / juce::MathConstants<float>::pi) - 1.0f;
                });
                break;
        }
    }
    void Tremolo::setModulationRate(float rateHz)
    {
        lfo.setFrequency(rateHz);
    }
}