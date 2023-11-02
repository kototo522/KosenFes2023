#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
const int irSensorPin = 0;
int irState = LOW;

int melo = 200;   // 音の長さを指定
int pin = 13;     // ブザーを接続したピン番号

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  Serial.println("Orientation Sensor Test");
}

void loop() {
  irState = analogRead(irSensorPin);

  if (irState >= 400) {
    // 通常時
    Serial.println(irState);
    noTone(pin);    // ブザーを止める
  }
  else {
    // 引っかかったら
    tone(pin,262,melo);                                                                                                                         
    delay(melo);
    Serial.println(irState);
  }
  delay(50);
}
