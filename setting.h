#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MAX30100_PulseOximeter.h"
#include "interrupt.h"
#include "oled.h"
#include "PWMLED.h"
#include "sensorI2C.h"
#include "timer.h"
#include "VoltageADC.h"
#include "measure.h"

#define REPORTING_PERIOD_MS 1000
#define buzzerPin 10
#define BUTTON_PIN 0
#define ledPin 1
#define PWMChannel 0
#define resolution 8   // 0->255
#define frequency 1000 // 1m
#define ANALOG_IN_PIN 4 // Chân S của module điện áp nối với GPIO4
#define BUTTON_RESET_PIN 6

PulseOximeter pox;
uint32_t tsLastReport = 0;
volatile bool deviceOn = true; // Trạng thái bật/tắt của OLED (volatile để sử dụng trong ISR)

unsigned long lastMillis = 0;        // Biến chống rung
const unsigned long delayTime = 100; // Thời gian chống rung nút nhấn (100ms)

unsigned long oledStartMillis = 0;   // Thời gian bắt đầu hiển thị OLED
unsigned long buzzerStartMillis = 0; // Thời gian bắt đầu còi kêu
unsigned long interval = 5000;       // Khoảng thời gian giữa các lần còi kêu (5 giây)
unsigned long buzzerOnTime = 200;    // Thời gian còi kêu mỗi lần (200ms)
int buzzerCount = 0;                 // Đếm số lần còi kêu

bool buzzerActive = false;           // Trạng thái kêu của còi
bool buzzerTriggered = false;        // Đánh dấu lần còi báo

// Số lượng giá trị cần lưu để tính trung bình (hàng đợi tối đa 5 giá trị)
const int period = 5;
float heartRateQueue[period]; // Hàng đợi cho nhịp tim
float spO2Queue[period];      // Hàng đợi cho SpO2
int queueIndex = 0;           // Chỉ mục hiện tại trong hàng đợi
int queueSize = 0;            // Kích thước hiện tại của hàng đợi

// Biến dùng để đo điện áp
float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0; // Giá trị của điện trở R1
float R2 = 7500.0;  // Giá trị của điện trở R2
float ref_voltage = 3.3; // Điện áp tham chiếu (ESP32 sử dụng 3.3V)
int adc_value = 0;


