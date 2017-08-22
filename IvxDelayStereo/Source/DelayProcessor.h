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


#include "FirTable.h"
#include "ShaperTable.h"
#include "NoiseTable.h"

#define OSCTABLESIZE 4096
#define OSCTABLEMAX OSCTABLESIZE - 1
#define FIRSIZE ((1 << 7) - 1)
#define FIRBUFFERSIZE 128
#define SHAPERSIZE 32768
#define FASTIPSLEVEL 0.4
#define MEDIPSLEVEL 0.55
#define SLOWIPSLEVEL 0.8
#define NOISELENGTH ((1 << 22) - 1)
#define FASTIPSNOISELEVEL 0.006
#define MEDIPSNOISELEVEL 0.005
#define SLOWIPSNOISELEVEL 0.012
#define FEEDBACKTRIM 0.7


class DelayProcessor : public FirTable, public ShaperTable, public NoiseTable
 {
 public:
   DelayProcessor();
   //~DelayProcessor();

   // parameter setting and getting functions
   void setDelayTime (float param_delay_time);
   float getDelayTime (void) { return delay_time_target * 1000; };
   void setFeedbackGain (float param_feedback_gain) { feedback_gain = param_feedback_gain * FEEDBACKTRIM; };
   float getFeedbackGain (void) { return feedback_gain; };
   void setWowRate (float param_wow_rate) { wow_rate = param_wow_rate; };
   float getWowRate (void) { return wow_rate; };
   void setWowAmt (float param_wow_amt) { wow_amt = param_wow_amt; };
   float getWowAmt (void) { return wow_amt; };
   void setFlutterRate (float param_flutter_rate) { flutter_rate = param_flutter_rate; };
   float getFlutterRate (void) { return flutter_rate; };
   void setFlutterAmt (float param_flutter_amt) { flutter_amt = param_flutter_amt; };
   float getFlutterAmt (void) { return flutter_amt; };
   void setScrapeAmt (float param_scrape_amt) { scrape_amt = param_scrape_amt; };
   float getScrapeAmt (void) { return scrape_amt; };
   void setBias (float param_bias)
   {
     if (bias != param_bias)
       {
	 bias = (int)param_bias;
	 param_changed = true;
       }
   };
   float getBias (void) { return (float)bias; };
   void setIPS (float param_IPS)
   {
     if (IPS != param_IPS)
       {
	 IPS = (int)param_IPS;
	 param_changed = true;
       }
   };
   float getIPS (void) { return (float)IPS; };
   void setNoiseLevel(float param_noise_level)
   {
     noise_level = param_noise_level;
   }
   float getNoiseLevel(void) { return noise_level; };
   
   // initialisation method
   void initialise (float maximum_delay_time, double DSP_sample_rate);


   // DSP algorithm
   void process (double* DSP_buffer, int buffer_size);



 private:

   float wowOsc ();
   float flutterOsc();
   float scrapeOsc();

   float osc_table[OSCTABLESIZE];
   float scrape_table[OSCTABLESIZE];
   float wow_phi;
   float flutter_phi;
   float scrape_phi;
   int wow_truncated_phi;
   int flutter_truncated_phi;
   int scrape_truncated_phi;
   float wow_rate;
   float flutter_rate;
   float wow_amt;
   float flutter_amt;
   float scrape_amt;

   double sample_rate;
   float delay_time_target;    // this variable follows the delay time setting in the GUI
   float delay_time_current;   // instantaneous delay time
   float delay_time_initial;   // initial value of delay time when setDelayTime is called
   float* delay_buffer;
   int delay_buffer_size;

   float* p_write;            // writing pointer into the delay buffer
   float sample_offset;       // instantaneous delay time converted to fractional samples
   float reading_position;    // instantaneous fractional reading position
   int writing_position;       // instantaneous writing position. not fractional.
   float feedback_sample;     // feedback loop
   float feedback_gain;

   float interpolateValue();
   float firFilter(float fir_input);
   float fir_buffer[FIRBUFFERSIZE];
   int fir_writing_position;
   int fir_reading_position;
   //float fir_coefficients[FIRSIZE];
   float* p_fir_coefficients;
   float fir_output;
   int bias;
   int IPS;
   bool param_changed;
   float maximum_delay_time;

   float waveShaper (float shaper_input);
   float* p_shaper_table;
   int shaper_index;
   float shaper_x;

   float noise();
   float noise_level;
   float noise_level_IPS;
   float* p_noise15;
   float* p_noise75;
   float* p_noise375;
   float* p_noise_current_table;
   float* p_noise_playback;
   float noise_output_sample;
   int noise_index;
   float noise_sample;

   float osc_increment;
   float shaper_input_level;
 };
