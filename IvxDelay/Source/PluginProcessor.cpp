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

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String GetStrValue(float v) { return String(v);};

//==============================================================================
IvxDelayAudioProcessor::IvxDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth

		       // request only mono input and output channel configurations
                       .withInput  ("Input",  AudioChannelSet::mono())//, true)
                      #endif
		       .withOutput ("Output", AudioChannelSet::mono())//, true)
                     #endif
                       )
#endif
{

//create  state manager and give current parameter set a name
mUndoManager = new UndoManager();
mState = new AudioProcessorValueTreeState(*this, mUndoManager);

//add each parameter. Skew Factor set in NormalisableRange, 4th parameter
 mState->createAndAddParameter(PARAM_INGAIN, "Input Gain", "", NormalisableRange<float>(0.125f, 8.0f, 0.001f, 0.45), input_gain.GetGain(), GetStrValue, nullptr);

 mState->createAndAddParameter(PARAM_OUTGAIN, "Output Gain", "", NormalisableRange<float>(0.125f, 8.0f, 0.001f, 0.45), output_gain.GetGain(), GetStrValue, nullptr);

 for (int i = 0; i < CHANNELS; i++)
   {
     mState->createAndAddParameter(PARAM_DELAYTIME, "Delay Time", "", NormalisableRange<float>(20, 1999, 1, 0.4),
				   Delay[i].getDelayTime(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_FEEDBACKGAIN, "Feedback Gain", "", NormalisableRange<float>(0, 1.5, 0.01, 0.65),
				   Delay[i].getFeedbackGain(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_WOWAMT, "Wow Amt", "", NormalisableRange<float>(0, 1, 0.01, 0.65),
				   Delay[i].getWowAmt(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_WOWRATE, "Wow Rate", "", NormalisableRange<float>(0.1, 4, 0.01, 0.5),
				   Delay[i].getWowRate(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_FLUTTERAMT, "Flutter Amt", "", NormalisableRange<float>(0, 1, 0.01, 0.65),
				   Delay[i].getFlutterAmt(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_FLUTTERRATE, "Flutter Rate", "", NormalisableRange<float>(10, 50, 1, 0.75),
				   Delay[i].getFlutterRate(), GetStrValue, nullptr);

     mState->createAndAddParameter(PARAM_SCRAPEAMT, "Scrape Amt", "", NormalisableRange<float>(0, 1, 0.01, 0.65),
				   Delay[i].getScrapeAmt(), GetStrValue, nullptr);
     
     mState->createAndAddParameter(PARAM_BIAS, "Bias", "", NormalisableRange<float>(2, 5, 1, 1),
				   Delay[i].getBias(), GetStrValue, nullptr);
     
     mState->createAndAddParameter(PARAM_IPS, "IPS", "", NormalisableRange<float>(1, 3, 1, 1),
				   Delay[i].getIPS(), GetStrValue, nullptr);
     
     mState->createAndAddParameter(PARAM_NOISELEVEL, "Noise Level", "", NormalisableRange<float>(0.01, 4, 0.01, 0.6),
				   Delay[i].getNoiseLevel(), GetStrValue, nullptr);

     
   }

//Once all parameters are added, it is safe to create the actual ValueTree
mState->state = ValueTree(PARAM_SETNAME);

 
//start it with deep updates
MajorParamChange = true;

}

IvxDelayAudioProcessor::~IvxDelayAudioProcessor()
{
  mState = nullptr;
  mUndoManager = nullptr;

}

//==============================================================================
const String IvxDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool IvxDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool IvxDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double IvxDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int IvxDelayAudioProcessor::getNumPrograms()
{
    return 1;
                
}

int IvxDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void IvxDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String IvxDelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void IvxDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void IvxDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  // this method is used for initialisation before playback starts

 int TransitionBandInPercent = 4;
 int StopBandAttenuation = 100;

  DSP_sample_rate = 192000; // upsampling sample rate, at which the processing will take place
  host_buffer_size = samplesPerBlock;
  maximum_buffer_size = 1.25 * samplesPerBlock; //the DSP buffer has to accomodate for the resampler's fluctuating block size

  //the buffers of doubles that are passed to the upsampler are initialised
  for (int i = 0; i < CHANNELS; i++)
    {
      buffer_of_doubles[i] = new double[maximum_buffer_size];  // the upsampler will overwrite this buffer and return it as the DSP buffer
      for (int j = 0; j < maximum_buffer_size; j++)
	{
	  buffer_of_doubles[i][j] = 0;
	}
    }

  // the juce arrays to hold the resamplers are cleared
  upsampler.clear();
  downsampler.clear();

  // the resamplers are instantiated
  for (int i = 0; i < CHANNELS; i++)
    {
      upsampler.add (new r8b::CDSPResampler< r8b::CDSPFracInterpolator< 6, 11 > >(sampleRate, DSP_sample_rate, maximum_buffer_size, TransitionBandInPercent, StopBandAttenuation, r8b::EDSPFilterPhaseResponse(0), false));
      downsampler.add (new r8b::CDSPResampler< r8b::CDSPFracInterpolator< 6, 11 > >(DSP_sample_rate, sampleRate, maximum_buffer_size, TransitionBandInPercent, StopBandAttenuation, r8b::EDSPFilterPhaseResponse(0), false));
    }

  // the delay objects are initialised
  for (int i = 0; i < CHANNELS; i++)
    {
      Delay[i].initialise (MAXTIME, DSP_sample_rate);
    }
}


void IvxDelayAudioProcessor::releaseResources()
{
    // When playback stops, resamplers are cleared of samples in their buffers
    for (int k = 0; k < upsampler.size(); ++k)
        {
	  downsampler[k]->clear();
	  upsampler[k]->clear();
        }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool IvxDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else

    // the support for channel configurations is checked. in this version, only mono is supported.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void IvxDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // GUI parameters are passed to the DSP objects
    input_gain.SetGain((*mState->getRawParameterValue(PARAM_INGAIN)));        
    output_gain.SetGain((*mState->getRawParameterValue(PARAM_OUTGAIN)));      

    for (int i = 0; i < CHANNELS; i++)
      {
	Delay[i].setBias((*mState->getRawParameterValue(PARAM_BIAS)));
	Delay[i].setIPS((*mState->getRawParameterValue(PARAM_IPS)));
	Delay[i].setDelayTime((*mState->getRawParameterValue(PARAM_DELAYTIME)));
	Delay[i].setFeedbackGain((*mState->getRawParameterValue(PARAM_FEEDBACKGAIN)));
	Delay[i].setWowAmt((*mState->getRawParameterValue(PARAM_WOWAMT)));
	Delay[i].setWowRate((*mState->getRawParameterValue(PARAM_WOWRATE)));
	Delay[i].setFlutterAmt((*mState->getRawParameterValue(PARAM_FLUTTERAMT)));
	Delay[i].setFlutterRate((*mState->getRawParameterValue(PARAM_FLUTTERRATE)));
	Delay[i].setScrapeAmt((*mState->getRawParameterValue(PARAM_SCRAPEAMT)));
	Delay[i].setNoiseLevel((*mState->getRawParameterValue(PARAM_NOISELEVEL)));
      }

    // this pointer to pointer holds the host buffer array.
    // processing is in place
    float** host_buffers = buffer.getArrayOfWritePointers();

    for (int i = 0; i < CHANNELS; ++i)
      {
	// input gain method is called on the audio stream
	input_gain.process(host_buffers[i], host_buffer_size);

	// as the r8b resampling library only works with doubles,
	// the audio samples are copied into a buffer of doubles
	const float *float_sample = buffer.getReadPointer(i);
	for (int j = 0; j < buffer.getNumSamples(); ++j)
	  {
	    buffer_of_doubles[i][j] = *float_sample;
	    ++float_sample;
	  }

	 // the upsamplers are called on each channel of the host buffers. DSP_buffer_size holds the new buffer size
	 DSP_buffer_size = upsampler[i]->process (buffer_of_doubles[i], buffer.getNumSamples(), DSP_buffer[i]);

	 // Delay Processor
	 Delay[i].process (DSP_buffer[i], DSP_buffer_size);

	// the downsamplers are called on each channel of the DSP buffers
	double* downsampler_output_sample;
	const int downsampler_buffer_size = downsampler[i]->process (DSP_buffer[i], DSP_buffer_size, downsampler_output_sample);

	// the downsampled signal is copied into the host buffers.
	// this step is necessary because the r8b library does not accept a buffer of floats
	for (int j = 0; j < jmin (buffer.getNumSamples(), downsampler_buffer_size); ++j)
	  {
	    host_buffers[i][j] = *downsampler_output_sample;
	    ++downsampler_output_sample;
	  }

	// output gain method is called on the audio stream
	output_gain.process(host_buffers[i], host_buffer_size);
      }
}

//==============================================================================
bool IvxDelayAudioProcessor::hasEditor() const
{
    return true; 
}

AudioProcessorEditor* IvxDelayAudioProcessor::createEditor()
{
    return new IvxDelayAudioProcessorEditor (*this);
}

//==============================================================================
void IvxDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
   
  //Save UserParams/Data to file
  MemoryOutputStream stream(destData, false);
  mState->state.writeToStream(stream);
}

void IvxDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

  ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
  if (tree.isValid())
    {
      if (tree.hasType(PARAM_SETNAME))
	{
	  mState->state = tree;
	}
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new IvxDelayAudioProcessor();
}

