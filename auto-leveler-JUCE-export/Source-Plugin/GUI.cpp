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

#include "GUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GUI::GUI ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    targetLevel.reset (new Slider ("targetLevel"));
    addAndMakeVisible (targetLevel.get());
    targetLevel->setRange (0, 1, 0.01);
    targetLevel->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    targetLevel->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    targetLevel->addListener (this);

    targetLevel->setBounds (0, 48, 216, 144);

    targetLabel.reset (new Label ("targetLabel",
                                  TRANS("Target")));
    addAndMakeVisible (targetLabel.get());
    targetLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    targetLabel->setJustificationType (Justification::centred);
    targetLabel->setEditable (false, false, false);
    targetLabel->setColour (TextEditor::textColourId, Colours::black);
    targetLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    targetLabel->setBounds (0, 16, 216, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GUI::~GUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    targetLevel = nullptr;
    targetLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == targetLevel.get())
    {
        //[UserSliderCode_targetLevel] -- add your slider handling code here..
        //[/UserSliderCode_targetLevel]
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

<JUCER_COMPONENT documentType="Component" className="GUI" componentName="" parentClasses="public Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="targetLevel" id="810d734cf7aead29" memberName="targetLevel"
          virtualName="" explicitFocusOrder="0" pos="0 48 216 144" min="0.0"
          max="1.0" int="0.01" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="targetLabel" id="dd3036810432912d" memberName="targetLabel"
         virtualName="" explicitFocusOrder="0" pos="0 16 216 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Target" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

