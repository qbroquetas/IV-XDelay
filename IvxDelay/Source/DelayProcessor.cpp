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

#include "DelayProcessor.h"
#include <cmath>


#define TWOPI 6.28318530718

DelayProcessor::DelayProcessor()
{
  setDelayTime(250);
  setFeedbackGain(0.2);
  setWowRate(1);
  setWowAmt(0.025);
  setFlutterRate(15);
  setFlutterAmt(0.025);
  setScrapeAmt(0.05);
  setBias(3);
  setIPS(2);
  setNoiseLevel(0.7);
  
  p_noise15 = NoiseTable::noise15;
  p_noise75 = NoiseTable::noise75;
  p_noise375 = NoiseTable::noise375;
  noise_index = 0;
}

    void DelayProcessor::initialise (float param_maximum_delay_time, double DSP_sample_rate)
{
  sample_rate = DSP_sample_rate;
  osc_increment = OSCTABLESIZE / sample_rate;
  maximum_delay_time = param_maximum_delay_time;

  // delay buffer is initialised
  delay_buffer_size = maximum_delay_time  * sample_rate / 1000;
  delay_buffer = new float[delay_buffer_size]; // delay buffer is dynamically allocated before playback starts
  for (int i = 0; i < delay_buffer_size; i++)
    {
      delay_buffer[i] = 0; // delay buffer is initialised to 0
    }
  p_write = delay_buffer; //set pointer to delay buffer

  //set initial writing and reading positions
  writing_position = 0;
  reading_position = 0;

  // intantaneous delay time is initalised to 0 before playback
  // to recreate the progressive speed incrementation of the tape transport.
  // reading offset will increment until delay time target is reached.
  delay_time_current = 0;

  // fir buffer is initialised
  for (int i = 0; i < FIRBUFFERSIZE; i++)
    {
      fir_buffer[i] = 0;
    }
  fir_writing_position = 0;

  //p_shaper_table = nullptr;

  // osc_table and scrape_table are intialised. scrape_table is filled with sinewaves ranging from 500 to 5000Hz
  for (int i = 0; i < OSCTABLESIZE; i++)
    {
      osc_table[i] = sin(TWOPI * i / OSCTABLESIZE);
	  scrape_table[i] = 0.025 * sin(TWOPI * 2.0 * i / OSCTABLESIZE + 0.67 * TWOPI)
		  + 0.0289 * sin(TWOPI * 3.0 * i / OSCTABLESIZE + 0.42 * TWOPI)
		  + 0.0313 * sin(TWOPI * 4.0 * i / OSCTABLESIZE + 0.86 * TWOPI)
		  + 0.0156 * sin(TWOPI * 5.0 * i / OSCTABLESIZE + 0.38 * TWOPI)
		  + 0.0165 * sin(TWOPI * 6.0 * i / OSCTABLESIZE + 0.71 * TWOPI)
		  + 0.0264 * sin(TWOPI * 7.0 * i / OSCTABLESIZE + 0.29 * TWOPI)
		  + 0.0198 * sin(TWOPI * 8.0 * i / OSCTABLESIZE + 0.92 * TWOPI)
		  + 0.0249 * sin(TWOPI * 9.0 * i / OSCTABLESIZE + 0.54 * TWOPI)
		  + 0.0195 * sin(TWOPI * 10.0 * i / OSCTABLESIZE + 0.13 * TWOPI)
		  + 0.0158 * sin(TWOPI * 11.0 * i / OSCTABLESIZE + 0.66 * TWOPI)
		  + 0.0213 * sin(TWOPI * 12.0 * i / OSCTABLESIZE + 0.45 * TWOPI)
		  + 0.0259 * sin(TWOPI * 13.0 * i / OSCTABLESIZE + 0.88 * TWOPI)
		  + 0.0176 * sin(TWOPI * 14.0 * i / OSCTABLESIZE + 0.31 * TWOPI)
		  + 0.0165 * sin(TWOPI * 15.0 * i / OSCTABLESIZE + 0.65 * TWOPI)
		  + 0.0129 * sin(TWOPI * 16.0 * i / OSCTABLESIZE + 0.32 * TWOPI)
		  + 0.0224 * sin(TWOPI * 17.0 * i / OSCTABLESIZE + 0.76 * TWOPI)
		  + 0.0164 * sin(TWOPI * 18.0 * i / OSCTABLESIZE + 0.25 * TWOPI)
		  + 0.0218 * sin(TWOPI * 19.0 * i / OSCTABLESIZE + 0.12 * TWOPI)
		  + 0.0089 * sin(TWOPI * 20.0 * i / OSCTABLESIZE + 0.84 * TWOPI)
		  + 0.0123 * sin(TWOPI * 21.0 * i / OSCTABLESIZE + 0.48 * TWOPI)
		  + 0.0074 * sin(TWOPI * 22.0 * i / OSCTABLESIZE + 0.64 * TWOPI)
		  + 0.0189 * sin(TWOPI * 23.0 * i / OSCTABLESIZE + 0.86 * TWOPI)
		  + 0.0220 * sin(TWOPI * 24.0 * i / OSCTABLESIZE + 0.34 * TWOPI)
		  + 0.0103 * sin(TWOPI * 25.0 * i / OSCTABLESIZE + 0.75 * TWOPI)
		  + 0.0152 * sin(TWOPI * 26.0 * i / OSCTABLESIZE + 0.62 * TWOPI)
		  + 0.0086 * sin(TWOPI * 27.0 * i / OSCTABLESIZE + 0.54 * TWOPI)
		  + 0.0120 * sin(TWOPI * 28.0 * i / OSCTABLESIZE + 0.92 * TWOPI)
		  + 0.0089 * sin(TWOPI * 29.0 * i / OSCTABLESIZE + 0.53 * TWOPI)
		  + 0.0104 * sin(TWOPI * 30.0 * i / OSCTABLESIZE + 0.81 * TWOPI)
		  + 0.0120 * sin(TWOPI * 31.0 * i / OSCTABLESIZE + 0.10 * TWOPI)
		  + 0.0056 * sin(TWOPI * 32.0 * i / OSCTABLESIZE + 0.08 * TWOPI)
		  + 0.0216 * sin (TWOPI * 1.0 * i / OSCTABLESIZE)
		  ;
    }




  // instantaneous phase values are initialised
  wow_phi = 0;
  flutter_phi = 0;
  scrape_phi = 0;
}

