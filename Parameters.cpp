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

        //WAVEFORM=============================================================================

        juce::AudioParameterChoice& createWaveformParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterChoice>(
                juce::ParameterID{"modulation.waveform", versionHint},
                "Modulation waveform", 
                juce::StringArray{"Sine", "Triangle"},
                0);
            return addParameterToProcessor(processor, std::move(parameter)); 
        }

        //ATTACK===============================================================================

        juce::AudioParameterFloat& createAttackParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID{ "modulation.attack", versionHint },
                "Modulation attack",
                juce::NormalisableRange(0.001f, 5.0f),
                0.01f);
            return addParameterToProcessor(processor, std::move(parameter));
        }

        //DECAY================================================================================

        juce::AudioParameterFloat& createDecayParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID{ "modulation.decay", versionHint },
                "Modulation decay",
                juce::NormalisableRange(0.001f, 5.0f),
                0.1f);
            return addParameterToProcessor(processor, std::move(parameter));
        }

        //SUSTAIN==============================================================================

        juce::AudioParameterFloat& createSustainParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID{ "modulation.sustain", versionHint },
                "Modulation sustain",
                juce::NormalisableRange(0.0f, 1.0f),
                0.7f);
            return addParameterToProcessor(processor, std::move(parameter));
        }
        
        //RELEASE==============================================================================

        juce::AudioParameterFloat& createReleaseParameter(juce::AudioProcessor& processor) {
            constexpr auto versionHint = 1;
            auto parameter = std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID{ "modulation.release", versionHint },
                "Modulation release",
                juce::NormalisableRange(0.001f, 10.0f),
                0.3f);
            return addParameterToProcessor(processor, std::move(parameter));
        }


        
    }
    Parameters::Parameters(juce::AudioProcessor& processor)
        :waveform{ createWaveformParameter(processor) }
        , attack{ createAttackParameter(processor) }
        , decay{ createDecayParameter(processor) }
        , sustain{ createSustainParameter(processor) }
        , release{ createReleaseParameter(processor) }
    {
        
    }

}

