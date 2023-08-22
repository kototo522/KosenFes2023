int LED = 3;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'T') {
      digitalWrite(LED, HIGH);
    } else if (receivedChar == 'N') {
      digitalWrite(LED, LOW);
    }
  }
}