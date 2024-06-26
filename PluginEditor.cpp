#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
/**
 * @brief Construct a new instance of the audio processor editor. This is the window that will be displayed to the user.
 * 
 * @param p the instance of the audio processor that will be used to control the audio processing.
 */
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    // Set the size of the window
    setSize (300, 400);

    // Add the components to the window
    // The frequency slider
    addAndMakeVisible(&soundFrequency);
    soundFrequency.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    soundFrequency.setRange (100.0, 15000.0, 1.0);
    soundFrequency.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    soundFrequency.setPopupDisplayEnabled (true, false, this);
    soundFrequency.setTextValueSuffix (" Hz");
    soundFrequency.setValue(INITFREQVAL);
    soundFrequency.setSkewFactorFromMidPoint(500.0);
    soundFrequency.onValueChange = [this]
    {
        if((*this).processorRef.getCurrentSampleRate() > 0.0)
        {
            updateAngleDelta();
        }
    };

    // The power button
    addAndMakeVisible(onOff);
    onOff.setButtonText(juce::String("Power"));
    onOff.setColour(juce::TextButton::buttonColourId, juce::Colours::black);
    onOff.setColour(juce::TextButton::buttonOnColourId, juce::Colours::white);
    onOff.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    onOff.setColour(juce::TextButton::textColourOnId, juce::Colours::black);
    onOff.setClickingTogglesState(true);

    onOff.onClick = [this]
    {
        (*this).processorRef.setIsOn(onOff.getToggleStateValue()==juce::Value(true));
    };
}

/**
 * @brief Destroy the instance of the audio processor editor (the window)
 * 
 */
AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

/**
 * @brief Computes the angular difference between samples depending on sample rate set in system.
 * 
 */
void AudioPluginAudioProcessorEditor::updateAngleDelta()
{
    auto cyclesPerSample = (*this).soundFrequency.getValue() / (*this).processorRef.getCurrentSampleRate();
    (*this).processorRef.setAngleDelta(cyclesPerSample * 2.0 * juce::MathConstants<double>::pi);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (30.0f);
    g.drawFittedText ("Basic sin oscillator", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

/**
 *  @brief Sets the layout of the plugin window.
 */ 
void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //auto leftMargin = getWidth() * 0.07;
    auto topMargin = getHeight() * 0.05; //TODO layout nicer maybe with illustrator
    auto titleHeight = 30;
    auto vertSpacing = 10;
    auto buttonWidth = getWidth() * 0.2;
    auto buttonHeight = buttonWidth * 0.5;

    auto freqSliderSize = 150;

    onOff.setBounds(getWidth()/2-buttonWidth/2, topMargin+titleHeight+vertSpacing, buttonWidth, buttonHeight);
    soundFrequency.setBounds(getWidth()/2-freqSliderSize/2, 160, freqSliderSize, freqSliderSize);
}
