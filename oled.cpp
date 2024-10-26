#include "oled.h"


Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OLEDInit()
{

  Wire.begin(3, 2); // SDA là chân 3, SCL là chân 2 trên ESP32-C3

  // Khởi tạo màn hình OLED với địa chỉ I2C 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("Failed to start OLED screen"));
    while (1)
      ;
  }
        
  oled.clearDisplay();

  

  oled.setTextSize(1);
  oled.setTextColor(WHITE);

  oledStartMillis = millis(); // Ghi nhận thời gian bắt đầu hiển thị OLED

}

// Callback khi phát hiện nhịp tim
void onBeatDetected()
{
  Serial.println("Beat!");
}

void calculateData()
{

      // Lấy giá trị nhịp tim và SpO2 hiện tại
      currentHeartRate = pox.getHeartRate();
      currentSpO2 = pox.getSpO2();

      // Thêm giá trị mới vào hàng đợi
      heartRateQueue[queueIndex] = currentHeartRate;
      spO2Queue[queueIndex] = currentSpO2;

      // Tăng chỉ mục hàng đợi và cuộn vòng
      queueIndex = (queueIndex + 1) % period;

      // Cập nhật kích thước hàng đợi (không vượt quá "period")
      if (queueSize < period)
      {
        queueSize++;
      }

      // Tính trung bình nhịp tim và SpO2 từ hàng đợi

      for (int i = 0; i < queueSize; i++)
      {
        sumHeartRate += heartRateQueue[i];
        sumSpO2 += spO2Queue[i];
      }
      averageHeartRate = sumHeartRate / queueSize;
      averageSpO2 = sumSpO2 / queueSize;
}


void OLEDDisplay()
{
      oled.clearDisplay();

      oled.setCursor(0, 0);
      oled.print("Heart rate: ");
      oled.print(currentHeartRate);
      oled.println(" bpm");

      oled.setCursor(0, 16);
      oled.print("SpO2: ");
      oled.print(currentSpO2);
      oled.println(" %");

      oled.setCursor(0, 32);
      oled.print("Avg HR: ");
      oled.print(averageHeartRate);
      oled.println(" bpm");

      oled.setCursor(0, 48);
      oled.print("Avg SpO2: ");
      oled.print(averageSpO2);
      oled.println(" %");

      // Hiển thị giá trị điện áp đo được
      oled.setCursor(0, 56); // Đặt con trỏ ở dòng dưới cùng
      oled.print("Voltage: ");
      oled.print(in_voltage, 2); // Hiển thị điện áp với 2 chữ số thập phân
      oled.println(" V");

      oled.display();
      delay(10);
    
}

void turnOffOLED()
{
  oled.clearDisplay();
  oled.display();
  digitalWrite(buzzerPin, LOW); // Tắt còi khi OLED tắt và dừng kêu
  buzzerActive = false;
}

void OLEDDisplayAverage()
{
      oled.clearDisplay();
        oled.setCursor(0, 0);
        oled.println("Result:");
        oled.setCursor(0, 16);
        oled.print("Avg HR: ");
        oled.print(averageHeartRate);
        oled.println(" bpm");

        oled.setCursor(0, 32);
        oled.print("Avg SpO2: ");
        oled.print(averageSpO2);
        oled.println(" %");

        oled.display();
        delay(10);



}







