#ifndef RX2B_COMMANDS_H_
#define RX2B_COMMANDS_H_

#include <Arduino.h>


#define RX2B_W1_END 4 // Not used
#define RX2B_W1_FORWARD 10 // Forward
#define RX2B_W1_FORWARD_TURBO 16 // Forward & Turbo
#define RX2B_W1_TURBO 22 // Turbo
#define RX2B_W1_FORWARD_LEFT_TURBO 28 // Turbo & Forward & Left
#define RX2B_W1_FORWARD_RIGHT_TURBO 34 // Turbo & Forward & Right
#define RX2B_W1_BACKWARD 40 // Backward
#define RX2B_W1_BACKWARD_RIGHT 46 // Backward & Right
#define RX2B_W1_BACKWARD_LEFT 52 // Backward & Left
#define RX2B_W1_LEFT 58 // Left
#define RX2B_W1_RIGHT 64 // Right

void rx2b_init(int pinNumber);

void rx2b_goLeft();
void rx2b_goRight();
void rx2b_goForward();
void rx2b_goBackward();

void rx2b_goForwardLeft();
void rx2b_goForwardRight();
void rx2b_goBackwardLeft();
void rx2b_goBackwardRight();


void rx2b_executeCommand(int w1Command);
void rx2b_executeCommandSub(int w1Command);
void rx2b_startCommunication();

#endif
