/**
 * @file    Basic_Example.cpp
 * @author  Víctor Pizarro (v.pizarro@outlook.cl)
 * @brief   Demonstrate the use of AdcReader class.
 * @version 0.1.0
 * @date    18-12-2020
 *
 * Copyright (c) 2020 Víctor Pizarro
 *
 */

#include <AdcReader.h>

// Suppose that a temperature value is obtained as an analog voltage (from a
// thermistor for example). The range of operation is from 10[°C] to 40[°C],
// corresponding to voltages from 0.7[V] to 3.1[V]. The AdcReader class can
// be used to wrap all this operations: convertion from ADC counts to analog
// voltage, mapping to a desired output range, and optionally analog voltage
// calibration.

enum
{
    BAUD_RATE            = 115200,
    ANALOG_PIN           = A0,
    SAMPLE_TIME_MILISECS = 1000
};

const float VCC    = 3.3; // ADC reference voltage for convertion [V].
const float inMin  = 0.7; // Minimum input value (analog voltage [V]).
const float inMax  = 3.1; // Maximum input value (analog voltage [V]).
const float outMin = 10;  // Minimum output value (temperature [°C]).
const float outMax = 40;  // Maximum output value (temperature [°C]).

unsigned long lastTime = 0; // Last recorded time [ms].

AdcReader adc;

void setup()
{
    Serial.begin(BAUD_RATE);

    adc.SetAnalogPin(ANALOG_PIN);
    adc.SetAdcRange(AdcReader::ADC_10_BITS);
    adc.UseAdcCal(false);
    adc.SetVcc(VCC);
    adc.SetInOutRange(inMin, inMax, outMin, outMax);

    Serial.print("Vin[V]");
    Serial.print('\t');
    Serial.println("T[°C}");

    lastTime = millis();
}

void loop()
{
    if (millis() - lastTime <= SAMPLE_TIME_MILISECS)
    {
        lastTime = millis();

        if (!adc.ReadValue())
        {
            Serial.println("Error on reading.");
        }
        else
        {
            float input_voltage = adc.GetVoltage();
            float temperature   = adc.GetValue();

            Serial.print("input_voltage");
            Serial.print('\t');
            Serial.println("temperature");
        }
    }
}