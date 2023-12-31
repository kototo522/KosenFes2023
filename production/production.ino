#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);

void setup(void)
{
  Serial.begin(115200);

  pinMode(3,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);

  while (!Serial) delay(10);  // wait for serial port to open!

  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
}

void loop(void)
{
  sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);//表示順orientationのx方向(0),y方向(1),z方向(2)
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);//表示順linearaccelerometerのx線形加速度(3),y線形加速度(4),z線形加速度(5)

  printEvent(&orientationData);
  printEvent(&linearAccelData);

  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  //表示順スイッチオンオフ(13)
  ( digitalRead(3) == HIGH ) ? Serial.print("1,") : Serial.print("0,");
  ( digitalRead(7) == HIGH ) ? Serial.print("1,") : Serial.print("0,");
  ( digitalRead(10) == HIGH ) ? Serial.println("1") : Serial.println("0");

  delay(BNO055_SAMPLERATE_DELAY_MS);
}

void printEvent(sensors_event_t* event) {
  double x = 0, y = 0 , z = 0;
  if (event->type == SENSOR_TYPE_ORIENTATION) {
    //Serial.print("Orient:");
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(",");
  }
  
}