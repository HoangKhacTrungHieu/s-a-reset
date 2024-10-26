#pragma once
#include "setting.h"

float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 670.0;      // Giá trị của điện trở R1
float R2 = 330.0;      // Giá trị của điện trở R2
float ref_voltage = 3.3; // Điện áp tham chiếu (ESP32 sử dụng 3.3V)
int adc_value = 0;

void readADC();
void calculateADC();