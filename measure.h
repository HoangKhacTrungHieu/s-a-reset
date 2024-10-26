#pragma once
#include "setting.h"

float lastHeartRate = 0;
bool isMeasuring = false;
int measureStartMillis = 0;
int elapsedSeconds = 0;

unsigned long measureStartMillis = 0;
const unsigned long measureInterval = 15000; // Đo trong 1 phút
unsigned long oledStartMillis = 0;
float sumHeartRate = 0;
float sumSpO2 = 0;
float averageHeartRate = 0;
float averageSpO2 = 0;





void startMeasuring();
void completeMeasuring();