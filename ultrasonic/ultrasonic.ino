#define LOOP_DELAY 100 // in ms
#define ECHO_PIN 7
#define TRIG_PIN 8
#define LED_PIN 13

#define PULSE_DURATION 10 // in us

#define MAX_RANGE 200 // in cm
#define MIN_RANGE 0 // in cm
#define OUT_OF_RANGE_MESSAGE "-"

long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
 pinMode(LED_PIN, OUTPUT);
}

void loop() {
 digitalWrite(TRIG_PIN, LOW); 
 delayMicroseconds(2); // Not really sure why we do this...

 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(PULSE_DURATION); 
 
 digitalWrite(TRIG_PIN, LOW);
 // Listen to the echo of the 10 microsecond 40k sound pulse we've just sent.
 duration = pulseIn(ECHO_PIN, HIGH);
 
 //Calculate the distance based on the speed of sound. 
 distance = (duration - PULSE_DURATION) / (29 * 2); //  1/340
 
 if (distance > MAX_RANGE || distance < MIN_RANGE){
  /* Send a negative number to the computer and Turn LED ON to indicate "out of range" */
   Serial.println(OUT_OF_RANGE_MESSAGE);
   digitalWrite(LED_PIN, HIGH);
 }
 else {
   /* Send the distance to the computer using Serial protocol, and turn LED OFF to indicate successful reading. */
   Serial.println(distance);
   digitalWrite(LED_PIN, LOW); 
 }
 
 //Delay before next reading.
 delay(LOOP_DELAY);
}
