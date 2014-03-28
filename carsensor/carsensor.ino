#define DEBUG 0

#define SENSOR_LEFT 8
#define SENSOR_MID_LEFT 7
#define SENSOR_CENTER 6
#define SENSOR_MID_RIGHT 5
#define SENSOR_RIGHT 4

#define TX_LEFT_PIN 11
#define TX_RIGHT_PIN 12

#define TIMEOUT 3000

void setup() {
  #if DEBUG
    Serial.begin(9600);
  #endif

  pinMode(TX_LEFT_PIN, OUTPUT);
  pinMode(TX_RIGHT_PIN, OUTPUT);
  
  pinMode(SENSOR_LEFT, INPUT);
  pinMode(SENSOR_MID_LEFT, INPUT);
  pinMode(SENSOR_CENTER, INPUT);
  pinMode(SENSOR_MID_RIGHT, INPUT);
  pinMode(SENSOR_RIGHT, INPUT);  

  digitalWrite(TX_LEFT_PIN, LOW);
  digitalWrite(TX_RIGHT_PIN, LOW);
}

int accum;
void loop() {
  accum = 0;

  bitWrite(accum, 4, !digitalRead(SENSOR_LEFT));
  bitWrite(accum, 3, !digitalRead(SENSOR_MID_LEFT));
  bitWrite(accum, 2, !digitalRead(SENSOR_CENTER));
  bitWrite(accum, 1, !digitalRead(SENSOR_MID_RIGHT));
  bitWrite(accum, 0, !digitalRead(SENSOR_RIGHT));
  
  tx(accum);
}

int prevV = 4;
int lineTs = 0;
void tx(int v) {
  #if DEBUG
    Serial.println(v);
  #endif

  if (v > 0 && v < 0b11111) {
    if (v < 4) {
      if (prevV == 0 || prevV == 0b11111) {
        // LEFT
        digitalWrite(TX_LEFT_PIN, HIGH);
        digitalWrite(TX_RIGHT_PIN, LOW);
      } else {
        // RIGHT
        digitalWrite(TX_LEFT_PIN, LOW);
        digitalWrite(TX_RIGHT_PIN, HIGH);
      }
      #if DEBUG
        Serial.println("right");
      #endif
    } else if (v > 4) {
      if (prevV == 0 || prevV == 0b11111) {
        // RIGHT
        digitalWrite(TX_LEFT_PIN, LOW);
        digitalWrite(TX_RIGHT_PIN, HIGH);
      } else {
        // LEFT
        digitalWrite(TX_LEFT_PIN, HIGH);
        digitalWrite(TX_RIGHT_PIN, LOW);
      }
      #if DEBUG
        Serial.println("left");
      #endif
    } else {
      // FORWARD
      digitalWrite(TX_LEFT_PIN, HIGH);
      digitalWrite(TX_RIGHT_PIN, HIGH);
      #if DEBUG
        Serial.println("fwd");
      #endif
    }
    lineTs = millis();
  } else {
    int diff = (millis() - lineTs);
    #if DEBUG
    Serial.println(diff);
    #endif
    
    if (diff > TIMEOUT) {
      // STOP
      digitalWrite(TX_LEFT_PIN, LOW);
      digitalWrite(TX_RIGHT_PIN, LOW);
      #if DEBUG
        Serial.println("stop");
      #endif
    }
  }
  prevV = v;
}


