#include "rx2b_commands.h"

int rx2b_outputPin;
void rx2b_init(int pinNumber) {
  rx2b_outputPin = pinNumber;
  pinMode(rx2b_outputPin, OUTPUT);
}

void rx2b_goLeft() {
  rx2b_executeCommand(RX2B_W1_LEFT);
}

void rx2b_goRight() {
  rx2b_executeCommand(RX2B_W1_RIGHT);
}

void rx2b_goForwardLeft() {
  rx2b_executeCommand(RX2B_W1_FORWARD_LEFT_TURBO);
}

void rx2b_goForwardRight() {
  rx2b_executeCommand(RX2B_W1_FORWARD_RIGHT_TURBO);
}

void rx2b_goBackwardLeft() {
  rx2b_executeCommand(RX2B_W1_BACKWARD_LEFT);
}

void rx2b_goBackwardRight() {
  rx2b_executeCommand(RX2B_W1_BACKWARD_RIGHT);
}

void rx2b_goForward() {
  rx2b_executeCommand(RX2B_W1_FORWARD);
}

void rx2b_goBackward() {
  rx2b_executeCommand(RX2B_W1_BACKWARD);
}

void rx2b_executeCommand(int w1Command) {
  rx2b_executeCommandSub(w1Command);
//  rx2b_executeCommandSub(w1Command);
//  rx2b_executeCommandSub(w1Command);
  rx2b_executeCommandSub(RX2B_W1_END);

//  rx2b_executeCommandSub(w1Command);
//  rx2b_executeCommandSub(w1Command);
//  rx2b_executeCommandSub(w1Command);
}

void rx2b_executeCommandSub(int w1Command) {
  rx2b_startCommunication();
  for(int i=0; i < w1Command; i++) // This makes the car go "w1Code name" w1Code value (n) pulses 500Mhz 50% duty cycle
  {
    digitalWrite(rx2b_outputPin, HIGH);
    delayMicroseconds(500);

    digitalWrite(rx2b_outputPin, LOW);
    delayMicroseconds(500);
  }
}

void rx2b_startCommunication() {
  for (int i=0; i<=3; i++) // This starts the communication 4 W2 pulses 1KHz 75% duty cycle 
  {
    digitalWrite(rx2b_outputPin, HIGH);
    delayMicroseconds(1500);

    digitalWrite(rx2b_outputPin, LOW);
    delayMicroseconds(500);
  }
}

