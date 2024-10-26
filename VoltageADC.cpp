#pragma once
#include "VoltageADC.h"

void readADC()
{
  adc_value = analogRead(ANALOG_IN_PIN);
}

void calculateADC()
{
  adc_voltage  = (adc_value * ref_voltage) / 4095.0; // ESP32 có độ phân giải ADC 12 bit
  in_voltage = adc_voltage * (R1 + R2) / R2;
}
