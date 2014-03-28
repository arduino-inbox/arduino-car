#include "rx2b_commands.h" // TODO: library
#include "btcar.h"
#include "Wire.h"

#define DEBUG 1

#define RX2B_PIN 11
#define NOOP_DELAY 1

int sensors;

// Bluetooth functions
void bt_init() {
  Serial1.begin(9600);
}

// Main
void setup() {
  rx2b_init(RX2B_PIN);
  bt_init();
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  #if DEBUG
    Serial.begin(9600);
  #endif
}

void receiveEvent(int howMany)
{
  while(Wire.available()) {
    sensors = Wire.read();
  }
  #if DEBUG
    Serial.println(sensors);
  #endif
}

int cnt = 0;
void loop() {
  switch (sensors) {
    case BTCAR_FORWARD:
      rx2b_goForward();
    break;
    case BTCAR_BACKWARD:
      rx2b_goBackward();
    break;
    case BTCAR_LEFT:
      rx2b_goLeft();
    break;
    case BTCAR_RIGHT:
      rx2b_goRight();
    break;
    case BTCAR_FORWARD_RIGHT:
      rx2b_goForwardRight();
    break;
    case BTCAR_BACKWARD_RIGHT:
      rx2b_goBackwardRight();
    break;
    case BTCAR_FORWARD_LEFT:
      rx2b_goForwardLeft();
    break;
    case BTCAR_BACKWARD_LEFT:
      rx2b_goBackwardLeft();
    break;
    
    default:
    case BTCAR_STOP:
          // noop

    break;
  }
  cnt++;
  if (cnt > 8) {
//    sensors = 0;
    rx2b_goBackward();
    delay(200);

    cnt = 0;
  }
}

