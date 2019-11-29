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
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    C74GenAudioProcessor& processor;
    
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> target;
    std::unique_ptr<Label> targetlabel;


    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (C74GenAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
