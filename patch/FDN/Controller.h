/**
 * @file Controller.h
 * @author Steffan Diedrichsen(sdiedrichsen@mac.com)
 * @brief  simple class for control parameters
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

enum character
{
    eLinear,
    eLogarithmic
};


struct Controller
{
  const char* _pName;
  float       _min;
  float       _max;
  int         _steps;
  character   _response;

  float       _value;
  int         _pos; 

  void Init(const char* pName, float min, float max, int steps, character response, float initialValue);

  void Increment(int steps = 1);
  void Decrement(int steps = 1);
  float Value   ();

  private:
  void ChangeValue(int steps);

};