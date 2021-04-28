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
#include <stdio.h>


void Controller::Init(const char* pName,
                      const char* pUnit,
                      float       min,
                      float       max,
                      int         steps,
                      character   response,
                      float       initialValue,
                      int         numDecimals)
{
    _pName        = pName;
    _pUnit        = pUnit;
    _min          = min;
    _max          = max;
    _steps        = steps;
    _response     = response;
    _value        = initialValue;
    _pos          = 0;
    _numDecimals  = numDecimals;
    _logab        = 0.f;
    _valueChanged = true;
    _callback     = nullptr;

    if(_response == eLinear)
        _pos = roundf((_value - _min) * float(_steps) / (_max - _min));
    else if(_response == eLogarithmic)
    {
        _logab = log10f(_max / _min);
        _pos   = _steps * log10f(_value / _min) / _logab;
    }
}

void Controller::SetUpdateCallback(void (*pf)(float))
{
    _callback = pf;
}

void Controller::Increment(int steps)
{
    ChangeValue(steps);
}
void Controller::Decrement(int steps)
{
    ChangeValue(-steps);
}
void Controller::ChangeValue(int steps)
{
    _pos += steps;
    _pos = (_pos > _steps) ? _steps : _pos;
    _pos = (_pos < 0) ? 0 : _pos;


    if(_response == eLinear)
    {
        _value = _min + (_max - _min) * float(_pos) / float(_steps);
    }
    else if(_response == eLogarithmic)
    {
        _value = _min * powf(10.f, _logab * (float(_pos) / float(_steps)));
    }
    _valueChanged = true;

    if(_callback)
        _callback(_value);
}


float Controller::Value()
{
    return _value;
}

const char* Controller::Name()
{
    return _pName;
}

const char* Controller::ValueString(std::string& str)
{
    int preDecimals = (int)_value;
    int decimals    = (_value - preDecimals) * powf(10.f, _numDecimals);

    str = std::to_string(preDecimals);

    if(_numDecimals == 0)
        goto ADD_UNIT;

    str += ".";

    for(int i = _numDecimals - 1; i > 0; --i)
    {
        float cmp = powf(10.f, i);
        if(decimals < cmp)
            str += "0";
        else
            break;
    }

    str += std::to_string(decimals);
ADD_UNIT:
    str += " ";
    str += _pUnit;

    return &str[0];
}

bool Controller::ValueHasChanged()
{
    bool retVal   = _valueChanged;
    _valueChanged = false;
    return retVal;
}
