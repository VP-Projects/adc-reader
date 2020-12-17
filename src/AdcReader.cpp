/**
 * @file    AdcReader.cpp
 * @author  Víctor Pizarro (v.pizarro@outlook.cl)
 * @brief   Implementation of the AdcReader class.
 * @version 0.1.0
 * @date    17-12-2020
 *
 * Copyright (c) 2020 Víctor Pizarro
 *
 */

#include <AdcReader.h>

AdcReader::AdcReader()
{
    Init();
}

float AdcReader::GetValue()   const { return _val;     }
float AdcReader::GetVoltage() const { return _voltage; }

bool AdcReader::Init()
{
    _analogPin = A0;
    pinMode(_analogPin, INPUT);

    _adcRange  = AdcRange::ADC_10_BITS;
    _useAdcCal = false;
    _val       = 0.0;
    _vcc       = 3.3;
    _voltage   = 0.0;

    _inMin  = 0.0;
    _inMax  = _vcc;
    _outMin = 0.0;
    _outMax = 1.0;

    for (size_t i = 0; i < CAL_N_PARAMS; i++)
    {
        _calParams[i] = 0.0;
    }
}

bool AdcReader::ReadValue()
{
    if (!ReadVoltage()) return false;

    if (_outMax - _outMin == 0) return false;

    _val =  _voltage / _vcc * (_outMax - _outMin) + _outMin;

    return true;
}

bool AdcReader::ReadVoltage()
{
    _voltage = (analogRead(_analogPin) + 0.5) / _adcRange * _vcc;

    if (_useAdcCal)
    {
        _voltage = _calParams[0] * 1
                 + _calParams[1] * _voltage
                 + _calParams[2] * _voltage * _voltage
                 + _calParams[3] * _voltage * _voltage * _voltage;
    }

    return true;
}

bool AdcReader::SetAdcRange(AdcRange adcRange)
{
    _adcRange  = adcRange;
    return true;
}

bool AdcReader::SetAnalogPin(uint8_t analogPin)
{
    _analogPin = analogPin;
    pinMode(_analogPin, INPUT);

    return true;
}

bool AdcReader::SetCalParams(float (&calParams) [CAL_N_PARAMS])
{
    for (size_t i = 0; i < CAL_N_PARAMS, i++;)
    {
        _calParams[i] = calParams[i];
    }

    return true;
}

bool AdcReader::SetInOutRange(
    float inMin,
    float inMax,
    float outMin,
    float outMax)
{
    if (inMin <= 0)       return false;
    if (inMax <= inMin)   return false;
    if (outMax <= outMin) return false;

    _inMin = inMin;
    _inMax = inMax;
    _outMin = outMin;
    _outMax = outMax;

    return true;
}

bool AdcReader::SetVcc(float vcc)
{
    if (vcc <= 0) return false;

    _vcc = vcc;

    return true;
}