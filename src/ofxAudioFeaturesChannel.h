/*
 * Copyright Paul Reimer, 2012
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial 3.0 Unported License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/
 * or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#pragma once

#include "aubio.h"

#include <vector>
#include <deque>
#include <map>
#include <string>

class ofxAudioFeaturesChannel
{
public:
  ofxAudioFeaturesChannel();
  ~ofxAudioFeaturesChannel();

  void setup(size_t _bufferSize, size_t _hopSize, float _sampleRate);
  void destroy();
  void process(const float now);

  std::vector<float> inputBuffer;
  std::vector<float> spectrum;
  std::vector<float> phase;
  std::vector<float> smoothedSpectrum;
  std::vector<float> smoothedPhase;

  float attack;
  float decay;
  float gain;

  bool calibrateMic;
  bool calibratedMic;

  std::deque<std::pair<float, float> > onsets;
  float pitch;

  std::map<std::string, float> spectralFeatures;
  std::vector<std::string> usedFeatures;

protected:
  fvec_t* currentHopBuffer;

  cvec_t* fftComplexOutputBuffer;
  aubio_fft_t* fftProcessor;
  
  fvec_t* onsetOutputBuffer;
  aubio_onset_t* onsetProcessor;
  
  fvec_t* pitchOutputBuffer;
  aubio_pitch_t* pitchProcessor;

  std::map<std::string, aubio_specdesc_t*> spectralFeatureProcessor;
  std::map<std::string, fvec_t*> spectralFeatureOutputBuffer;

private:
  std::vector<float> binsScale;

  float sampleRate;
  size_t spectrumSize;
  size_t bufferSize;
  size_t hopSize;
};
