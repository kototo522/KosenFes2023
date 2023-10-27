#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // LCDのI2Cアドレスとサイズに合わせて変更

const int irSensorPin = 0;  // 赤外線センサーモジュールのピン番号に合わせて変更
int irState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  Serial.println("Orientation Sensor Test");
}

void loop() {
  irState = analogRead(irSensorPin);

  if (irState >= 750) {
    // 通常時
    Serial.println(irState);
  }
  else {
    // 引っかかったら
    Serial.println(irState);
  }
  delay(50);
}
