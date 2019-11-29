/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginGUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginGUI::PluginGUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    target.reset (new Slider ("target"));
    addAndMakeVisible (target.get());
    target->setTooltip (TRANS("Target output level"));
    target->setRange (-70, 0, 0.01);
    target->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    target->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    target->addListener (this);

    target->setBounds (20, 40, 180, 180);

    targetlabel.reset (new Label ("targetlabel",
                                  TRANS("Target")));
    addAndMakeVisible (targetlabel.get());
    targetlabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    targetlabel->setJustificationType (Justification::centred);
    targetlabel->setEditable (false, false, false);
    targetlabel->setColour (TextEditor::textColourId, Colours::black);
    targetlabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    targetlabel->setBounds (20, 10, 180, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (220, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginGUI::~PluginGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    target = nullptr;
    targetlabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginGUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginGUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginGUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == target.get())
    {
        //[UserSliderCode_target] -- add your slider handling code here..
        //[/UserSliderCode_target]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginGUI" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="220" initialHeight="300">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="target" id="62934c1b7f2ed7c0" memberName="target" virtualName=""
          explicitFocusOrder="0" pos="20 40 180 180" tooltip="Target output level"
          min="-70.0" max="0.0" int="0.01" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="targetlabel" id="26cc6c7124cc1702" memberName="targetlabel"
         virtualName="" explicitFocusOrder="0" pos="20 10 180 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Target" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

