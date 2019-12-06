/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class C74GenAudioProcessorEditor  : public AudioProcessorEditor,
                                    public Slider::Listener
{
public:
    C74GenAudioProcessorEditor (C74GenAudioProcessor&);
    ~C74GenAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    C74GenAudioProcessor& processor;

    Slider targetSlider;
    float targetSliderValue;
    Label targetLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (C74GenAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
