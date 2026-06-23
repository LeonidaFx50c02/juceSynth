/*
  ==============================================================================

    Synth.cpp
    Created: 22 Jun 2026 9:17:25am
    Author:  Leonida

  ==============================================================================
*/

#include "Synth.h"

namespace synth {
   Synth::Synth()
    {
        setWaveForm(LfoWaveForm::sine);
        lfo.setFrequency(440.f, true); // il cambio di f è istantaneo
        //juce::ADSR::Parameters params;
        params.attack = 0.1f;
        params.decay = 0.1f; 
        params.sustain = 0.8f; //level
        params.release = 0.1f;

        adsr.setParameters(params);
    }

    void Synth::prepare(double sampleRate, int expectedMaxFramesPerBlock)
    {
        juce::dsp::ProcessSpec processSpec{
                    .sampleRate = sampleRate,
                    .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
                    .numChannels = 1u,
        };
        lfo.prepare(processSpec);
        adsr.setSampleRate(sampleRate);
    }

    void Synth::process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) noexcept
    {
        //params.attack = parameters.attack.get();
        //params.decay = parameters.decay.get();
        //params.sustain = parameters.sustain.get();
        //params.release = parameters.release.get();

        //auto totalNumOutputChannels = juce::AudioProcessor::getTotalNumOutputChannels();
        for (const auto& metadata : midiMessages) 
        {

            msg = metadata.getMessage();
            int nota = msg.getNoteNumber();

            if (msg.isNoteOn()) 
            {
                notePremute.push_back(nota);

                auto note = msg.getNoteNumber();
                velocity = msg.getFloatVelocity();
                auto freq = juce::MidiMessage::getMidiNoteInHertz(note);
                lfo.setFrequency(freq);
                adsr.noteOn();
                noteIsOn = true;
            }
            if (msg.isNoteOff()) {
                //notePremute.erase(std::remove(notePremute.begin(), notePremute.end(), nota), notePremute.end());
                std::erase(notePremute, nota);

                if (notePremute.empty()) {
                    adsr.noteOff();
                    //DBG(params.release);
                    //DBG(adsr.getNextSample());
                    if (params.release < 0.0001f) {
                        noteIsOn = false;
                    }
                    
                }
                else {
                    int ultNota = notePremute.back();
                    float freq = juce::MidiMessage::getMidiNoteInHertz(ultNota);
                    lfo.setFrequency(freq);
                }

            }
        }
        // per ogni frame
        buffer.clear();
        for (int frameIndex = 0; frameIndex < buffer.getNumSamples(); frameIndex++) {
            // generate the LFO value
            float value = 0.0f;
            if (noteIsOn) {
                value = lfo.processSample(0.0f) * velocity * adsr.getNextSample();
            }

            // per ogni canale del frame
            for (int channelIndex = 0; channelIndex < buffer.getNumChannels(); channelIndex++) {
                buffer.setSample(channelIndex, frameIndex, value);
            }
        }
    }

    void Synth::reset() noexcept
    {
        lfo.reset();
    }

    void Synth::setWaveForm(LfoWaveForm newWaveForm)
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

    void Synth::setAttack(float attack)
    {
        params.attack = attack;
        adsr.setParameters(params);
    }

    void Synth::setDecay(float decay)
    {
        params.decay = decay;
        adsr.setParameters(params);
    }

    void Synth::setSustain(float sustain)
    {
        params.sustain = sustain;
        adsr.setParameters(params);
    }

    void Synth::setRelease(float release)
    {
        params.release = release;
        adsr.setParameters(params);
    }

}
