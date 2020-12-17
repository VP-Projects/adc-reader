/**
 * @file    AdcReader.h
 * @author  Víctor Pizarro (v.pizarro@outlook.cl)
 * @brief   Declaration of the AdcReader class.
 * @version 0.1.0
 * @date    17-12-2020
 *
 * Copyright (c) 2020 Víctor Pizarro
 *
 */

#ifndef AdcReader_h
#define AdcReader_h

#include <Arduino.h>

/**
 * @brief Class to represent a ADC reader on Arduino. Includes functionality for
 * convertion to desired range, check for invalid values and optional voltage
 * calibration (values must be provided by the user).
 */
class AdcReader
{
/////////////////////////////// PUBLIC ////////////////////////////////////////

public:

    enum AdcRange
    {
        ADC_8_BITS  = 256,
        ADC_10_BITS = 1024,
        ADC_12_BITS = 4096
    };

    enum
    {
        CAL_N_PARAMS = 4
    };

//============================= LIFECYCLE  ====================================

    AdcReader();

//============================= OPERATIONS ====================================

    bool ReadValue();
    bool SetAdcRange(AdcRange adcRange);
    bool SetAnalogPin(uint8_t analogPin);
    bool SetCalParams(float (&calParams) [CAL_N_PARAMS]);
    bool SetInOutRange(float inMin, float inMax, float outMin, float outMax);
    bool SetVcc(float vcc);
    bool UseAdcCal(bool useAdcCal);

// ============================= ACCESS     ====================================

    float GetValue()   const;
    float GetVoltage() const;

//============================= INQUIRY    ====================================

/////////////////////////////// PRIVATE ///////////////////////////////////////

private:

    uint8_t  _analogPin;
    AdcRange _adcRange;

    float _inMin;
    float _inMax;
    float _outMin;
    float _outMax;

    bool  _useAdcCal;
    float _val;
    float _vcc;
    float _voltage;

    float _calParams[CAL_N_PARAMS];

    bool Init();
    bool ReadVoltage();
};

#endif // AdcReader_h