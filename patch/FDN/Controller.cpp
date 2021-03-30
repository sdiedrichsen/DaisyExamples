/**
 * @file    Controller.cpp
 * @author Steffan Diedrichsen (sdiedrichsen@mac.com)
 * @brief 
 * @version 0.1
 * @date 2021-03-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Controller.h"
#include <math.h>

void Controller::Init
( const char* pName, float min, float max, int steps, character response, float initialValue)
{
  _pName = pName;
  _min = min;
  _max = max;
  _steps = steps;
  _response = response;
  _value = initialValue;
  _pos   = 0;

  _pos = roundf((_value - _min) * float(_steps) / (_max - _min));
}

void 
Controller::Increment(int steps)
{
  ChangeValue(steps);
}
void 
Controller::Decrement(int steps)
{
  ChangeValue(-steps);
}
void
Controller::ChangeValue(int steps)
{
  if(_response == eLinear)
  {
    _pos += steps;
    _pos = (_pos > _steps)? _steps : _pos;
    _pos = (_pos <  0)?     0 : _pos;

    _value = _min + (_max - _min) * float(_pos) /float(_steps);
  }

}


float 
Controller::Value()
{
  return _value;
}

const char* 
Controller::Name()
{
  return _pName;
}