void DelayProcessor::setDelayTime(float param_delay_time)
{
  delay_time_target = param_delay_time * 0.001;
}

// main DSP function. processing is in place on the DSP_buffer pointer
// passed as first argument. buffer_size is the size of the DSP_buffer.
// DelayProcessor::initialise must be called before this function
void  DelayProcessor::process (double* DSP_buffer, int buffer_size)
{
  // this switch updates local variables and data structures
  // if the IPS or Bias paramters are changed by the user
  if (param_changed)
    {
      switch (IPS)
	{
	case 3:
	  shaper_input_level = FASTIPSLEVEL;
	  noise_level_IPS = FASTIPSNOISELEVEL;
	  p_noise_current_table = p_noise15;
	  p_noise_playback = p_noise15;
	  switch (bias)
	    {
	    case 2:
	      p_fir_coefficients = FirTable::fir2;
	      p_shaper_table = ShaperTable::shaper15_2;
	      break;
	    case 3:
	      p_fir_coefficients = FirTable::fir4;
	      p_shaper_table = ShaperTable::shaper15_3;
	      break;
	    case 4:
	      p_fir_coefficients = FirTable::fir6;
	      p_shaper_table = ShaperTable::shaper15_4;
	      break;
	    case 5:
	      p_fir_coefficients = FirTable::fir8;
	      p_shaper_table = ShaperTable::shaper15_5;
	      break;
	    }
	  break;

	case 2:
	  shaper_input_level = MEDIPSLEVEL;
	  noise_level_IPS = MEDIPSNOISELEVEL;
	  p_noise_current_table = p_noise75;
	  p_noise_playback = p_noise75;
	  switch (bias)
	    {
	    case 2:
	      p_fir_coefficients = FirTable::fir18;
	      p_shaper_table = ShaperTable::shaper75_2;
	      break;
	    case 3:
	      p_fir_coefficients = FirTable::fir20;
	      p_shaper_table = ShaperTable::shaper75_3;
	      break;
	    case 4:
	      p_fir_coefficients = FirTable::fir22;
	      p_shaper_table = ShaperTable::shaper75_4;
	      break;
	    case 5:
	      p_fir_coefficients = FirTable::fir24;
	      p_shaper_table = ShaperTable::shaper75_5;
	      break;
	    }
	  break;

	case 1:
	  shaper_input_level = SLOWIPSLEVEL;
	  noise_level_IPS = SLOWIPSNOISELEVEL;
	  p_noise_current_table = p_noise375;
	  p_noise_playback = p_noise375;
	  switch (bias)
	    {
	    case 2:
	      p_fir_coefficients = FirTable::fir34;
	      p_shaper_table = ShaperTable::shaper375_2;
	      break;
	    case 3:
	      p_fir_coefficients = FirTable::fir36;
	      p_shaper_table = ShaperTable::shaper375_3;
	      break;
	    case 4:
	      p_fir_coefficients = FirTable::fir38;
	      p_shaper_table = ShaperTable::shaper375_4;
	      break;
	    case 5:
	      p_fir_coefficients = FirTable::fir40;
	      p_shaper_table = ShaperTable::shaper375_5;
	      break;
	    }
	  break;
	}
      param_changed = false;
    }

  // main DSP loop. performs all DSP processing sample by sample,
  // computes the immediate reading and writing positions and performs
  // the DSP_buffer and delay_buffer reading and writing operations
  for (int i = 0; i < buffer_size; i++)
    {
      // inertia of tape transport, creates pitching effect when changing delay time
      // delay_time_current is set to reach delay_time_target over a period of time
      // delay_time_current speed towards delay_time_target is reduced as the
      // differential between them decreases
      delay_time_current = delay_time_current + 0.00001 * (delay_time_target - delay_time_current);

      // sample offset calculated from immediate delay time in milliseconds
      sample_offset = delay_time_current * sample_rate;

      // noise samples and the feedback tap are added to the input signal
      noise_sample = noise();
      DSP_buffer[i] = DSP_buffer[i] + (noise_level * noise_level_IPS * noise_sample) + (feedback_gain * feedback_sample);


      // FIR filter is called on the DSP buffer and its ouput is written
      // into the delay buffer, according to the writing position
      p_write[writing_position] = firFilter(waveShaper(DSP_buffer[i]));

      // interpolateValue is called to read from the delay buffer.
      // its output is copied into the DSP buffer and the feedback tap
      DSP_buffer[i] = interpolateValue ();
      feedback_sample = DSP_buffer[i];

      // writing position is incremented
      // and wrapped around the delay buffer
       writing_position++;
       if (writing_position >= delay_buffer_size)
	 {
	   writing_position = 0;
	 }

      // reading position is calculated based on the writing position
      // and the sample offset. speed modulations are multiplied by their
      // maximum intensity in samples and added to the reading position
      reading_position = writing_position - sample_offset + 1500 * wow_amt * wowOsc() + 50 * flutter_amt * flutterOsc() + 35 * scrape_amt * scrapeOsc();
      if (reading_position < 0)
	{
	  reading_position += delay_buffer_size;
	}
    }
}

