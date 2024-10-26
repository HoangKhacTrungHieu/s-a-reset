#include <Arduino.h>
#include "setting.h"


void setup() {
  Serial.begin(9600);
}

void loop() 
{

if (!deviceOn) return; // Nếu `deviceOn` là `false`, không cập nhật OLED

void updateDataSensor();

if (isMeasuring)
  {
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {

      void calculateData();
      void OLEDDisplay();
      void PWMled();
  
      tsLastReport = millis();
    }

    // Kiểm tra xem đã đến lúc kêu còi chưa (5 giây một lần)
    void checkIntervalInTimer();
  }
  else
  {
    void turnOffOLED();     // Đảm bảo dừng kêu còi khi OLED tắt
  }
}