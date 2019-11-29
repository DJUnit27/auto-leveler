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

    targetlabel.reset (new Label ("targetlabel",
                                  TRANS("Target: 20 LKFS")));
    addAndMakeVisible (targetlabel.get());
    targetlabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    targetlabel->setJustificationType (Justification::centred);
    targetlabel->setEditable (false, false, false);
    targetlabel->setColour (TextEditor::textColourId, Colours::black);
    targetlabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    targetlabel->setBounds (20, 75, 180, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (220, 150);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginGUI::~PluginGUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

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
                 fixedSize="0" initialWidth="220" initialHeight="150">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="targetlabel" id="26cc6c7124cc1702" memberName="targetlabel"
         virtualName="" explicitFocusOrder="0" pos="20 75 180 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Target: 20 LKFS" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

