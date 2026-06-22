/*
  ==============================================================================

    Parameters.cpp
    Created: 16 Jun 2026 11:02:27am
    Author:  Leonida

  ==============================================================================
*/

#include "Parameters.h"
namespace synth {
    namespace {
        auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
            auto& parameterReference = *parameter;
            processor.addParameter(parameter.release());
            return parameterReference;
        }

        juce::AudioParameterChoice& createWaveformParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterChoice>(
                juce::ParameterID{"modulation.waveform", versionHint},
                "Modulation waveform", 
                juce::StringArray{"Sine", "Triangle"},
                0);
            return addParameterToProcessor(processor, std::move(parameter)); 
        }
    }
    Parameters::Parameters(juce::AudioProcessor& processor)
        :waveform{createWaveformParameter(processor)}
    {
        
    }
}

