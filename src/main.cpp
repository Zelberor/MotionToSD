#include "Button.h"
#include <Arduino.h>

const int submitPin = 10;

MotionToSD::Button submit{submitPin};

void setup() { Serial.begin(9600); }

void loop() {
  if (submit.Pressed())
    Serial.println("Pressed");
}

void printErrorCode(int code) {}
