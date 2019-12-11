/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
C74GenAudioProcessorEditor::C74GenAudioProcessorEditor (C74GenAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    setSize(200, 220);

    // These define the parameter of our slider object
    targetSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    targetSlider.setRange(-30.0, 0.0, 0.01);
    targetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 12);
    targetSlider.setPopupDisplayEnabled(false, false, this);
    targetSlider.setTextValueSuffix(" LKFS");
    targetSlider.setValue(-14.0);
    targetSlider.setDoubleClickReturnValue(true, -14.0);

    targetLabel.setText("Target", dontSendNotification);
    targetLabel.attachToComponent(&targetSlider, false);
    targetLabel.setJustificationType(Justification::centred);

    // this function adds the slider to the editor
    addAndMakeVisible(&targetSlider);
    addAndMakeVisible(&targetLabel);

    // add the listener to the slider
    targetSlider.addListener(this);
}

C74GenAudioProcessorEditor::~C74GenAudioProcessorEditor()
{
}

//==============================================================================
void C74GenAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(Colour(0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void C74GenAudioProcessorEditor::resized()
{
    int windowHeight = getHeight();
    int windowWidth = getWidth();
    int windowHorizontalCenter = windowWidth / 2;
    int windowVerticalCenter = windowHeight / 2;
    int margin = 20;
    int labelSpace = 40;
    int sliderSize = 160;

    // sets the position and size of the slider with arguments (x, y, width, height)
    targetSlider.setBounds(windowHorizontalCenter - (sliderSize / 2), windowVerticalCenter - (sliderSize / 2), sliderSize, sliderSize);
    // targetLabel.setBounds(0, 20, getWidth(), 20);
}

void C74GenAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider->getName() == targetSlider.getName())
    {
        // Convert targetSlider dB value to absolute
        targetSliderValue = pow(10, slider->getValue() / 20);
        processor.setParameter(0, targetSliderValue);
    }
}