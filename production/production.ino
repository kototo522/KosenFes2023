#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <RunningMedian.h>

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

int BUTTON1 = 13;
int BUTTON2 = 9;
int BUTTON3 = 8;

// 中央値を計算するためのRunningMedianオブジェクト
RunningMedian x_median(10);
RunningMedian y_median(10);
RunningMedian z_median(10);

void setup(void)
{
  Serial.begin(115200);

  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  while (!Serial)
    delay(10); // wait for serial port to open!

  Serial.println("Orientation Sensor Test");
  Serial.println("");

  /* エラー処理 */
  if (!bno.begin())
  {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
}

void loop(void)
{
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

  x_median.add(orientationData.orientation.x); // データをRunningMedianに追加
  y_median.add(orientationData.orientation.y);
  z_median.add(orientationData.orientation.z);

  Serial.print(x_median.getMedian());
  Serial.print(",");
  Serial.print(y_median.getMedian());
  Serial.print(",");
  Serial.print(z_median.getMedian());
  Serial.print(",");

  // スイッチの状態を表示
  (digitalRead(BUTTON1) == HIGH) ? Serial.print("1,") : Serial.print("0,");
  (digitalRead(BUTTON2) == HIGH) ? Serial.print("1,") : Serial.print("0,");
  (digitalRead(BUTTON3) == HIGH) ? Serial.println("1") : Serial.println("0");

  delay(BNO055_SAMPLERATE_DELAY_MS);
}
