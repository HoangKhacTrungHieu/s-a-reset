#pragma once
#include "setting.h"

#define SCREEN_WIDTH 128 // pixels
#define SCREEN_HEIGHT 64 // pixels

float currentHeartRate = 0;
float currentSpO2 = 0;
float sumHeartRate = 0;
float sumSpO2 = 0;
float averageHeartRate = 0;
float averageSpO2 = 0;

void OLEDInit();
void onBeatDetected();
void calculateData();
void OLEDDisplay();
void turnOffOLED(); 
void OLEDDisplayAverage();



