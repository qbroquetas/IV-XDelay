/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
IvxDelayAudioProcessorEditor::IvxDelayAudioProcessorEditor (IvxDelayAudioProcessor& ownerProc)
    : AudioProcessorEditor(ownerProc), processor(ownerProc)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (input_gain_slider = new Slider ("Input Gain"));
    input_gain_slider->setRange (0, 8, 0);
    input_gain_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    input_gain_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 10);
    input_gain_slider->setColour (Slider::trackColourId, Colour (0xff450800));
    input_gain_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffcd1500));
    input_gain_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff9e1100));
    input_gain_slider->setColour (Slider::textBoxTextColourId, Colour (0xffa81300));
    input_gain_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x00880f00));
    input_gain_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    input_gain_slider->setSkewFactor (0);

    addAndMakeVisible (output_gain_slider = new Slider ("Output Gain"));
    output_gain_slider->setRange (0, 8, 0);
    output_gain_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    output_gain_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 10);
    output_gain_slider->setColour (Slider::trackColourId, Colour (0xff0a3100));
    output_gain_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xff188100));
    output_gain_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff126100));
    output_gain_slider->setColour (Slider::textBoxTextColourId, Colour (0xff167500));
    output_gain_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    output_gain_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    output_gain_slider->setSkewFactor (0);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Input Gain")));
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xffb50000));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Output Gain")));
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colour (0xff167700));
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (delay_time_slider = new Slider ("Delay Time"));
    delay_time_slider->setRange (20, 1999, 1);
    delay_time_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    delay_time_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 10);
    delay_time_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    delay_time_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff8600));
    delay_time_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffb55f00));
    delay_time_slider->setColour (Slider::textBoxTextColourId, Colour (0xffda6a00));
    delay_time_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    delay_time_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    delay_time_slider->setSkewFactor (0);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Time [ms]")));
    label3->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colour (0xffdd7400));
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (feedback_gain_slider = new Slider ("Feedback Gain"));
    feedback_gain_slider->setRange (0, 1, 0);
    feedback_gain_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    feedback_gain_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 10);
    feedback_gain_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    feedback_gain_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff8600));
    feedback_gain_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffb55f00));
    feedback_gain_slider->setColour (Slider::textBoxTextColourId, Colour (0xffda6a00));
    feedback_gain_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    feedback_gain_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    feedback_gain_slider->setSkewFactor (0);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Feedback")));
    label4->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colour (0xffdd7400));
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (wow_rate_slider = new Slider ("Wow Rate"));
    wow_rate_slider->setRange (0, 4, 0);
    wow_rate_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wow_rate_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 40, 10);
    wow_rate_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    wow_rate_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffdcbf00));
    wow_rate_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffa38d00));
    wow_rate_slider->setColour (Slider::textBoxTextColourId, Colour (0xffa38d00));
    wow_rate_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    wow_rate_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    wow_rate_slider->setSkewFactor (0);

    addAndMakeVisible (wow_amt_slider = new Slider ("Wow Amt"));
    wow_amt_slider->setRange (0, 1, 0);
    wow_amt_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    wow_amt_slider->setTextBoxStyle (Slider::NoTextBox, true, 40, 10);
    wow_amt_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    wow_amt_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffdcbf00));
    wow_amt_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffa38d00));
    wow_amt_slider->setColour (Slider::textBoxTextColourId, Colour (0xffda6a00));
    wow_amt_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    wow_amt_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    wow_amt_slider->setSkewFactor (0);

    addAndMakeVisible (flutter_amt_slider = new Slider ("Flutter Rate"));
    flutter_amt_slider->setRange (0, 1, 0);
    flutter_amt_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    flutter_amt_slider->setTextBoxStyle (Slider::NoTextBox, true, 40, 10);
    flutter_amt_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    flutter_amt_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xff6bd700));
    flutter_amt_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff4d9a00));
    flutter_amt_slider->setColour (Slider::textBoxTextColourId, Colour (0xffda6a00));
    flutter_amt_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    flutter_amt_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    flutter_amt_slider->setSkewFactor (0);

    addAndMakeVisible (flutter_rate_slider = new Slider ("Flutter Rate"));
    flutter_rate_slider->setRange (10, 50, 1);
    flutter_rate_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    flutter_rate_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 40, 10);
    flutter_rate_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    flutter_rate_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xff6bd700));
    flutter_rate_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xff4d9a00));
    flutter_rate_slider->setColour (Slider::textBoxTextColourId, Colour (0xff4d9a00));
    flutter_rate_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    flutter_rate_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    flutter_rate_slider->setSkewFactor (0);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Wow")));
    label5->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colour (0xffa38d00));
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Flutter")));
    label6->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colour (0xff4d9a00));
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Rate:")));
    label7->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colour (0xff9c9c9c));
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Amt:")));
    label8->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (Label::textColourId, Colour (0xff9c9c9c));
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (scrape_amt_slider = new Slider ("Scrape Amt"));
    scrape_amt_slider->setRange (0, 1, 0);
    scrape_amt_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    scrape_amt_slider->setTextBoxStyle (Slider::NoTextBox, true, 40, 10);
    scrape_amt_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    scrape_amt_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff6f00));
    scrape_amt_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffff6f00));
    scrape_amt_slider->setColour (Slider::textBoxTextColourId, Colour (0xffff6f00));
    scrape_amt_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    scrape_amt_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    scrape_amt_slider->setSkewFactor (0);

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Scrape")));
    label9->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (Label::textColourId, Colour (0xffff6f00));
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (bias_slider = new Slider ("Bias"));
    bias_slider->setRange (2, 5, 1);
    bias_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    bias_slider->setTextBoxStyle (Slider::TextBoxBelow, true, 40, 10);
    bias_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    bias_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffffc900));
    bias_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffc49b00));
    bias_slider->setColour (Slider::textBoxTextColourId, Colour (0xffd3a700));
    bias_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    bias_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Bias")));
    label10->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (Label::textColourId, Colour (0xffcda100));
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("IPS")));
    label11->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (Label::textColourId, Colour (0xffdd7400));
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("3.75")));
    label12->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (Label::textColourId, Colour (0xffdd7400));
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("15")));
    label13->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (Label::textColourId, Colour (0xffdd7400));
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("7.5")));
    label14->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (Label::textColourId, Colour (0xffdd7400));
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (IPS_slider = new Slider ("IPS"));
    IPS_slider->setRange (1, 3, 1);
    IPS_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    IPS_slider->setTextBoxStyle (Slider::NoTextBox, true, 50, 10);
    IPS_slider->setColour (Slider::trackColourId, Colour (0xff082a00));
    IPS_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffff8600));
    IPS_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffb55f00));
    IPS_slider->setColour (Slider::textBoxTextColourId, Colour (0xffda6a00));
    IPS_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    IPS_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    IPS_slider->setSkewFactor (0);

    addAndMakeVisible (noise_level_slider = new Slider ("Noise Level"));
    noise_level_slider->setRange (0, 4, 0);
    noise_level_slider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    noise_level_slider->setTextBoxStyle (Slider::NoTextBox, true, 40, 10);
    noise_level_slider->setColour (Slider::trackColourId, Colour (0xffba00b0));
    noise_level_slider->setColour (Slider::rotarySliderFillColourId, Colour (0xffee00ff));
    noise_level_slider->setColour (Slider::rotarySliderOutlineColourId, Colour (0xffba00b0));
    noise_level_slider->setColour (Slider::textBoxTextColourId, Colour (0xff4d9a00));
    noise_level_slider->setColour (Slider::textBoxBackgroundColourId, Colour (0x000f5100));
    noise_level_slider->setColour (Slider::textBoxOutlineColourId, Colour (0x00808080));
    noise_level_slider->setSkewFactor (0);

    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("Noise")));
    label15->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (Label::textColourId, Colour (0xffba00b0));
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (750, 145);


    //[Constructor] You can add your own custom stuff here..

    //implementation of the helper methods that tie GUI objects to paramters in the value tree class.
    mInputGainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_INGAIN, *input_gain_slider);
    mOutputGainAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_OUTGAIN, *output_gain_slider);
    mDelayTimeAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_DELAYTIME, *delay_time_slider);
    mFeedbackGainAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FEEDBACKGAIN, *feedback_gain_slider);
    mWowAmtAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_WOWAMT, *wow_amt_slider);
    mWowRateAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_WOWRATE, *wow_rate_slider);
    mFlutterAmtAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FLUTTERAMT, *flutter_amt_slider);
    mFlutterRateAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_FLUTTERRATE, *flutter_rate_slider);
    mScrapeAmtAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_SCRAPEAMT, *scrape_amt_slider);
    mBiasAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_BIAS, *bias_slider);
    mIPSAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_IPS, *IPS_slider);
    mNoiseLevelAttachment = new  AudioProcessorValueTreeState::SliderAttachment(processor.getState(), PARAM_NOISELEVEL, *noise_level_slider);

    startTimer(200); //starts timer to refresh manual user interface controls. added for compatibility.


    //[/Constructor]
}

