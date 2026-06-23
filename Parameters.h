/*
  ==============================================================================

    Parameters.h
    Created: 16 Jun 2026 10:52:10am
    Author:  Leonida

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace synth {
    struct Parameters {
        explicit Parameters(juce::AudioProcessor&);
        
        juce::AudioParameterFloat& attack;
        juce::AudioParameterFloat& decay;
        juce::AudioParameterFloat& sustain;
        juce::AudioParameterFloat& release;

        juce::AudioParameterChoice& waveform;

        JUCE_DECLARE_NON_COPYABLE(Parameters);
        JUCE_DECLARE_NON_MOVEABLE(Parameters);
    };
}