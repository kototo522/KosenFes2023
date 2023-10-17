#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define BUTTON1 5
#define BUTTON2 9
#define BUTTON3 8

uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void setup(void) {
  Serial.begin(115200);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  while (!Serial)
    delay(10);

  Serial.println("Orientation Sensor Test");
  Serial.println("");

  if (!bno.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
}

float filteredX, filteredY, filteredZ;

void loop(void) {
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

  // フィルタリングするデータとしてorientationDataを使用
  filteredX = orientationData.orientation.x;
  filteredY = orientationData.orientation.y;
  filteredZ = orientationData.orientation.z;

  Serial.print(filteredX);
  Serial.print(",");
  Serial.print(filteredY);
  Serial.print(",");
  Serial.print(filteredZ);
  Serial.print(",");

  (digitalRead(BUTTON1) == HIGH) ? Serial.print("1,") : Serial.print("0,");
  (digitalRead(BUTTON2) == HIGH) ? Serial.print("1,") : Serial.print("0,");
  (digitalRead(BUTTON3) == HIGH) ? Serial.println("1") : Serial.println("0");

  delay(BNO055_SAMPLERATE_DELAY_MS);
}
