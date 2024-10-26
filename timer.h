#pragma once
#include "setting.h"



// Trạng thái kêu của còi
bool buzzerActive = false;
bool buzzerTriggered = false; 

unsigned long oledStartMillis = 0;   // Thời gian bắt đầu hiển thị OLE
unsigned long buzzerStartMillis = 0; // Thời gian bắt đầu còi kêu
unsigned long interval = 5000;       // Khoảng thời gian giữa các lần còi kêu (5 giây)
unsigned long buzzerOnTime = 200;    // Thời gian còi kêu mỗi lần (200ms)
int buzzerCount = 0;   

void timerInit();
void IRAM_ATTR Timer0_ISR();
void checkIntervalInTimer();

