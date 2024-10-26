#include "interrupt.h"

void interrputInit()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(BUTTON_PIN, handleButtonPress, FALLING);
}

void IRAM_ATTR handleButtonPress()
{
  if ((millis() - lastMillis) > delayTime)
  {
    deviceOn = !deviceOn;
    lastMillis = millis();
    oledStartMillis = millis(); // Đặt lại thời gian bắt đầu hiển thị OLED
  }
}
