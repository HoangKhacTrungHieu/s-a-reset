#include "timer.h"


// Khai báo biến timer
hw_timer_t *timer = NULL;

// Hàm ngắt Timer để điều khiển còi
void IRAM_ATTR Timer0_ISR()
{
  if (buzzerActive && !buzzerTriggered)
  {
    if (millis() - buzzerStartMillis < buzzerOnTime)
    {
      digitalWrite(buzzerPin, HIGH); // Bật còi
    }
    else
    {
      digitalWrite(buzzerPin, LOW); // Tắt còi sau khi kêu xong
      buzzerTriggered = true;       // Đánh dấu lần còi báo xong
    }
  }
}

void timerInit()
{

  pinMode(buzzerPin, OUTPUT);
  // Khởi tạo Timer0 cho ISR để điều khiển còi
  timer = timerBegin(0, 80, true);                // Khởi tạo Timer0 với tần số 80 MHz
  timerAttachInterrupt(timer, &Timer0_ISR, true); // Gán ISR cho Timer
  timerAlarmWrite(timer, 100000, true);           // Đặt ngắt mỗi 100ms
  timerAlarmEnable(timer);                        // Bật báo ngắt
}

void checkIntervalInTimer()
{
    if (millis() - oledStartMillis >= interval)
    {
      buzzerActive = true;             // Kích hoạt còi kêu
      buzzerStartMillis = millis();    // Ghi nhận thời gian bắt đầu kêu còi
      buzzerTriggered = false;         // Đặt lại đánh dấu kêu còi
      oledStartMillis = millis();      // Đặt lại bộ đếm 5 giây
    }
}