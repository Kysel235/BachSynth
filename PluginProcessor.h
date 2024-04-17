#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#define INITFREQVAL 440.0

//==============================================================================
class AudioPluginAudioProcessor : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    double getCurrentSampleRate() const { return currentSampleRate; }
    void setCurrentSampleRate(double sampleRate) { currentSampleRate = sampleRate; }

    double getCurrentAngle() const { return currentAngle; }
    void setCurrentAngle(double angle) { currentAngle = angle; }

    double getAngleDelta() const { return angleDelta; }
    void setAngleDelta(double delta) { angleDelta = delta; }

    bool getIsOn() const { return isOn; }
    void setIsOn(bool state) { isOn = state; }

private:
    double currentSampleRate{0.0};
    double currentAngle{0.0};
    double angleDelta{0.0};
    bool isOn{false};
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
