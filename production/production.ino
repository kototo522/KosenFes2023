#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

int BUTTON1 = 13;
int BUTTON2 = 9;
int BUTTON3 = 8;

void setup(void)
{
  Serial.begin(115200);

  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  pinMode(BUTTON3,INPUT);

  while (!Serial) delay(10);  // wait for serial port to open!

  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* エラー処理 */
  if (!bno.begin())
  {Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
}

void loop(void)
{
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);//表示順orientationのx方向(0),y方向(1),z方向(2)
 
  printEvent(&orientationData);
 
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  //表示順スイッチオンオフ
  ( digitalRead(BUTTON1) == HIGH ) ? Serial.print("1,") : Serial.print("0,");
  ( digitalRead(BUTTON2) == HIGH ) ? Serial.print("1,") : Serial.print("0,");
  ( digitalRead(BUTTON3) == HIGH ) ? Serial.println("1") : Serial.println("0");

  delay(BNO055_SAMPLERATE_DELAY_MS);
}

void printEvent(sensors_event_t* event) {
  double x = -1000000, y = -1000000 , z = -1000000;
  // Orient
  if (event->type == SENSOR_TYPE_ORIENTATION) {
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  }
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.print(",");
}

