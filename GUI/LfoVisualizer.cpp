/*
  ==============================================================================

    LfoVisualizer.cpp
    Created: 17 Jun 2026 11:22:56am
    Author:  Leonida

  ==============================================================================
*/

#include "LfoVisualizer.h"

namespace synth {
    void LfoVisualizer::setFrequency(float newFrequency)
    {
        frequency = newFrequency;
        repaint();
    }

    void LfoVisualizer::paint(juce::Graphics& g)
    {
        juce::Path sine;

        const auto halfHeight =
            getHeight() / 2;

        const auto amplitude =
            halfHeight; //1 -> 0 | 0 -> -1 | -1 -> 0

        sine.startNewSubPath(0, halfHeight);

        for (auto x = 1; x <= getWidth(); x++) {
            const float phase =
                juce::MathConstants<float>::twoPi * x / getWidth();

            float time =
                (float)x / (float)getWidth();

            const float y =
                halfHeight - amplitude * std::sin(juce::MathConstants<float>::twoPi * frequency * time);

            sine.lineTo((float)x, y);
        }

        g.strokePath(sine, juce::PathStrokeType{ 2.f });
    }
}

