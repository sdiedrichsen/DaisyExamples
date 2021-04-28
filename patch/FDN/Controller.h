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

#include <string>


enum character
{
    eLinear,
    eLogarithmic
};

struct Controller
{
    const char* _pName;
    const char* _pUnit;
    float       _min;
    float       _max;
    float       _logab;
    int         _steps;
    character   _response;

    float _value;
    int   _pos;
    int   _numDecimals;
    bool  _valueChanged;

    void (*_callback)(float);

    void        Init(const char* pName,
                     const char* pUnit,
                     float       min,
                     float       max,
                     int         steps,
                     character   response,
                     float       initialValue,
                     int         numDecimals);
    void        SetUpdateCallback(void (*Update)(float));
    void        Increment(int steps = 1);
    void        Decrement(int steps = 1);
    float       Value();
    void        ChangeValue(int steps);
    const char* Name();
    const char* ValueString(std::string& str);

    bool ValueHasChanged();
};