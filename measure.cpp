#include "measure.h"

void startMeasuring()
{
 if (lastHeartRate == 0 && pox.getHeartRate() > 0) {
    isMeasuring = true;
    measureStartMillis = millis();
    queueIndex = 0;
    queueSize = 0;
    lastHeartRate = pox.getHeartRate();
  }
}

void completeMeasuring()
{
    if(pox.getHeartRate() == 0)
    {
    isMeasuring = false;

    for (int i = 0; i < queueSize; i++) {
        sumHeartRate += heartRateQueue[i];
        sumSpO2 += spO2Queue[i];
    }

    averageHeartRate = sumHeartRate / queueSize;
    averageSpO2 = sumSpO2 / queueSize;
}

