#define TX_LEFT_PIN 11
#define TX_RIGHT_PIN 12

void setup() {
  pinMode(TX_LEFT_PIN, OUTPUT);
  pinMode(TX_RIGHT_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'g':
        digitalWrite(TX_LEFT_PIN, HIGH);
        digitalWrite(TX_RIGHT_PIN, HIGH);
        break;
      case 'l':
        digitalWrite(TX_LEFT_PIN, HIGH);
        digitalWrite(TX_RIGHT_PIN, LOW);
        break;
      case 'r':
        digitalWrite(TX_LEFT_PIN, LOW);
        digitalWrite(TX_RIGHT_PIN, HIGH);
        break;
      case 's':
        digitalWrite(TX_LEFT_PIN, LOW);
        digitalWrite(TX_RIGHT_PIN, LOW);
        break;
    }
  }
  delay(500);
}
