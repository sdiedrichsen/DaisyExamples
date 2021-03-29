/**
 * @file    Bandpass.h
 * @author  Steffan Diedrichsen (sdiedrichsen@mac.com)
 * @brief   state variable 1 pole low pass abd 1 pole highpass in series
 * @version 0.1
 * @date    2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

struct Bandpass
{
	float _lpHist;
	float _hpHist;
	float _d0LP;
	float _d0HP;
	float _gainHS;

	void Init();

  /**
   * @brief Process processes
   * 
   * @param in      input sample
   * @return float  filtered output sample
   */
	float Process(const float in);
	
  /**
   * @brief Set High Cutoff 
   * 
   * @param normFreq    normalized cutoff frequency 0...0.5 
   * @param gainHighShelf non functional, provide 0.f
   */
	void SetHighCut(float normFreq, float gainHighShelf);
	void SetLowCut(float normFreq);
};
