#include "rx2b_commands.h" // TODO: library
#include "btcar.h"
#include "Wire.h"

#define DEBUG 1

#define RX2B_PIN 11

int speed = 100;

// Main
void setup() {
  rx2b_init(RX2B_PIN);
}

void loop() {
  rx2b_goForward();
  delay(1000);
}