IvxDelayAudioProcessorEditor::~IvxDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..

  // The value tree class methods have to be deleted
  // before the GUI objects to avoid crashes
  mInputGainAttachment = nullptr;
  mOutputGainAttachment = nullptr;
  mDelayTimeAttachment = nullptr;
  mFeedbackGainAttachment = nullptr;
  mWowAmtAttachment = nullptr;
  mWowRateAttachment = nullptr;
  mFlutterAmtAttachment = nullptr;
  mFlutterRateAttachment = nullptr;
  mScrapeAmtAttachment = nullptr;
  mBiasAttachment = nullptr;
  mIPSAttachment = nullptr;
  mNoiseLevelAttachment = nullptr;
    //[/Destructor_pre]

    input_gain_slider = nullptr;
    output_gain_slider = nullptr;
    label = nullptr;
    label2 = nullptr;
    delay_time_slider = nullptr;
    label3 = nullptr;
    feedback_gain_slider = nullptr;
    label4 = nullptr;
    wow_rate_slider = nullptr;
    wow_amt_slider = nullptr;
    flutter_amt_slider = nullptr;
    flutter_rate_slider = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    label8 = nullptr;
    scrape_amt_slider = nullptr;
    label9 = nullptr;
    bias_slider = nullptr;
    label10 = nullptr;
    label11 = nullptr;
    label12 = nullptr;
    label13 = nullptr;
    label14 = nullptr;
    IPS_slider = nullptr;
    noise_level_slider = nullptr;
    label15 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void IvxDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff121212));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void IvxDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    input_gain_slider->setBounds (281, 14, 130, 105);
    output_gain_slider->setBounds (386, 14, 130, 105);
    label->setBounds (257, 102, 150, 24);
    label2->setBounds (469, 102, 100, 24);
    delay_time_slider->setBounds (5, 20, 100, 85);
    label3->setBounds (23, 102, 70, 24);
    feedback_gain_slider->setBounds (177, 20, 100, 85);
    label4->setBounds (196, 103, 150, 24);
    wow_rate_slider->setBounds (562, 11, 45, 50);
    wow_amt_slider->setBounds (562, 66, 45, 45);
    flutter_amt_slider->setBounds (627, 66, 45, 45);
    flutter_rate_slider->setBounds (627, 11, 45, 50);
    label5->setBounds (564, 103, 70, 24);
    label6->setBounds (625, 103, 70, 24);
    label7->setBounds (517, 20, 45, 24);
    label8->setBounds (521, 79, 39, 24);
    scrape_amt_slider->setBounds (692, 66, 45, 45);
    label9->setBounds (689, 103, 70, 24);
    bias_slider->setBounds (376, 90, 45, 50);
    label10->setBounds (357, 123, 56, 25);
    label11->setBounds (125, 101, 56, 25);
    label12->setBounds (92, 88, 38, 25);
    label13->setBounds (157, 88, 42, 25);
    label14->setBounds (130, -1, 42, 25);
    IPS_slider->setBounds (103, 17, 75, 80);
    noise_level_slider->setBounds (694, 8, 41, 46);
    label15->setBounds (694, 47, 48, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void IvxDelayAudioProcessorEditor::timerCallback()  //user interface timer implementation
{
     //if you want any display updates with a refresh timer add them here
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="IvxDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="IvxDelayAudioProcessor&amp; ownerProc" variableInitialisers="AudioProcessorEditor(ownerProc), processor(ownerProc)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.000"
                 fixedSize="0" initialWidth="750" initialHeight="145">
  <BACKGROUND backgroundColour="ff121212"/>
  <SLIDER name="Input Gain" id="a8530061fa26205a" memberName="input_gain_slider"
          virtualName="" explicitFocusOrder="0" pos="281 14 130 105" trackcol="ff450800"
          rotarysliderfill="ffcd1500" rotaryslideroutline="ff9e1100" textboxtext="ffa81300"
          textboxbkgd="880f00" textboxoutline="808080" min="0" max="8"
          int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="50" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <SLIDER name="Output Gain" id="1cac91e81f7ffc98" memberName="output_gain_slider"
          virtualName="" explicitFocusOrder="0" pos="386 14 130 105" trackcol="ff0a3100"
          rotarysliderfill="ff188100" rotaryslideroutline="ff126100" textboxtext="ff167500"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="8" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="50" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <LABEL name="new label" id="6e6fc86f7c7b1ed5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="257 102 150 24" textCol="ffb50000"
         edTextCol="ff000000" edBkgCol="0" labelText="Input Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9900569d876f741e" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="469 102 100 24" textCol="ff167700"
         edTextCol="ff000000" edBkgCol="0" labelText="Output Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Delay Time" id="17625408a19875d7" memberName="delay_time_slider"
          virtualName="" explicitFocusOrder="0" pos="5 20 100 85" trackcol="ff082a00"
          rotarysliderfill="ffff8600" rotaryslideroutline="ffb55f00" textboxtext="ffda6a00"
          textboxbkgd="f5100" textboxoutline="808080" min="20" max="1999"
          int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="50" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <LABEL name="new label" id="2bea1b081658bdc0" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="23 102 70 24" textCol="ffdd7400"
         edTextCol="ff000000" edBkgCol="0" labelText="Time [ms]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Feedback Gain" id="c4f37ca2e1c5fa2b" memberName="feedback_gain_slider"
          virtualName="" explicitFocusOrder="0" pos="177 20 100 85" trackcol="ff082a00"
          rotarysliderfill="ffff8600" rotaryslideroutline="ffb55f00" textboxtext="ffda6a00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="1" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="50" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <LABEL name="new label" id="5042618bee92f0e1" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="196 103 150 24" textCol="ffdd7400"
         edTextCol="ff000000" edBkgCol="0" labelText="Feedback" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Wow Rate" id="41826fcacc032854" memberName="wow_rate_slider"
          virtualName="" explicitFocusOrder="0" pos="562 11 45 50" trackcol="ff082a00"
          rotarysliderfill="ffdcbf00" rotaryslideroutline="ffa38d00" textboxtext="ffa38d00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="4" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <SLIDER name="Wow Amt" id="d43d7e188f04c376" memberName="wow_amt_slider"
          virtualName="" explicitFocusOrder="0" pos="562 66 45 45" trackcol="ff082a00"
          rotarysliderfill="ffdcbf00" rotaryslideroutline="ffa38d00" textboxtext="ffda6a00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="1" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="40" textBoxHeight="10" skewFactor="0" needsCallback="0"/>
  <SLIDER name="Flutter Rate" id="d855e910754693d2" memberName="flutter_amt_slider"
          virtualName="" explicitFocusOrder="0" pos="627 66 45 45" trackcol="ff082a00"
          rotarysliderfill="ff6bd700" rotaryslideroutline="ff4d9a00" textboxtext="ffda6a00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="1" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="40" textBoxHeight="10" skewFactor="0" needsCallback="0"/>
  <SLIDER name="Flutter Rate" id="bf612f9a3b3abf56" memberName="flutter_rate_slider"
          virtualName="" explicitFocusOrder="0" pos="627 11 45 50" trackcol="ff082a00"
          rotarysliderfill="ff6bd700" rotaryslideroutline="ff4d9a00" textboxtext="ff4d9a00"
          textboxbkgd="f5100" textboxoutline="808080" min="10" max="50"
          int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="10" skewFactor="0"
          needsCallback="0"/>
  <LABEL name="new label" id="8c32d6b2ec5d469a" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="564 103 70 24" textCol="ffa38d00"
         edTextCol="ff000000" edBkgCol="0" labelText="Wow" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c5db74d784cbe663" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="625 103 70 24" textCol="ff4d9a00"
         edTextCol="ff000000" edBkgCol="0" labelText="Flutter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f88760fdf450630e" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="517 20 45 24" textCol="ff9c9c9c"
         edTextCol="ff000000" edBkgCol="0" labelText="Rate:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d3c907adbfb3efb0" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="521 79 39 24" textCol="ff9c9c9c"
         edTextCol="ff000000" edBkgCol="0" labelText="Amt:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Scrape Amt" id="6cb0685905828f74" memberName="scrape_amt_slider"
          virtualName="" explicitFocusOrder="0" pos="692 66 45 45" trackcol="ff082a00"
          rotarysliderfill="ffff6f00" rotaryslideroutline="ffff6f00" textboxtext="ffff6f00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="1" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="40" textBoxHeight="10" skewFactor="0" needsCallback="0"/>
  <LABEL name="new label" id="dd764cc9f7a71e53" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="689 103 70 24" textCol="ffff6f00"
         edTextCol="ff000000" edBkgCol="0" labelText="Scrape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Bias" id="3c40cd001ab8a332" memberName="bias_slider" virtualName=""
          explicitFocusOrder="0" pos="376 90 45 50" trackcol="ff082a00"
          rotarysliderfill="ffffc900" rotaryslideroutline="ffc49b00" textboxtext="ffd3a700"
          textboxbkgd="f5100" textboxoutline="808080" min="2" max="5" int="1"
          style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="10" skewFactor="1"
          needsCallback="0"/>
  <LABEL name="new label" id="b91a2c02b635c3b1" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="357 123 56 25" textCol="ffcda100"
         edTextCol="ff000000" edBkgCol="0" labelText="Bias" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="24bc073356c53ffe" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="125 101 56 25" textCol="ffdd7400"
         edTextCol="ff000000" edBkgCol="0" labelText="IPS" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="787b4540dbb2daa" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="92 88 38 25" textCol="ffdd7400" edTextCol="ff000000"
         edBkgCol="0" labelText="3.75" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14"
         kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1d167f6965e567cb" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="157 88 42 25" textCol="ffdd7400"
         edTextCol="ff000000" edBkgCol="0" labelText="15" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6e090b68f6d988df" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="130 -1 42 25" textCol="ffdd7400"
         edTextCol="ff000000" edBkgCol="0" labelText="7.5" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14" kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="IPS" id="2bef45ac47ec5769" memberName="IPS_slider" virtualName=""
          explicitFocusOrder="0" pos="103 17 75 80" trackcol="ff082a00"
          rotarysliderfill="ffff8600" rotaryslideroutline="ffb55f00" textboxtext="ffda6a00"
          textboxbkgd="f5100" textboxoutline="808080" min="1" max="3" int="1"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="50" textBoxHeight="10" skewFactor="0" needsCallback="0"/>
  <SLIDER name="Noise Level" id="41764f6f8519b875" memberName="noise_level_slider"
          virtualName="" explicitFocusOrder="0" pos="694 8 41 46" trackcol="ffba00b0"
          rotarysliderfill="ffee00ff" rotaryslideroutline="ffba00b0" textboxtext="ff4d9a00"
          textboxbkgd="f5100" textboxoutline="808080" min="0" max="4" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="40" textBoxHeight="10" skewFactor="0" needsCallback="0"/>
  <LABEL name="new label" id="159869caecdd7ce" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="694 47 48 20" textCol="ffba00b0"
         edTextCol="ff000000" edBkgCol="0" labelText="Noise" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
