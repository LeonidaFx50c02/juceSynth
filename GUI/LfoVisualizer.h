/*
  ==============================================================================

    LfoVisualizer.h
    Created: 17 Jun 2026 11:21:57am
    Author:  Leonida

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace synth {
    class LfoVisualizer : public juce::Component {
    private:
        float frequency = 440.f;

    public:
        void setFrequency(float newFrequency);
        void paint(juce::Graphics& g) override;
    };
}