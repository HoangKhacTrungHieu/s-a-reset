#include "sensorI2C.h"

void sensorInit()
{
  Serial.print("Initializing pulse oximeter...");
  if (!pox.begin())
  {
    Serial.println("FAILED");
    while (1)
      ;
  }
  else
  {
    Serial.println("SUCCESS");
  }

  // Đăng ký callback khi phát hiện nhịp tim
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

// Callback khi phát hiện nhịp tim
void onBeatDetected()
{
  Serial.println("Beat!");
}

void updateDataSensor()
{
  // Cập nhật dữ liệu từ cảm biến MAX30100
  pox.update();
}