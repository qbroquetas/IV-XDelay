//    Copyright (C) 2017 Joaquim Broquetas Ruiz

//    This file is part of IV-X Delay.
//    IV-X Delay is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    IV-X Delay is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with IV-X Delay.  If not, see <http://www.gnu.org/licenses/>.



#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "../libraries/r8brain-free-src/CDSPResampler.h"
#include "level_processor.h"
#include "DelayProcessor.h"

//==============================================================================
/**
*/
class IvxDelayAudioProcessor  : public AudioProcessor,
    public AudioProcessorValueTreeState::Listener  // this class inheritance allows the processor to receive parameter changes from the GUI
{
public:
    //==============================================================================
    IvxDelayAudioProcessor();
    ~IvxDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;

    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;


    // Parameters and access to the GUI

#define CHANNELS  1                         // sets number of channels according to the supported channel configuration
#define MAXTIME 2000                        // sets maximum delay time in milliseconds
#define PARAM_SETNAME "IvxDelayParams"      // set of all the parameters in the tree
#define PARAM_INGAIN "Input Gain"           // input gain parameter
#define PARAM_OUTGAIN "Output Gain"         // output gain parameter
#define PARAM_DELAYTIME "Delay Time"        // delay time parameter
#define PARAM_FEEDBACKGAIN "Feedback Gain"  // feedback gain parameter
#define PARAM_WOWAMT "Wow Amt"
#define PARAM_WOWRATE "Wow Rate"
#define PARAM_FLUTTERAMT "Flutter Amt"
#define PARAM_FLUTTERRATE "Flutter Rate"
#define PARAM_SCRAPEAMT "Scrape Amt"
#define PARAM_BIAS "Bias"
#define PARAM_IPS "IPS"
#define PARAM_NOISELEVEL "Noise Level"


    AudioProcessorValueTreeState& getState() { return *mState; };  // this function returns the current parameter state

    void parameterChanged(const String& parameterID, float newValue) // triggers a parameter update synchronised with the processing blocks
    { MajorParamChange = true; };


private:
    //==============================================================================


    bool MajorParamChange;
    ScopedPointer<AudioProcessorValueTreeState> mState;  //this is the object were all the user parameter values are stored
    ScopedPointer<UndoManager> mUndoManager;
    
    
    double DSP_sample_rate;           // sample rate at which the DSP algorithms work
    int host_buffer_size;             // original buffer size
    int maximum_buffer_size;          // actual size of the DSP buffer and the buffer of doubles that feed the upsampler, provides safety margin
    int DSP_buffer_size;              // portion of the DSP buffer that contains audio samples, returned by the upsampler
    int downsampler_buffer_size;      // size of the buffer after downsampling
    double* buffer_of_doubles[CHANNELS];
    double* DSP_buffer[CHANNELS] ;

    OwnedArray<r8b::CDSPResampler< r8b::CDSPFracInterpolator< 6, 11 > >> upsampler;   // upsamplers
    OwnedArray<r8b::CDSPResampler< r8b::CDSPFracInterpolator< 6, 11 > >> downsampler; // downsamplers
    level_processor input_gain;             // input gain DSP object
    level_processor output_gain;            // output gain DSP object
    DelayProcessor Delay[CHANNELS];         // delay object
    



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IvxDelayAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED

