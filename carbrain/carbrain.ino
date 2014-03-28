#include "rx2b_commands.h" // TODO: library

#define DEBUG 0
#define SERIAL Serial

#define RX2B_PIN 8

#define TX_LEFT_PIN 11
#define TX_RIGHT_PIN 12

// ultrasonic
#define ULTRASONIC 0
#if ULTRASONIC
#define ECHO_PIN 3
#define TRIG_PIN 2
#define LED_PIN 13
#define PULSE_DURATION 10 // in us
#define MAX_RANGE 200 // in cm
#define MIN_RANGE 0 // in cm
#define ALLOWED_RANGE 10
long duration, distance; // Duration used to calculate distance

int readUltrasonic() {
 digitalWrite(TRIG_PIN, LOW); 
 delayMicroseconds(2); // Not really sure why we do this...

 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(PULSE_DURATION); 
 
 digitalWrite(TRIG_PIN, LOW);
 // Listen to the echo of the 10 microsecond 40k sound pulse we've just sent.
 duration = pulseIn(ECHO_PIN, HIGH);
 
 //Calculate the distance based on the speed of sound. 
 distance = (duration - PULSE_DURATION) / (29 * 2); //  1/340
 #if DEBUG
 SERIAL.print("distance: ");
 SERIAL.println(distance);
 #endif

 if (distance > MIN_RANGE && distance < ALLOWED_RANGE){
  digitalWrite(LED_PIN, HIGH);
  return 0; // go back until far from an obstacle.
 }
 digitalWrite(LED_PIN, LOW);
 return 1; // go forward
}
#endif


// Main
void setup() {
  rx2b_init(RX2B_PIN);
  pinMode(TX_LEFT_PIN, INPUT);
  pinMode(TX_RIGHT_PIN, INPUT);

  #if ULTRASONIC  
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  #endif

  #if DEBUG
    SERIAL.begin(9600);
  #endif
}

void loop() {
  int left = digitalRead(TX_LEFT_PIN);
  int right = digitalRead(TX_RIGHT_PIN);
  int fwd = 1;
  #if ULTRASONIC
  fwd = readUltrasonic();
  #endif
  if (left && right) {
      if (fwd) rx2b_goForward();
      else rx2b_goBackward();
      #if DEBUG
      SERIAL.println("go");
      #endif
  } else if (right) {
      if (fwd) rx2b_goForwardRight();
      else rx2b_goBackwardRight();
      #if DEBUG
      SERIAL.println("right");
      #endif
  } else if (left) {
      if (fwd) rx2b_goForwardLeft();
      else rx2b_goBackwardLeft();
      #if DEBUG
      SERIAL.println("left");
      #endif
  } else {
      #if DEBUG
      SERIAL.println("stop");
      #endif
  }

  
  delay(5);
}

