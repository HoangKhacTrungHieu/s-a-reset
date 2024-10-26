#include "PWMLED.h"

void PWMInit()
{
  ledcSetup(PWMChannel, frequency, resolution);
  ledcAttachPin(ledPin, PWMChannel);
}

void PWMled()
{
      if (averageHeartRate < 30 || averageHeartRate > 240)
      {
        // Sáng LED khi nhịp tim trung bình nằm ngoài khoảng 30-240 bpm
        ledcWrite(PWMChannel, 255); // Sáng tối đa
      }
      else
      {
        // Tắt LED khi nhịp tim trung bình nằm trong khoảng 30-240 bpm
        ledcWrite(PWMChannel, 0); // Tắt LED
      }
}