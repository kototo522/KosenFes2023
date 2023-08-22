int BUTTON = 2;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    Serial.write('T');
    delay(1000);
  } else {
    Serial.write('N');
    delay(1000);
  }
}