// interpolating function. takes closest values to the reading position
// and performs linear interpolation between them according to the instantanous reading position
float DelayProcessor::interpolateValue()
{
  int truncated_reading_position = (int)reading_position;
  float sample0 = delay_buffer[truncated_reading_position];
  float weight_sample1 = reading_position - truncated_reading_position;
  
  truncated_reading_position++;
  if (truncated_reading_position >= delay_buffer_size)
    {
      truncated_reading_position = 0;
    }
  
  float sample1 = delay_buffer[truncated_reading_position];
  return sample0 + weight_sample1 * (sample1 - sample0);
}

// sine wave table lookup oscillator with linear interpolation
// used to alter the reading position and cause frequency modulation
float DelayProcessor::wowOsc ()
{
  // instantaneous phase incrementation according to wow rate
  wow_phi += wow_rate * osc_increment;
  if (wow_phi >= OSCTABLESIZE)
    {
      wow_phi -= OSCTABLESIZE;
    }
  wow_truncated_phi = (int)wow_phi;
  float sample0 = osc_table[wow_truncated_phi];
  float weight_sample1 = wow_phi - wow_truncated_phi;

  // if sample0 is the last sample in the table,
  // wrap index so that sample1 reads from first sample
  wow_truncated_phi++;
  wow_truncated_phi &= OSCTABLEMAX;
  float sample1 = osc_table[wow_truncated_phi];

  return sample0 + weight_sample1 * (sample1 - sample0);
}

// sine wave table lookup oscillator with linear interpolation
// used to alter the reading position and cause frequency modulation
float DelayProcessor::flutterOsc ()
{
  flutter_phi += flutter_rate * osc_increment;
  if (flutter_phi >= OSCTABLESIZE)
    {
      flutter_phi -= OSCTABLESIZE;
    }
  flutter_truncated_phi = (int)flutter_phi;
  float sample0 = osc_table[flutter_truncated_phi];
  float weight_sample1 = flutter_phi - flutter_truncated_phi;
  flutter_truncated_phi++;
  flutter_truncated_phi &= OSCTABLEMAX;
  float sample1 = osc_table[flutter_truncated_phi];

  return sample0 + weight_sample1 * (sample1 - sample0);
}

// wideband table lookup oscillator with linear interpolation
// used to alter the reading position and cause frequency modulation
float DelayProcessor::scrapeOsc ()
{
  scrape_phi += 100 * osc_increment;
  if (scrape_phi >= OSCTABLESIZE)
    {
      scrape_phi -= OSCTABLESIZE;
    }
  scrape_truncated_phi = (int)scrape_phi;
  float sample0 = scrape_table[scrape_truncated_phi];
  float weight_sample1 = scrape_phi - scrape_truncated_phi;
  scrape_truncated_phi++;
  scrape_truncated_phi &= OSCTABLEMAX;
  float sample1 = scrape_table[scrape_truncated_phi];

  return sample0 + weight_sample1 * (sample1 - sample0) + 0.6 * noise_sample;
}


// FIR filter implementation using a circular buffer.
// input samples are passed using fir_input
float DelayProcessor::firFilter(float fir_input)
{
  // input sample is written into a circular buffer
  // and reading position is set to the last written sample
  fir_buffer[fir_writing_position] = fir_input;
  fir_output = 0;
  fir_reading_position = fir_writing_position;

  // output is calculated using multiply-add operations,
  // reading fir_buffer backwards and multiplying each sample
  // by its respective coefficient
  for (int i = 0; i <= FIRSIZE; i++)
    {
      fir_output += fir_buffer[fir_reading_position] * p_fir_coefficients[i];
      fir_reading_position--;
      fir_reading_position &= FIRSIZE;
    }
  // writing position is incremented and output is returned
  fir_writing_position++;
  fir_writing_position &= FIRSIZE;
  return fir_output;
}

// wave shaper function. takes pointer to a sample and
// overwrites it with the output of a transfer curve
// stored in shaper_table
float DelayProcessor::waveShaper (float shaper_input)
{
  shaper_input = shaper_input_level * shaper_input;

  // clipping if audio input exceeds normalised range (-1, 1)
  if (shaper_input >= 1)
    {
      return 1;
    }
  else if (shaper_input <= -1)
    {
      return -1;
    }
  // floating point input of the wave shaper function is stored in shaper_x,
  // truncated index is stored in shaper_index
  // and linearly interpolated output value is written in place
  else
    {
      shaper_x = (0.5 * SHAPERSIZE) + (0.5 * SHAPERSIZE * shaper_input);
      shaper_index = (int) shaper_x;
      float sample0 = p_shaper_table[shaper_index];
      float sample1 = p_shaper_table[shaper_index + 1];
      return sample0 + (shaper_x - shaper_index) * (sample1 - sample0);
    }
}

// noise playback function. 
float DelayProcessor::noise()
{
  noise_index++;
  noise_index &= NOISELENGTH;
  return p_noise_playback[noise_index];
}

